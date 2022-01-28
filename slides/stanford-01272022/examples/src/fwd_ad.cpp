#include <fastad>
#include <iostream>
#include <string>
#include <iomanip>

int main(int argc, char** argv)
{
    // setup (IGNORE)
    std::vector<double> t_vals;
    if (argc > 1) {
        t_vals.resize(argc-1);
        ++argv;
        for (int i = 0; *argv; ++argv, ++i) {
            t_vals[i] = std::stod(*argv);
        }
    } else {
        t_vals.resize(1);
        t_vals[0] = 1.0;
    }
    // end setup

    using namespace ad;

    for (double t_val : t_vals) {

        // essence
        ForwardVar<double> t(t_val, 1);
        ForwardVar<double> theta = ForwardVar<double>(3.) * t;
        ForwardVar<double> x = cos(theta);
        ForwardVar<double> y = sin(theta);
        // end essence

        // output (IGNORE)
        std::cout 
            << std::setprecision(16) 
            << "Velocity at t=" << t_val 
            << ": (" << x.get_adjoint() << ", " << y.get_adjoint() << ")"
            << std::setw(10);
        std::cout << "Actual: (" 
            << -3*std::sin(3*t_val)
            << ", "
            << 3*std::cos(3*t_val)
            << ")\n";
        // end output
    }

    return 0;
}
