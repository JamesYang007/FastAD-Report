#pragma once
#include <fastad>

template <class ExprType, class XType, class ResetterType>
inline int
grad_desc(ExprType&& expr, 
          XType&& x,
          ResetterType resetter,
          double alpha, 
          double tol=1e-8,
          size_t max_iter = 100)
{
    constexpr bool is_scl = ad::util::is_scl_v<std::decay_t<XType> >;

    auto diff = [](const auto& a, const auto& b) {
        if constexpr (is_scl) {
            return std::abs(a-b);
        } else {
            return (a-b).norm();
        }
    };

    size_t iter = 0;

    using old_t = std::conditional_t<is_scl, double, Eigen::VectorXd>;

    old_t x_old;
    old_t a_old;

    auto new_alpha = [&]() {
        auto a_diff = x.get_adj() - a_old; 
        if constexpr (is_scl) {
            return std::abs((x.get()-x_old)/ a_diff);
        }
        else {
            return std::abs((x.get()-x_old).dot(a_diff)) / a_diff.squaredNorm();
        }
    };

    resetter();
    ad::autodiff(expr); 

    do {
        x_old = x.get();
        x.get() -= alpha * x.get_adj();

        a_old = x.get_adj();
        resetter();
        ad::autodiff(expr);

        alpha = new_alpha();
    } while ((diff(x.get(), x_old) > tol) && ++iter < max_iter);

    if (iter >= max_iter) return 1;
    return 0;
}
