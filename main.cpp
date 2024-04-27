#include <iostream>
#include <cstddef>
#include <random>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>

double MonteCarloMethod(size_t numThreads, size_t n, double a, double b, double (*f)(double)){
    double result = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    auto RandomValue = [&a, &b, &n, &gen]{ return a + (b - a)*((gen()%n)/(double)n); };
    double sumFValues = 0;
    std::vector<std::thread> threads;
    size_t in = 0;
    auto s = [&result, &f, &in, &n, &RandomValue](){
        while (in<n){
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
    return (b-a)/n*result;
}

int main(){
    std::cout << MonteCarloMethod(10, 10000, 0, M_PI, *sin) << '\n';
    return 0;
}
