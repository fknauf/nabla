#include <nabla/nabla.hh>
#include <iostream>

auto main() -> int {
    auto x = nabla::expr::variable<0> {};
    auto y = nabla::expr::variable<1> {};
    auto z = nabla::expr::variable<2> {};

    // function.
    auto f  = exp(x * log(y) + z) / pow(y * z, 2 * x);

    // partial derivative with respect to y
    auto df = f.diff(y);

    // prints "-0.557932", the value of the derivative at point (1, 2, 3)
    std::cout << df(1, 2, 3) << std::endl;

    auto ddf = f.diff(x, y);
    std::cout << ddf(1, 2, 3) << std::endl;

    // Convenience functions for gradient and hessian matrix computation exist:
    std::cout <<
        "Gradient: "        << nabla::gradient(f, 1, 2, 3).transpose() << "\n"
        "Hessian matrix:\n" << nabla::hessian (f, 1, 2, 3)             << std::endl;
}
