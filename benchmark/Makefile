all: run

compile_optimizer:
	cd ../optimization && mkdir -p build && cd build && PYTHON_LIBRARY=/usr/lib/python2.7\
        PYTHON_INCLUDE_DIR=/usr/include/python2.7 cmake .. && make
	
prepare: clean compile_optimizer
	cp ../optimization/build/optimization.so .
	mkdir data/
	mkdir bests/

run: prepare
	python ./run.py

clean:
	rm -rf data/
	rm -rf bests/
