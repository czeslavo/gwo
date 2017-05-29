#include "grey_wolf_optimizer.hpp"
#include "benchmark_functions.hpp"
#include "optimization_utils.hpp"

#include <limits>
#include <iostream>
#include <exception>

namespace optimization
{
solution particle_swarm_optimization(function f, double left_bound, double right_bound, int dimension,
                                     int max_number_of_evaluations, int number_of_agents)
{
    constexpr double v_max = 6.;
    constexpr double c1 = 2.;
    constexpr double c2 = 2.;
    constexpr double w_max = 0.9;
    constexpr double w_min = 0.2;

    std::vector<double> global_best_pos(dimension, 0.);
    double global_best_score = std::numeric_limits<double>::infinity();
    
    std::vector<std::vector<double>> particles_best_pos(number_of_agents, 
                                                       std::vector<double>(dimension, 0.));
    std::vector<double> particles_best_score(number_of_agents, std::numeric_limits<double>::infinity());

    auto positions = get_initial_positions(left_bound, right_bound, dimension, number_of_agents);
    std::vector<std::vector<double>> velocities(number_of_agents, std::vector<double>(dimension, 0.));

    solution s{};
    int iteration{0};

    const int max_number_of_iterations{max_number_of_evaluations / number_of_agents};
    while (iteration++ < max_number_of_iterations)
    {
        clip_positions(positions, left_bound, right_bound);

        for (auto i = 0u; i < positions.size(); ++i)
        {
            double fitness = objective_function(f, positions[i]);

            if (particles_best_score[i] > fitness)
            {
                particles_best_score[i] = fitness;
                particles_best_pos[i] = positions[i];
            } 

            if (global_best_score > fitness)
            {
                global_best_score = fitness;
                global_best_pos = positions[i];
            }
        }

        double w = w_max - iteration * ((w_max - w_min) / max_number_of_iterations);

        for (auto i = 0u; i < number_of_agents; ++i)
            for (auto j = 0u; j < dimension; ++j)
            {
                // alpha
                double r1 = get_random(0., 1.);
                double r2 = get_random(0., 1.);

                velocities[i][j] =  w * velocities[i][j] + c1 * r1 * (particles_best_pos[i][j] - positions[i][j]) + c2 
                    * r2 * (global_best_pos[j] - positions[i][j]);

                if (velocities[i][j] > v_max)
                    velocities[i][j] = v_max;
                
                if (velocities[i][j] < -v_max)
                    velocities[i][j] = -v_max;

                positions[i][j] += velocities[i][j];
            }

        s.convergence.push_back(global_best_score);
        s.best = global_best_score;
    }

    return s;
}
} // optimization