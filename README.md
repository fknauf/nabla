# Nabla - compile-time partial derivatives for C++

Nabla is a library for automatic partial differentiation of multivariate functions
at compile time using C++ expression templates for speed and profit. Currently it
handles functions in the reals. Eigen3 and Armadillo are supported backends.

## Usage

With Nabla, otherwise tedious partial differentiation of even deeply nested
functions in n directions requires only a closed form of the function:

```c++
#include <nabla/nabla.hh>
#include <iostream>

int main() {
    nabla::expr::variable<0> x;
    nabla::expr::variable<1> y;
    nabla::expr::variable<2> z;

    // function.
    auto f  = exp(x * log(y) + z) / pow(y * z, 2 * x);

    // partial derivative with respect to y
    auto df = f.diff(y);

    // prints "-0.557932", the value of the derivative at point (1, 2, 3)
    std::cout << df(1, 2, 3) << std::endl;

    // Convenience functions for gradient and hessian matrix computation exist:
    std::cout <<
        "Gradient: "        << nabla::gradient(f, 1, 2, 3).transpose() << "\n"
        "Hessian matrix:\n" << nabla::hessian (f, 1, 2, 3)             << std::endl;
}
```

Each differentiation yields a Nabla function, so derivatives can be nested
to arbitrary depths. In the example above,

```c++
    auto ddf  = df.diff(x);   // would yield d^2f/dxdy
    auto ddf2 = f.diff(x, y); // would yield the same
```

It is also possible to pass evaluation arguments to a Nabla function as a vector.
This is equivalent to the last line of the example:

```c++
    nabla::vector<3> vars { 1, 2, 3 };
    std::cout << df(vars) << std::endl;
```

Note that the exact handling of `nabla::vector` depends on the chosen backend.
The default backend is Eigen3, in which case `nabla::vector<3>` is an alias
for `Eigen::Matrix<double, 3, 1>`. If `NABLA_BACKEND_ARMADILLO` is defined,
it is instead an alias for `arma::Col<double>::fixed<3>`.

For more examples, take a look into the `tests` subdirectory. That's pretty
much it, though. In addition to elementary arithmetic, currently supported
functions are:

| Category              | Function List                                                            |
| --------------------- | ------------------------------------------------------------------------ |
| Powers and Logarithms | `pow`, `exp`, `log`, `exp2`, `expm1`, `log10`, `log1p`, `log2`           |
| Roots                 | `sqrt`, `cbrt`                                                           |
| Trigonometry          | `sin`, `cos`, `tan`, `asin`, `acos`, `atan`                              |
| Hyberbolic functions  | `sinh`, `cosh`, `tanh`, `asinh`, `acosh`, `atanh`                        |
| Geometry              | `hypot` (Euclidian distance)                                             |
| Statistics            | `erf`, `erfc`, `gausscdf`, `Phi` (`gausscdf` with &mu; = 0, &sigma; = 1) |
| Other                 | `fabs`                                                                   |

## Dependencies

Nabla depends on either [Eigen](http://eigen.tuxfamily.org) or
[Armadillo](https://arma.sourceforge.net/) for the vector types and
calculations.

The build system for the unit tests pulls both in using
[vcpkg](https://vcpkg.io), which is supposed to have been integrated
with `vcpkg integrate install`. This is not required to use Nabla,
which is header-only.
