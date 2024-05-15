#include "../include/mcm.h"

MCM::MCM(size_t num, double a, double b, double minF, double maxF, size_t numThreads, 
         size_t numPoints, double epsilon, double (*f)(double), double realIntegralValue)
         : num_(num), a_(a), b_(b), minF_(minF), maxF_(maxF), numThreads_(numThreads), 
         numPoints_(numPoints), epsilon_(epsilon), f_(f), realIntegralValue_(realIntegralValue)
{
    d_ = (a<b)?(b-a)*(maxF-minF):(a-b)*(maxF-minF);
}

double MCM::Compute(){
    std::random_device rd;
    std::mt19937 gen(rd());
    auto RandomValue = [&]{ return a_ + (b_ - a_)*((gen()%num_)/(double)num_); };
    std::vector<std::thread> threads;
    std::vector<double> results(numThreads_, 0);
    double result = 0;
    auto s = [&](size_t ind){
        size_t in = 0;
        while (in < num_){
            results[ind] += f_(RandomValue());
            ++in;
        }
    };
    for (size_t i = 0; i < numThreads_; ++i){
        threads.emplace_back(s, i);
    }
    for (auto& thread: threads){
        thread.join();
    }
    for (size_t i = 0; i < numThreads_; ++i){
        result += results[i];
    }
    return (b_ - a_)/num_*result/numThreads_;
}

void MCM::ApproximationMCM(){
    resultIntegralValue_ = 0;
    error_ = 0;
    double r = 0;
    for (size_t i = 0; i < num_; ++i){
        r = Compute();
        (abs(realIntegralValue_ - r) <= epsilon_*d_)?:++error_;
        resultIntegralValue_ += r;
    }
    resultIntegralValue_/=num_;
}

bool MCM::ValidateAccuracyMCM(){
    return ((double)error_/num_ <= realIntegralValue_*(d_ - realIntegralValue_)/(numPoints_*(epsilon_*epsilon_)*(d_*d_)))?true:false;
}

void MCM::ShowResult(){
    auto start = std::chrono::high_resolution_clock::now();
    ApproximationMCM();
    std::cout << "result: " << resultIntegralValue_ << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()/static_cast<double>(num_) << "ms\n";
    std::cout << "is validate: " << ValidateAccuracyMCM() << '\n';
}
