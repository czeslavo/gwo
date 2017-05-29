#!/usr/bin/python

from numpy import std
import optimization as op


num_of_evaluations = 100000
dim = 10
x_size_min = -100.0
x_size_max = 100.0
repetitions = 30

functions_map = {
	'bent_cigar': op.function.bent_cigar,
	'rosenbrock': op.function.rosenbrock,
	'rastrigin': op.function.rastrigin,
	'zakharov': op.function.zakharov
}

optimums_map = {
	'bent_cigar': 100.0,
	'rosenbrock': 400.0,
	'rastrigin': 500.0,
	'zakharov': 300.0
}

calculation_types_map = {
	'lin': op.calculation_type.lin,
	'exp': op.calculation_type.exp,
	'rand': op.calculation_type.rand
}

populations_proposed = [
	10,
	20,
	40
]

def save_function_error_value(func_name, filename, convergence_list, population):
	print filename
	with open('data/' + filename, 'w+') as f:
		for i in range(len(convergence_list)):
			evaluation_num = i * population
			f.write('%d\t%.10f\n' % (evaluation_num, convergence_list[i]))

def save_bests(best_list, filename):
	with open('bests/' + filename, 'w') as f:
		f.write("Lista: %s\n" % best_list)
		f.write("Best: %s\n" % min(best_list))
		f.write("Srednia: %.30f\n" % (sum(best_list)/float(len(best_list))))
		f.write("Odchyl: %.30f\n" % std(best_list))

# initialization
best_list_pso = {}
best_list_gwo = {}
for func_name in functions_map.keys(): # func name
	for population in populations_proposed: # population
		best_list_pso['pso_' + func_name + '_' + str(population)] = []
		for a in calculation_types_map.keys(): # a param
			for C in calculation_types_map.keys(): # C param
				best_list_gwo['gwo_' + func_name + '_' + a + '_' + C + '_' + str(population)] = []

# there should be loop for 30 iterations
for main_i in range(repetitions):
	for func_name, func_enum_value in functions_map.iteritems():
		for population in populations_proposed: # population
			# particle_swarm_opimization for each function
			pso = op.particle_swarm_optimization(func_enum_value, x_size_min, x_size_max, dim, num_of_evaluations, population)
			temp_name = 'pso_' + func_name + '_' + str(population)
			(best_list_pso[temp_name]).append(float(pso.best))
			print best_list_pso[temp_name]
			save_function_error_value(func_name, '%d_%s' % (main_i, temp_name), pso.convergence, population)

			for a_name, a in calculation_types_map.iteritems(): # a param
				for C_name, C in calculation_types_map.iteritems(): # C param
					# rodzaj_funkcji, a funct type, C func type
					gwo = op.grey_wolf_optimizer(func_enum_value, a, C, num_of_evaluations, population, x_size_min, x_size_max, dim)
					temp_name = 'gwo_' + func_name + '_' + a_name + '_' + C_name + '_' + str(population)
					(best_list_gwo[temp_name]).append(float(gwo.best))
					save_function_error_value(func_name, '%d_%s' % (main_i, temp_name), gwo.convergence, population)

for func_name in functions_map.keys(): # func name
	for population in populations_proposed: # population
		save_bests(best_list_pso['pso_' + func_name + '_' + str(population)], 'pso_' + func_name + '_' + str(population))
		for a in calculation_types_map.keys(): # a param
			for C in calculation_types_map.keys(): # C param
				save_bests(best_list_gwo['gwo_' + func_name + '_' + a + '_' + C + '_' + str(population)], 
					'gwo_' + func_name + '_' + a + '_' + C + '_' + str(population))