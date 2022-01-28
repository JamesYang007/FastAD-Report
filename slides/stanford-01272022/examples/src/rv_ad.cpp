#include <fastad>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
    using namespace ad;

    double x_vals[3] = {0.0};
    double a_vals[3] = {0.0};

    // setup (IGNORE)
    if (argc == 4) {
        ++argv;
        for (int i = 0; *argv; ++argv, ++i) {
            x_vals[i] = std::stod(*argv);
        }
    } else {
        std::cerr << "Needs 3 input values" << std::endl;
        return 1;
    }
    // end setup

    // reverse ad code

    VarView<double, vec> x(x_vals, a_vals, 3);
    auto expr = ad::bind(sin(x[0]) + cos(x[1]) * x[2] - log(x[2]));
    autodiff(expr);
    std::cout << std::setprecision(16) << x.get_adj() << std::endl << std::endl;

    // sanity check
    std::cout << 
        std::setprecision(16)
        <<
        std::cos(x_vals[0])
        << "\n"
        << -std::sin(x_vals[1]) * x_vals[2] 
        << "\n"
        << std::cos(x_vals[1]) - 1./x_vals[2]
        << std::endl;

    return 0;
}
