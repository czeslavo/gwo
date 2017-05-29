#pragma once

#include <vector>

namespace optimization
{
std::vector<std::vector<double>> get_initial_positions(double left_bound, double right_bound, int dimension, int number_of_agents);

struct solution
{
    std::vector<double> convergence;
    int time_of_execution;
    double best;
};

double get_random(double left_bound, double right_bound);
std::vector<std::vector<double>> &clip_positions(std::vector<std::vector<double>> &positions, double left_bound, double right_bound);

}