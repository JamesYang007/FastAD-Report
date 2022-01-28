#include <cmath>
#include <iostream>

double f(double x) 
{
    return x * std::sin(x);
}

double dfdx(double x, double h)
{
    return (f(x+h)-f(x))/h;
}

double dfdx_an(double x)
{
    return std::sin(x) + x * std::cos(x);
}

int main() 
{
    for (double h = 1e-7; h >= 1e-16; h /= 10) {
        std::cout << "h=" << h << ", dfdx=" << dfdx(0.13, h) << '\n';
    }
    std::cout << "dfdx_an=" << dfdx_an(0.13) << '\n';

    std::cout << '\n';

    for (double h = 1e-7; h >= 1e-16; h /= 10) {
        std::cout << "h=" << h << ", dfdx=" << dfdx(32, h) << '\n';
    }
    std::cout << "dfdx_an=" << dfdx_an(32) << '\n';

    return 0;
}
