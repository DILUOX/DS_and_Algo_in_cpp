#include "stack.h"
#include <random>
#include <time.h>
#include <iostream>
#include <iomanip>

int main()
{
    srand(time(0));

    clock_t start, end;
    start = clock();

    int randint;
    stack<float> *s = new stack<float>();

    const int stacksize = 2000000;
    std::cout << "Initializing stack with " << stacksize << " elements" << '\n';

    for (int i = 0; i <= stacksize; i++)
    {
        randint = rand() % 20000000;
        s->push(randint);
    }
    // s->print();
    std::cout << "Deleting stack content" << '\n';
    s->empty();
    s->print();

    // unsync the I/O of C and C++.
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << time_taken << std::setprecision(5);
    std::cout << " sec " << '\n';

    delete s;
    s = nullptr;

    return 0;
}
