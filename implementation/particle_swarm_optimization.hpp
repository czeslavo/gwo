#pragma once

namespace optimization
{

solution particle_swarm_optimization(function f, double left_bound, double right_bound, int dimension,
                                     int max_number_of_evaluations, int number_of_agents);
}