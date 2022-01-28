#include <fastad>
#include "optimizer.hpp"
#include <iostream>
#include <random>
#include <iomanip>

int main(int argc, char **argv)
{
    size_t n = 0;
    size_t p = 0;
    double lmda = 0;
    size_t seed = 0;

    if (argc == 5) {
        ++argv;
        n = std::stoi(*argv++);
        p = std::stoi(*argv++);
        lmda = std::stod(*argv++);
        seed = std::stoi(*argv++);
    } else {
        std::cerr << "./a.out n_samples n_vars lmda seed" << std::endl;
        return 1;
    }

    // Generate X_i ~ N(0, I_p)
    std::mt19937 gen(seed);
    Eigen::MatrixXd X = 
        Eigen::MatrixXd::NullaryExpr(n, p, 
                [&](auto i) { 
                    return std::normal_distribution<double>(0.0, 1.0)(gen);
                });
 
    // Generate true beta
    Eigen::VectorXd beta =
        Eigen::VectorXd::NullaryExpr(p,
                [&](auto i) {
                    return std::normal_distribution<double>(0.0, 1.0)(gen);
                });

    // Generate y ~ N(Xbeta, I)
    Eigen::VectorXd y=
        Eigen::VectorXd::NullaryExpr(n,
                [&](auto i) {
                    return std::normal_distribution<double>(0.0, 1.0)(gen);
                }) + X * beta;

    // Ridge model (negative joint log-pdf)
    ad::Var<double, ad::vec> b(p);

    auto expr = ad::bind(
        -ad::normal_adj_log_pdf(y, ad::dot(X, b), 1.0)
        -ad::normal_adj_log_pdf(b, 0.0, 1./lmda)
    );
    
    auto resetter = [&]() { b.reset_adj(); };

    int status = grad_desc(expr, b, resetter, 0.005, 1e-8, 1000);
    if (status) {
        std::cerr << "Warning: did not converge." << std::endl;
    }

    // Compute true MAP (ridge solution)
    Eigen::MatrixXd xtx_lmda = X.transpose() * X;
    xtx_lmda.diagonal().array() += lmda;
    Eigen::ColPivHouseholderQR<Eigen::MatrixXd> dec(xtx_lmda);
    Eigen::VectorXd true_map = dec.solve(X.transpose() * y);

    // Compare output
    std::cout << std::setprecision(16) << "Esti MAP: \n" << b.get() << std::endl;
    std::cout << std::setprecision(16) << "True MAP: \n" << true_map << std::endl;

    return 0;
}
