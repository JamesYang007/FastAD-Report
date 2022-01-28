#include <fastad>
#include <iostream>
#include <chrono>
#include <iomanip>

// Definition of f.
struct F
{
    F(const Eigen::MatrixXd& M)
        : M_{M}
    {}

    auto operator()(const Eigen::VectorXd& x) const {
        return (M_ * x).sum() - 2.0 * std::log(x.array().exp().sum());
    }

    Eigen::VectorXd dfdx(const Eigen::VectorXd& x) const {
        Eigen::VectorXd ex = x.array().exp();
        return M_.colwise().sum().transpose() - (2. / ex.sum()) * ex;
    }

    Eigen::VectorXd f_dfdx(const Eigen::VectorXd& x) const {
        Eigen::VectorXd ex = x.array().exp();
        double ex_sum = ex.sum();
        volatile double tmp = (M_ * x).sum() - 2.0 * std::log(ex_sum);
        static_cast<void>(tmp);
        return M_.colwise().sum().transpose() - (2. / ex_sum) * ex;
    }

    auto expr(const ad::VarView<double, ad::vec>& x) const {
        return ad::sum(ad::dot(M_, x)) - 2.0 * ad::log(ad::sum(ad::exp(x)));
    }


private:
    const Eigen::MatrixXd& M_;
};

// Finite Difference method to compute gradient of f.
template <class F>
Eigen::VectorXd fd(F f, Eigen::VectorXd& x, double h)
{
    Eigen::VectorXd out(x.size());
    double fx = f(x);
    for (int i = 0; i < out.size(); ++i) {
        x[i] += h;
        out[i] = (f(x) - fx) / h;
        x[i] -= h;
    }
    return out;
}

template <class F>
void rv_ad(F f, ad::VarView<double, ad::vec>& x)
{
    auto expr = ad::bind(f.expr(x));
    ad::autodiff(expr);
}

int main(int argc, char **argv)
{
    size_t n = 0;
    size_t p = 0;
    bool do_fd = false;
    if (argc == 4) {
        ++argv;
        n = std::stoi(*argv++);
        p = std::stoi(*argv++);
        do_fd = std::stoi(*argv++);
    }
    else {
        std::cerr << "./a.out n p do_fd" << std::endl;
        return 1;
    }

    Eigen::MatrixXd M(n, p);
    M.setRandom();

    Eigen::VectorXd x_vals(p);
    Eigen::VectorXd a_vals(p);
    x_vals.setRandom();
    a_vals.setZero();

    ad::VarView<double, ad::vec> x(x_vals.data(), a_vals.data(), p);

    F f(M);

    // time fd
    double fd_time = -1.0;
    Eigen::VectorXd fd_res;
    if (do_fd) {
        auto begin = std::chrono::steady_clock::now();
        fd_res = fd(f, x_vals, 1e-8);
        auto end = std::chrono::steady_clock::now();
        fd_time = std::chrono::duration_cast<
            std::chrono::nanoseconds>(end-begin).count() * 1e-9;
    }

    // time rv_ad
    auto begin = std::chrono::steady_clock::now();
    rv_ad(f, x);
    auto end = std::chrono::steady_clock::now();
    double rv_ad_time = std::chrono::duration_cast<
        std::chrono::nanoseconds>(end-begin).count() * 1e-9;

    // time manual
    begin = std::chrono::steady_clock::now();
    auto manual_res = f.dfdx(x_vals);
    end = std::chrono::steady_clock::now();
    double manual_time = std::chrono::duration_cast<
        std::chrono::nanoseconds>(end-begin).count() * 1e-9;

    // time manual f + dfdx
    begin = std::chrono::steady_clock::now();
    manual_res = f.f_dfdx(x_vals);
    end = std::chrono::steady_clock::now();
    double manual_all_time = std::chrono::duration_cast<
        std::chrono::nanoseconds>(end-begin).count() * 1e-9;

    std::cout << std::setprecision(16) << "FD res: \n" << fd_res << std::endl;
    std::cout << std::setprecision(16) << "AD res: \n" << x.get_adj() << std::endl;
    std::cout << std::setprecision(16) << "MA res: \n" << manual_res << std::endl;
    std::cout << "FD (s): " << fd_time << std::endl;
    std::cout << "AD (s): " << rv_ad_time << std::endl;
    std::cout << "M  (s): " << manual_time << std::endl;
    std::cout << "MA (s): " << manual_all_time << std::endl;

    return 0;
}
