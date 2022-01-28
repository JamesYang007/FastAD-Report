#include <fastad>
#include "optimizer.hpp"
#include <iostream>
#include <random>
#include <iomanip>

int main(int argc, char** argv)
{
    size_t n = 0;
    // (pi, mu_1, mu_2, sigma_1, sigma_2)
    Eigen::VectorXd theta(5);
    size_t seed = 0;

    if (argc == 8) {
        ++argv;
        n = std::stoi(*argv++);
        for (int i = 0; i < theta.size(); ++i) {
            theta[i] = std::stod(*argv++);
        }
        seed = std::stoi(*argv++);
    } else {
        std::cerr << "./a.out n_samples seed pi mu_1 mu_2 sigma_1 sigma_2" << std::endl;
        return 1;
    }

    // for identifiability, switch order of mixture
    if (theta[0] > 0.5) {
        theta[0] = 1-theta[0];
        std::swap(theta[1], theta[3]);
        std::swap(theta[2], theta[4]);
    }

    // Gaussian model
    std::mt19937 gen(seed);
    Eigen::VectorXd x_vals(n);
    for (int i = 0; i < n; ++i) {
        bool cl = std::bernoulli_distribution(theta[0])(gen);
        if (cl) {
            x_vals[i] = std::normal_distribution<double>(theta[1], theta[3])(gen);
        } else {
            x_vals[i] = std::normal_distribution<double>(theta[2], theta[4])(gen);
        }
    }

    // (logit(pi), mu_1, mu_2, log(sigma_1), log(sigma_2))
    Eigen::VectorXd mle_vals(theta.size());
    Eigen::VectorXd mle_adjs(theta.size());
    mle_vals.setZero();
    mle_vals[0] = -0.01;
    mle_adjs.setZero();

    ad::VarView<double, ad::vec> mle(mle_vals.data(), mle_adjs.data(), theta.size());
    ad::Var<double> pi, s1, s2;

    auto expr = ad::bind((
        pi = 1. / (1. + ad::exp(-mle[0])),
        s1 = ad::exp(mle[3]),
        s2 = ad::exp(mle[4]),
        -ad::sum(ad::log(
            (pi / s1) * ad::exp(ad::pow<2>(x_vals-mle[1])/(-2.*ad::pow<2>(s1)))
            + ((1.-pi) / s2) * ad::exp(ad::pow<2>(x_vals-mle[2])/(-2.*ad::pow<2>(s2)))
        ))
    ));

    auto resetter = [&]() {
        mle.reset_adj();
        pi.reset_adj();
        s1.reset_adj();
        s2.reset_adj();
    };

    int status = grad_desc(expr, mle, resetter, 0.005, 1e-8, 1000);
    if (status) {
        std::cerr << "Warning: did not converge." << std::endl;
    }

    // retransform the variables
    mle_vals[0] = 1. / (1. + std::exp(-mle_vals[0]));
    mle_vals[3] = std::exp(mle_vals[3]);
    mle_vals[4] = std::exp(mle_vals[4]);

    std::cout << std::setprecision(16) << "Esti MLE: \n" << mle.get() << std::endl;

    return 0;
}
