#include "../include/mcm.h"

int main(){

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

    MCM mcm(num, a, b, minF, maxF, numThreads, numPoints, epsilon, f, realIntegralValue);
    mcm.ShowResult();
    return 0;
}
