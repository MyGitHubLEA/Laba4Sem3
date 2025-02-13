#include "Route.h"
#include <iostream>
#include <cassert>

void testDefaultConstructor() 
{
    Route<int> route;
    assert(route.GetLength() == 0);
    std::cout << "test Default Constructor passed" << std::endl;
}

void testPrepend() 
{
    Route<int> route;
    route.Prepend(1);
    assert(route.GetLength() == 1);
    assert(route.Get(0) == 1);

    route.Prepend(2);
    assert(route.GetLength() == 2);
    assert(route.Get(0) == 2);
    assert(route.Get(1) == 1);
    std::cout << "test Prepend passed" << std::endl;
}

void testAdd() 
{
    Route<int> route;
    route.Add(1);
    assert(route.GetLength() == 1);
    assert(route.Get(0) == 1);

    route.Add(2);
    assert(route.GetLength() == 2);
    assert(route.Get(0) == 1);
    assert(route.Get(1) == 2);
    std::cout << "test Add passed" << std::endl;
}

void testGet() 
{
    Route<int> route;
    route.Add(10);
    route.Add(20);
    route.Add(30);

    assert(route.Get(0) == 10);
    assert(route.Get(1) == 20);
    assert(route.Get(2) == 30);
    std::cout << "test Get passed" << std::endl;
}

void testGetLength() 
{
    Route<int> route;
    assert(route.GetLength() == 0);

    route.Add(1);
    assert(route.GetLength() == 1);

    route.Add(2);
    route.Add(3);
    assert(route.GetLength() == 3);
    std::cout << "test GetLength passed" << std::endl;
}
