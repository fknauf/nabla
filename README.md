# Nabla - automatic partial derivatives for C++

Nabla is a library for automatic partial differentiation of multivariate functions
using C++ expression templates for speed and profit. Currently it handles functions in
the reals; future versions may include support for complex numbers.

## Usage

With Nabla, otherwise tedious partial differentiation of even deeply nested
functions in n directions requires only a closed form of the function:

    #include <nabla/nabla.hh>
    #include <iostream>
    
    int main() {
      nabla::expr::variable<0> x;
      nabla::expr::variable<1> y;
      nabla::expr::variable<2> z;
    
      // function.
      auto f  = exp(x * log(y) + z) / pow(y * z, 2 * x);
    
      // partial derivative with respect to y
      auto df =  f.diff(y);
    
      // prints "-0.557932", the value of the derivative at point (1, 2, 3)
      std::cout << df(1, 2, 3) << std::endl;

      // Convenience functions for gradient and hessian matrix computation exist:
      std::cout <<
        "Gradient: "        << nabla::gradient(f, 1, 2, 3).transpose() << "\n"
        "Hessian matrix:\n" << nabla::hessian (f, 1, 2, 3)             << std::endl;
    }

Each differentiation yields a Nabla function, so derivatives can be nested
to arbitrary depths. In the example above,

    auto ddf  = df.diff(x);   // would yield d^2f/dxdy
    auto ddf2 = f.diff(x, y); // would yield the same

It is also possible to pass evaluation arguments to a Nabla function as a vector.
This is equivalent to the last line of the example:

    nabla::vector<3> vars { 1, 2, 3 };
    std::cout << df(vars) << std::endl;

Note that `nabla::vector<3>` is an alias for `Eigen::Vector3d` (see "Dependencies" below).

For more examples, take a look into the `tests` subdirectory. That's pretty
much it, though. In addition to elementary arithmetic, currently supported
functions are:

 * `pow`
 * `exp`
 * `log`
 * `exp2`
 * `expm1`
 * `log10`
 * `log1p`
 * `log2`
 * `sin`
 * `cos`
 * `tan`
 * `asin`
 * `acos`
 * `atan`
 * `sinh`
 * `cosh`
 * `tanh`
 * `asinh`
 * `acosh`
 * `atanh`
 * `sqrt`
 * `cbrt`
 * `fabs`
 * `erf`
 * `erfc`
 * `Phi` (gauss normal distribution function with &mu; = 0, &sigma; = 1)
 * `gausscdf` (same with arbitrary &mu; and &sigma;)
 * `hypot`

## Dependencies

Nabla depends on [Eigen](http://eigen.tuxfamily.org) for the vector types and
calculations. `nabla::vector<n>` is an alias for an Eigen vector of doubles of
length `n`.

Furthermore, Nabla depends on my own pack_traits library for introspection on
variadic template argument packs. This is configured as a subrepository and will
be automatically cloned into your Nabla working copy.
