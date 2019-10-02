
#include <iostream>

#include "shared_ptr.hpp"

struct A {
    void brr() {
        std::cout << "trtt" << std::endl;
    }
    ~A()
    {
        std::cout << "MERAAAAAAAAAAAAA" << std::endl;
    }
};


int shared_ptr_test ()
{
    A* a = new A;
    {
        shared_ptr<A> ptr(a);
        shared_ptr<A> ptr1(a);
        shared_ptr<A> ptr2(a);
        shared_ptr<A> ptr3(a);
        ptr->brr();
        (*ptr).brr();
    }


    return 0;
}
