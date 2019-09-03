
#ifndef __SHARED_PTR__
#define __SHARED_PTR__


template<typename T>
class shared_ptr
{
    
    private:
        int* count;
        T* obj;
    
    public:
        shared_ptr() noexcept
            : count(new int(1))
            , obj(nullptr)
        {
                        
        }

        explicit shared_ptr(T* other) 
        {
            if (other == obj) {
                *count++;
            } else {
                count = new int(1);
                obj = other;
            }
        }

        ~shared_ptr() 
        {
            reset();
        }

        shared_ptr(const shared_ptr& other) noexcept
        {
        }

        shared_ptr& operator=(const shared_ptr& other) noexcept
        {
        }
        
        
        shared_ptr(shared_ptr&& other) noexcept
        {
        }

        shared_ptr& operator=(shared_ptr&& other) noexcept
        {
        }


        reset() 
        {
            if (--count == 0) {
                delete obj;
                delete count;
            }
            obj = nullptr;
        }

        int use_count()
        {
            return *count;
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
            
        }


};

#endif // __SHARED_PTR__
