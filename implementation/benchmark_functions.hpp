#pragma once

#include <boost/python/list.hpp>
#include <vector>

namespace optimization
{
enum class function
{
    bent_cigar,
    rosenbrock,
    rastrigin,
    zakharov
};

double bent_cigar(const std::vector<double> &x);
double bent_cigar_pywrapper(const boost::python::list &x);

double rosenbrock(const std::vector<double> &x);
double rosenbrock_pywrapper(const boost::python::list &x);

double rastrigin(const std::vector<double> &x);
double rastrigin_pywrapper(const boost::python::list &x);

double zakharov(const std::vector<double> &x);
double zakharov_pywrapper(const boost::python::list &x);

double objective_function(function f, const std::vector<double> &x);
} // optimization