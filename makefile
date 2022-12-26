all: test run clean

test:
	clang++ -std=c++17 test_generator.cpp -o test && ./test > sample_input.txt

run: main.cpp
	clang++ -std=c++17 main.cpp -o main && ./main < sample_input.txt

clean: 
	rm -f main test