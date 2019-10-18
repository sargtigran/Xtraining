
#include <iostream>

#include "shared_ptr.hpp"

struct A {
    A() {
        std::cout << "CONSTRUCTED: " << this << std::endl;
    }
    int aaa = 45;
    void brr() {
        std::cout << "trtt" << std::endl;
    }
    ~A()
    {
        std::cout << "DESTRUCTED: " << this << std::endl;
        aaa = -1;
    }
};

void test_explicit(shared_ptr<A> sp)
{
    std::cout << sp.use_count() << std::endl;
}

int shared_ptr_test ()
{
    {

        //shared_ptr<A> ptr(new A);
        //shared_ptr<A> ptr1 = ptr;
        //shared_ptr<A> ptr2 = ptr;
        //{ 
        //    shared_ptr<A> ptr3 = ptr2;
        //}
        //ptr->brr();
        //(*ptr).brr();
        //test_explicit(ptr);
        A* pp = new A;
        test_explicit(pp);
        //(*pp).aaa = 123;
        std::cout << pp->aaa << std::endl;
        
    }

    
    return 0;
}


