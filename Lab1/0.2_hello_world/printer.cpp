#include "printer.h"

void printer(const char* text, const int N)
{
    std::cout << "Hello, ";

    for(int i = 0; i < N; i++)
    {
        std::cout << text;
        if (i < N-1)
            std::cout << " ";
        else
            std::cout << "!\n";
    }
}
