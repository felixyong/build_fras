//main.cpp
#include <iostream>
#include "simplemath.h"

int main() {
    std::cout << "Hello, World!" << std::endl
			<< "My first project built with SCons!" << std::endl;
	double m, n;
	m = 10;
	n = cubic(m);
	std::cout << m << "^3 = " << n << std::endl;
    return 0;
}