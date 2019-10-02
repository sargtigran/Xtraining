
#ifndef __SHARED_PTR__
#define __SHARED_PTR__

#include <cstddef>
#include <iostream>

template<typename T>
class shared_ptr
{
    
    private:
        int* count;
        T* obj;
    
    public:

        shared_ptr() noexcept
            : count(nullptr)
            , obj(nullptr)
        {}

        shared_ptr(std::nullptr_t) noexcept 
            : count(nullptr)
            , obj(nullptr)
        {
        }

        explicit shared_ptr(T*& other) 
        {
            if (other == nullptr) return;

            std::cout << "Constructor " << other << " == " << obj << std::endl;
            if (other == obj) {
                (*count)++;
                std::cout << "inicrease count: " << (*count) << std::endl;
            } else {
                count = new int(1);
                std::cout << "New object: " << (*count) << std::endl;
                obj = other;
            }
        }

        ~shared_ptr() 
        {
            std::cout << "shared_ptr destructor:" << *count << std::endl;
            reset();
        }

        shared_ptr(const shared_ptr& other) noexcept
            : obj(other.obj)
            , count(other.count)
        {
            if (count) { (*count)++; }
        }

        shared_ptr& operator=(const shared_ptr& other) noexcept
        {
            if (obj != other.obj) {
                reset();
                obj = other.obj;
                count = other.count;
                if (count) { (*count)++; }
            }
            return *this;
        }
        
        shared_ptr(shared_ptr&& other) noexcept
            : obj(other.obj)
            , count(other.count)
        {
            other.obj = nullptr;
            other.count = nullptr;
        }

        shared_ptr& operator=(shared_ptr&& other) noexcept
        {
        }

        void reset() 
        {
            if (--(*count) == 0) {
                delete obj;
                delete count;
                count = nullptr;
            }
            obj = nullptr;
        }

        int use_count()
        {
            if (count) { return *count; }
            return 0;
        }

        T* get()
        {
            return obj;
        }

        void reset(T* ptr) 
        {
            reset();
            count = new int(1);
            obj = ptr;
        }

        T& operator *() const noexcept
        {
            if (obj != nullptr) return *obj;
        }

        T* operator ->() const noexcept
        {
            return obj;       
        }

};

#endif // __SHARED_PTR__
