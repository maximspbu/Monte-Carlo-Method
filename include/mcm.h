#include <iostream>
#include <cstddef>
#include <random>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>
#include <chrono>
#include <utility>


class MCM{
public:
    MCM(size_t num, double a, double b, double minF, double maxF,
    size_t numThreads, size_t numPoints, double epsilon, double (*f)(double), double realIntegralValue);
    double Compute();
    void ApproximationMCM();
    bool ValidateAccuracyMCM();
    void ShowResult();
private:
    size_t num_; 
    double a_; 
    double b_;
    double minF_; 
    double maxF_;
    double d_;
    size_t numThreads_;
    size_t numPoints_;
    double epsilon_;
    double (*f_)(double);
    double realIntegralValue_;
    double resultIntegralValue_;
    size_t error_;
};
