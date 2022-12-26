all: test clean

test: main.cpp
	clang++ -std=c++17 main.cpp -o main && ./main < sample_input.txt

clean: 
	rm -f main