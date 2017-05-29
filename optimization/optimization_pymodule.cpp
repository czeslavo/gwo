#include "grey_wolf_optimizer.hpp"
#include "particle_swarm_optimization.hpp"
#include "benchmark_functions.hpp"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

BOOST_PYTHON_MODULE(optimization)
{
    using namespace boost::python;

    class_<std::vector<double>>("vector_double")
        .def(vector_indexing_suite<std::vector<double>>());

    enum_<optimization::function>("function")
        .value("bent_cigar", optimization::function::bent_cigar)
        .value("rosenbrock", optimization::function::rosenbrock)
        .value("rastrigin", optimization::function::rastrigin)
        .value("zakharov", optimization::function::zakharov);
    
    class_<optimization::solution>("solution")
        .def_readonly("convergence", &optimization::solution::convergence)
        .def_readonly("time_of_execution", &optimization::solution::time_of_execution)
        .def_readonly("best", &optimization::solution::best);

    def("bent_cigar", &optimization::bent_cigar_pywrapper);
    def("rosenbrock", &optimization::rosenbrock_pywrapper);
    def("rastrigin", &optimization::rastrigin_pywrapper);
    def("zakharov", &optimization::zakharov_pywrapper);

    enum_<optimization::calculation_type>("calculation_type")
        .value("lin", optimization::calculation_type::lin)
        .value("exp", optimization::calculation_type::exp)
        .value("rand", optimization::calculation_type::rand);

    def("grey_wolf_optimizer", &optimization::grey_wolf_optimizer);
    def("particle_swarm_optimization", &optimization::particle_swarm_optimization);
}