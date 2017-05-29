cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(Boost COMPONENTS python)

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

python_add_module(optimization grey_wolf_optimizer.cpp 
                               benchmark_functions.cpp 
                               particle_swarm_optimization.cpp
                               optimization_utils.cpp
                               optimization_pymodule.cpp)

target_link_libraries(optimization ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
