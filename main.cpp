#include <iostream>
#include <cstddef>
#include <random>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>
#include <chrono>
#include <utility>

namespace {
    size_t num = 100;
    double a = 0;
    double b = M_PI;
    double minF = 0;
    double maxF = 1;
    double d = (a<b)?(b-a)*(maxF-minF):(a-b)*(maxF-minF);
    size_t numThreads = 10;
    size_t numPoints = 10000;
    double epsilon = 0.01;
    double (*f)(double) = sin;
    double realIntegralValue = 2;
}; //namespace

double MCM(){
    double result = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    auto RandomValue = [&gen]{ return a + (b - a)*((gen()%num)/(double)num); };
    double sumFValues = 0;
    std::vector<std::thread> threads;
    size_t in = 0;
    auto s = [&result, &in, &RandomValue](){
        while (in<num){
            result += f(RandomValue());
            ++in;
        }
    };
    for (size_t i = 0; i < numThreads; ++i){
        threads.emplace_back(s);
    }
    for (auto& thread: threads){
        thread.join();
    }
    return (b - a)/num*result;
}

std::pair<double, size_t> ApproximationMCM(){
    double resultIntegralValue = 0;
    size_t error = 0;
    double r = 0;
    for (size_t i = 0; i < num; ++i){
        r = MCM();
        (abs(realIntegralValue - r) <= epsilon*d)?:++error;
        resultIntegralValue += r;
    }
    return std::pair<double, size_t>(resultIntegralValue/num, error);
}

bool ValidateAccuracyMCM(std::pair<double, size_t> result){
    return ((double)result.second/num <= realIntegralValue*(d - realIntegralValue)/(numPoints*(epsilon*epsilon)*(d*d)))?true:false;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<double, size_t> result = ApproximationMCM();
    std::cout << "result: " << result.first << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()/static_cast<double>(num) << "ms\n";
    std::cout << "is validate: " << ValidateAccuracyMCM(result) << '\n';
    return 0;
}
