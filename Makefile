all: rbgs

rbgs: rbgs.cpp
	g++ -std=c++17 -Wall -Wextra -Wshadow -Werror -fopenmp -O3 -DNDEBUG rbgs.cpp -o rbgs

