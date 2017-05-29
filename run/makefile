all: run

compile_optimizer:
	cd ../implementation
	mkdir build
	cd build
	cmake ..
	make

prepare: clean
	cp ../implementation/build/optimization.so .
	mkdir data/
	mkdir bests/

run: prepare
	./run.py

clean:
	rm -rf data/
	rm -rf bests/
