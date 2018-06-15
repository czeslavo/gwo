#include "grey_wolf_optimizer.hpp"
#include "benchmark_functions.hpp"
#include "optimization_utils.hpp"

#include <limits>
#include <iostream>
#include <exception>
#include <cmath>

namespace optimization
{

double calculate_a(calculation_type type, int iteration, int max_number_of_iterations)
{
    switch (type)
    {
    case calculation_type::lin:
        return 2 - iteration * (2. / static_cast<double>(max_number_of_iterations));
    case calculation_type::exp:
        return std::exp(-static_cast<float>(iteration) / static_cast<float>(max_number_of_iterations));
    case calculation_type::rand:
        return get_random(0., 1.) * 2.;
    }
    throw std::runtime_error("Not supported type of a calculation");
}

double calculate_c(calculation_type type, float r1, int iteration, int max_number_of_iterations)
{
    switch (type)
    {
    case calculation_type::lin:
        return iteration * (2. / static_cast<double>(max_number_of_iterations));
    case calculation_type::exp:
        return std::exp(static_cast<float>(iteration) / static_cast<float>(max_number_of_iterations));
    case calculation_type::rand:
        return r1 * 2.;
    }
    throw std::runtime_error("Not supported type of c calculation");
}

solution grey_wolf_optimizer(function f, calculation_type calc_type_a, calculation_type calc_type_c, 
                             int max_number_of_evaluations, int number_of_agents, double left_bound, 
                             double right_bound, int dimension)
{
    std::vector<double> alpha_pos(dimension, 0.);
    double alpha_score = std::numeric_limits<double>::infinity();

    std::vector<double> beta_pos(dimension, 0.);
    double beta_score = std::numeric_limits<double>::infinity();

    std::vector<double> delta_pos(dimension, 0.);
    double delta_score = std::numeric_limits<double>::infinity();

    auto positions = get_initial_positions(left_bound, right_bound, dimension, number_of_agents);

    solution s{};
    int iteration{0};

    const int max_number_of_iterations{max_number_of_evaluations / number_of_agents};
    while (iteration++ < max_number_of_iterations)
    {
        clip_positions(positions, left_bound, right_bound);

        for (auto &agent : positions)
        {
            double fitness = objective_function(f, agent);

            if (fitness < alpha_score)
            {
                alpha_score = fitness;
                alpha_pos = agent;
            }

            if (fitness > alpha_score and fitness < beta_score)
            {
                beta_score = fitness;
                beta_pos = agent;
            }

            if (fitness > alpha_score and fitness > beta_score and fitness < delta_score)
            {
                delta_score = fitness;
                delta_pos = agent;
            }
        }

        double a = calculate_a(calc_type_a, iteration, max_number_of_iterations);

        for (auto &agent : positions)
            for (auto j = 0u; j < agent.size(); ++j)
            {
                // alpha
                double r1 = get_random(0., 1.);
                double r2 = get_random(0., 1.);

                double A1 = 2. * a * r1 - a;
                double C1 = calculate_c(calc_type_c, r2, iteration, max_number_of_iterations);

                const double D_alpha = std::abs(C1 * alpha_pos[j] - agent[j]);
                const double X1 = alpha_pos[j] - A1 * D_alpha;

                // beta
                r1 = get_random(0., 1.);
                r2 = get_random(0., 1.);

                double A2 = 2. * a * r1 - a;
                double C2 = calculate_c(calc_type_c, r2, iteration, max_number_of_iterations);

                const double D_beta = std::abs(C2 * beta_pos[j] - agent[j]);
                const double X2 = beta_pos[j] - A2 * D_beta;

                // delta
                r1 = get_random(0., 1.);
                r2 = get_random(0., 1.);

                double A3 = 2. * a * r1 - a;
                double C3 = calculate_c(calc_type_c, r2, iteration, max_number_of_iterations);

                const double D_delta = std::abs(C3 * delta_pos[j] - agent[j]);
                const double X3 = delta_pos[j] - A3 * D_delta;

                agent[j] = (X1 + X2 + X3) / 3.;
            }

        s.convergence.push_back(alpha_score);
        s.best = alpha_score;
    }

    return s;
}
} // optimization
