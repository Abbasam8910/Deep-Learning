#include <iostream>
#include <cmath>
#include <functional>

// Bisection Method Function
double bisection(std::function<double(double)> func, double a, double b, double tolerance)
{
    // Check if the initial interval is valid
    if (func(a) * func(b) >= 0)
    {
        std::cerr << "Error: The function must have opposite signs at the endpoints a and b." << std::endl;
        return NAN;
    }

    double mid;
    while ((b - a) / 2.0 > tolerance)
    {
        mid = (a + b) / 2.0;
        double f_mid = func(mid);

        // Check if the midpoint is a root
        if (std::fabs(f_mid) <= tolerance)
        {
            return mid;
        }

        // Narrow down the interval
        if (func(a) * f_mid < 0)
        {
            b = mid; // Root is in the left subinterval
        }
        else
        {
            a = mid; // Root is in the right subinterval
        }
    }

    // Return the midpoint as the approximate root
    return (a + b) / 2.0;
}

// Example usage
int main()
{
    // Define the function as a lambda
    auto func = [](double x)
    { return x * x - 4; }; // Example: f(x) = x^2 - 4

    double a = 0.0;          // Start of the interval
    double b = 5.0;          // End of the interval
    double tolerance = 1e-6; // Desired precision

    double root = bisection(func, a, b, tolerance);

    if (!std::isnan(root))
    {
        std::cout << "The root is approximately: " << root << std::endl;
    }
    else
    {
        std::cerr << "Failed to find a root." << std::endl;
    }

    return 0;
}
