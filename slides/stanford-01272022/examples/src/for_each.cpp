#include <fastad>
#include "counting_iterator.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    using namespace ad;

    size_t n = 0;
    if (argc == 2) {
        ++argv;
        n = std::stoi(*argv++);
    }
    else {
        std::cerr << "./a.out n" << std::endl;
        return 1;
    }

    Var<double, vec> x(n);
    Var<double> s;
    auto expr = ad::bind((
            for_each(util::counting_iterator<>(0),
                     util::counting_iterator<>(n),
                     [&](int i) { return (s += static_cast<double>(i)*x[i]); }),
            s
    ));

    autodiff(expr);
    std::cout << "Esti: " << x.get_adj() 
        << "\nActual: " << Eigen::VectorXd::LinSpaced(n, 0, n-1) << std::endl;

    return 0;
}
