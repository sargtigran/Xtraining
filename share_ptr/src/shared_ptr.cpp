
#include <iostream>

#include "shared_ptr.hpp"

struct A {
    void brr() {
        std::cout << "trtt" << std::endl;
    }
};


int shared_ptr_test ()
{
    A* a = new A;
    shared_ptr<A> ptr(a);
    ptr->brr();
    (*ptr).brr();
    


    return 0;
}
