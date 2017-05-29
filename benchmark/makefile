all: run

compile_optimizer:
	cd ../optimization
	mkdir -p build
	cd build
	cmake ..
	make

prepare: clean compile_optimizer
	cp ../optimization/build/optimization.so .
	mkdir data/
	mkdir bests/

run: prepare
	./run.py

clean:
	rm -rf data/
	rm -rf bests/
