#include "benchmark_functions.hpp"

#include <boost/python.hpp>
#include <cmath>
#include <numeric>

namespace optimization
{

namespace
{
template <typename Type>
std::vector<Type> list_to_vector(const boost::python::list &l)
{
    std::vector<Type> out(len(l));
    for (auto i = 0u; i < len(l); ++i)
        out.emplace_back(boost::python::extract<Type>(l[i]));

    return out;
}
}

double bent_cigar(const std::vector<double> &x)
{
    return std::pow(x[0], 2) +
           std::pow(10, 6) * std::accumulate(std::next(x.begin()), x.end(), 0., [](double acc, double el) {
               return acc + std::pow(el, 2);
           });
}

double bent_cigar_pywrapper(const boost::python::list &x)
{
    return bent_cigar(list_to_vector<double>(x));
}

double rosenbrock(const std::vector<double> &x)
{
    double result = 0;

    for (auto i = 0u; i < x.size() - 1; ++i)
        result += 100 * std::pow(std::pow(x[i], 2) - std::pow(x[i + 1], 2), 2) + std::pow(x[i] - 1, 2);

    return result;
}

double rosenbrock_pywrapper(const boost::python::list &x)
{
    return rosenbrock(list_to_vector<double>(x));
}

double rastrigin(const std::vector<double> &x)
{
    return std::accumulate(x.begin(), x.end(), 0., [](double acc, double el) {
        return acc + std::pow(el, 2) - 10. * std::cos(2 * std::acos(-1) * el) + 10.;
    });
}

double rastrigin_pywrapper(const boost::python::list &x)
{
    return rastrigin(list_to_vector<double>(x));
}

double zakharov(const std::vector<double> &x)
{
    const double by_half = std::accumulate(x.begin(), x.end(), 0., [](double acc, double el) {
        return el * 0.5;
    });

    return std::accumulate(x.begin(), x.end(), 0., [](double acc, double el) {
               return acc + std::pow(el, 2);
           }) +
           std::pow(by_half, 2.) + std::pow(by_half, 4.);
}

double zakharov_pywrapper(const boost::python::list &x)
{
    return zakharov(list_to_vector<double>(x));
}

double objective_function(function f, const std::vector<double> &x)
{
    switch (f)
    {
    case function::bent_cigar:
        return bent_cigar(x);
    case function::rosenbrock:
        return rosenbrock(x);
    case function::rastrigin:
        return rastrigin(x);
    case function::zakharov:
        return zakharov(x);
    }

    throw std::runtime_error("Wrong enum value for function");
}

} // optimization
