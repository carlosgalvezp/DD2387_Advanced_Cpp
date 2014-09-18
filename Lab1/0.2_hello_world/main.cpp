#include "printer.h"
#include <cstdlib>

int main(int argc, char* argv[])
{
    char* text; // text to print
    int N;      // number of repetitions

    // *** Check input parameters
    switch (argc)
    {
        case 1: // No text, no N given
            text = (char*)("world");
            N = 1;
            break;

        case 2: // Text given
            text = argv[1];
            N = 1;
            break;

        case 3: // Text and number given
            // Check correct N
            text = argv[1];
            N = std::atoi(argv[2]);
            if (N <= 0)
            {
                std::cerr << "2nd argument must be an integral greater than zero!\n";
                return -1;
            }
            break;

        default: // More than 2 arguments
            std::cerr << "Too many arguments!\n";
            return -1;
    }

    // *** Print if everything went fine
    printer(text, N);
}
