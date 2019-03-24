#include <iostream>

template <class T>
class MyAlloc
{
    public:
        using T           value_type;
        using T*          pointer;
        using const T*    const_pointer;
        using T&          reference;
        using const T&    const_reference;
        using std::size_t size_type;
        ////using std::ptrdiff_t difference_type;

        template <class U>              //// rebind allocator to type U
        struct rebind
        {
            using MyAlloc <U> other;
        }

        MyAlloc () {}
        MyAlloc (const MyAlloc &) {}
        template <class U>
        MyAlloc (const MyAlloc <U> &) {}
        ~MyAlloc (){}

        pointer adress (reference value) const
        {
            return &value;
        }
        const_pointer adress (const_reference value) const
        {
            return &value;
        }
        // return maximum number of elements that can be allocated
        size_type max_size () const
        {
            return std::numeric_limits<std::size_t>::max () / sizeof (T);
        }
        // allocate but don't initialize num elements of type T
        pointer allocate (size_type num)
        {
            pointer ret = calloc (num, sizeof (value_type));
            return ret;
        }
        void construct (pointer ptr, const T& value)
        {
            // initialize memory with placement new
            new (ptr) T (value);
        }
        // destroy elements of initialized storage p
        void destroy (pointer ptr)
        {
            // destroy objects by calling their destructor
            p -> ~T ();
        }
        // deallocate storage p of deleted elements
        void deallocate (pointer ptr, size_type num = 0)
        {
            std::free (ptr);
        }
        // return that all specializations of this allocator are interchangeable
        template <class T2>
        bool operator == (const MyAlloc<T2> &) const
        {
            return true;
        }
        template <class T2>
        bool operator != (const MyAlloc<T2> &) const
        {
            return false;
        }
};
