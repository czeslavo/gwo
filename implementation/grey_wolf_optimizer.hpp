#pragma once

#include "optimization_utils.hpp"

namespace optimization
{

enum class function;

enum class calculation_type
{
    lin,
    exp,
    rand
};

solution grey_wolf_optimizer(function f, calculation_type, calculation_type, int max_number_of_evaluations,
                             int number_of_agents, double left_bound, double right_bound, 
                             int dimension);

} // optimization