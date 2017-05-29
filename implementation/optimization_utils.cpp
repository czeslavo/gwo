#include "optimization_utils.hpp"
#include <boost/algorithm/clamp.hpp>
#include <random>

namespace optimization
{
std::vector<std::vector<double>> get_initial_positions(double left_bound, double right_bound, int dimension, int number_of_agents)
{
    std::vector<std::vector<double>> positions(number_of_agents, std::vector<double>(dimension, 0.));
    for (auto &agent : positions)
        for (auto &coord : agent)
            coord = get_random(left_bound, right_bound);

    return positions;
}

double get_random(double left_bound, double right_bound)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(left_bound, right_bound);

    return dist(gen);
}

std::vector<std::vector<double>> &clip_positions(std::vector<std::vector<double>> &positions, double left_bound, double right_bound)
{
    for (auto &agent : positions)
        for (auto &coord : agent)
            coord = boost::algorithm::clamp(coord, left_bound, right_bound);

    return positions;
}
}