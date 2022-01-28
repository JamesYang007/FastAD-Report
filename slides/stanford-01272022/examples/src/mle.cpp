#include <fastad>
#include "optimizer.hpp"
#include <iostream>
#include <random>
#include <iomanip>

int main(int argc, char** argv)
{
    size_t n = 0;
    double mu_val = 0.0;
    size_t seed = 0;

    if (argc == 4) {
        ++argv;
        n = std::stoi(*argv++);
        mu_val = std::stod(*argv++);
        seed = std::stoi(*argv++);
    } else {
        std::cerr << "./a.out n_samples mu_val seed" << std::endl;
        return 1;
    }

    // Gaussian model
    std::mt19937 gen(seed);
    Eigen::VectorXd x_vals = 
        Eigen::VectorXd::NullaryExpr(n,
                [&](auto i) { 
                    return std::normal_distribution<double>(mu_val, 1.0)(gen);
                });

    double mle_val = 0.0;
    double mle_adj = 0.0;
    ad::VarView<double> mle(&mle_val, &mle_adj);

    auto expr = ad::bind(0.5 * ad::norm(x_vals - mle));

    auto resetter = [&]() { mle.reset_adj(); };

    int status = grad_desc(expr, mle, resetter, 0.001, 1e-8, 100);
    if (status) {
        std::cerr << "Warning: did not converge." << std::endl;
    }

    std::cout << std::setprecision(16) << "Esti MLE: " << mle.get() << std::endl;
    std::cout << std::setprecision(16) << "True MLE: " << x_vals.mean() << std::endl;

    return 0;
}
