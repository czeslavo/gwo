# __Grey Wolf Optimizer (GWO)__ C++ implementation with Python bindings

## Structure
- _optimization/_ - implementation and python bindings
- _benchmark/_ - python code using the bindings, producing data for benchmarking
- _parpers/_ - original paper on GWO

## Usage
You can go directly to `benchmark` directory and execute:
``
make run
``

It will compile `optimization.so` shared library (with python bindings) and run python script, 
which imports the aforementioned library (module).
Results of the execution will be present in `data/` and `bests/` directories.


