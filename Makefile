main: file.cpp
	g++ -std=c++11 -O3 -g -Wall file.cpp -lm -o main

random: random_k.cpp
	g++ -O3 -Wall -o random_k random_k.cpp -lm
