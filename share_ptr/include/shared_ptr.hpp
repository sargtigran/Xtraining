
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
            : count(nullptr)
            , obj(nullptr)
        {}

        shared_ptr(std::nulptr_t) noexcept 
            : count(nullptr)
            , obj(nullptr)
        {
        }

        explicit shared_ptr(T* other) 
        {
            if (other == nullptr) return;

            if (other == obj) {
                (*count)++;
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
            : obj(other.obj)
            , count(other.count)
        {
            if (count) { (*count)++; }
        }

        shared_ptr& operator=(const shared_ptr& other) noexcept
        {
            if (obj == other.obj) { return; }
            reset();
            obj = other.obj;
            count = other.count;
            if (count) { (*count)++; }
        }
        
        shared_ptr(shared_ptr&& other) noexcept
        {
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
