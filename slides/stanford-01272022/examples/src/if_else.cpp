#include <fastad>
#include <iostream>

int main()
{
    using namespace ad;

    Var<double> x(0);
    auto expr = bind(if_else(x==0, cos(x), sin(x)/x));

    autodiff(expr);
    std::cout << "Esti: " << x.get_adj() << "\tActual: " << 0 << std::endl;

    x.get() = 0.0001;
    autodiff(expr);
    double actual = (x.get()*std::cos(x.get()) - std::sin(x.get())) / (x.get()*x.get());
    std::cout << "Esti: " << x.get_adj() << "\tActual: " << actual << std::endl;

    return 0;
}
