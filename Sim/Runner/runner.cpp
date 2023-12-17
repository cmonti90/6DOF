#include "runner.h"

#include <iostream>

int main()
{
        std::cout << "Starting Simulation" << std::endl << std::endl;

        sim_.go();

        return 1;
}