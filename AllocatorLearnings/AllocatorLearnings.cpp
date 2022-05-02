

#include <iostream>
#include <Windows.h>

#include "Pool.h"

struct A_t
{
    int A = 0x89ABCDEF;
    char B = 0xAB;

    A_t() { std::cout << "I'm borned" << std::endl; }
    ~A_t() { std::cout << "I'm died" << std::endl; }
};

Pool_t<A_t, 3> MyPool;

int main()
{
    MyPool.Init();

    A_t* first = MyPool.Create();
    A_t* second = MyPool.Create();
    A_t* third = MyPool.Create();

    first->A = 0xAAAAAAAA;
    first->B = 0xFF;

    MyPool.Destroy(first);


    while (true)
    {
        Sleep(500);
    }
}
