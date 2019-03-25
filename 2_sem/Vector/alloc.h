#include <limits>
#include <stdlib.h>

template <typename T>
class MyAlloc
{
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef std::size_t size_type;

        MyAlloc () {}
        MyAlloc (const MyAlloc &) {}
        template <class U>
        MyAlloc (const MyAlloc <U> &) {}
        ~MyAlloc (){}

        template <typename U>                                                  //// rebind allocator to type U
        struct rebind
        {typedef MyAlloc <U> other;};

        pointer allocate (size_type num)                                    //// alloc but don't init num el of type T
        {
            return static_cast <pointer> (calloc (num, sizeof (value_type)));
        }
        void deallocate (pointer ptr, size_type num) {free (ptr);}      //// deallocate storage p of deleted elements
        void construct (pointer ptr, const T& value) {new (ptr) T (value);} //// init mem with placement new
        void destroy (pointer ptr) { ptr -> ~T ();}
        pointer adress (reference value) const {return &value;}
        const_pointer adress (const_reference value) const {return &value;}
        size_type max_size () const
        {
            return std::numeric_limits <size_type>::max () / sizeof (T);
        }
                                                                                    //// return that all spec of this alloc are interchangeable
        template <class T2>
        bool operator == (const MyAlloc<T2> &) const
        {return true;}
        template <class T2>
        bool operator != (const MyAlloc<T2> &) const
        {return false;}
};
