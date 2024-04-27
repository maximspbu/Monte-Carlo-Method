#include <iostream>
#include <cstddef>
#include <random>
#include <thread>
#include <vector>
#include <cmath>

double MonteCarloMethod(size_t numThreads, size_t n, double a, double b, double (*f)(double)){
    double result = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    auto RandomValue = [&a, &b, &n, &gen]{ return a + (b - a)*((gen()%n)/(double)n); };
    double sumFValues;
    for (size_t i = 0; i < n; ++i){
        sumFValues += f(RandomValue());
    }
    result = (b-a)/n*sumFValues;
    return result;
}

int main(){
    std::cout << MonteCarloMethod(10, 10000, 0, 3.14, *sin) << '\n';
    return 0;
}
