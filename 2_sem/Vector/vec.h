#include "alloc.h"
#include <memory>

template <typename T, typename Allocator = MyAlloc <T> >
class MyVector
{
	public:
		typedef Allocator   allocator_type;
		typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef std::size_t size_type;

		explicit MyVector (const allocator_type &alloc) noexcept;
		MyVector (size_type count, const T &value, const allocator_type &alloc);
		MyVector (size_type count, const allocator_type &alloc);
		MyVector (const MyVector &other, const allocator_type &alloc);
		MyVector (MyVector &&other, const allocator_type &alloc) noexcept;
		~MyVector () noexcept;

		pointer 		begin () noexcept;
		const_pointer 	begin () const noexcept;
		pointer 		end () noexcept;
		const_pointer 	end () const noexcept;
		reference 		at (size_type index);
		const_reference at (size_type index) const;
		reference       operator [] (size_type index);
		const_reference operator [] (size_type index) const;
		reference 		front () noexcept;
		const_reference front () const noexcept;
		reference 		back () noexcept;
		const_reference back () const noexcept;
		size_type size () const noexcept;
		size_type max_size () const noexcept;
		size_type capacity () const noexcept;
		bool empty () const noexcept;
		void assign (size_type count, const T &value);
		pointer insert (const_pointer pos, const T &value);
		pointer insert (const_pointer pos, T &&value);
		pointer erase (const_pointer pos);
		pointer erase (const_pointer first, const_pointer last);
		void push_back (const T &value);
		void push_back (T &&value);
		void pop_back ();
		void resize (size_type count);
		void reserve (size_type new_cap);
		void clear () noexcept;
		/*
		!!!!MyVector &operator = (const MyVector &other);
		!!!!MyVector &operator = (MyVector &&other);
		*/
	private:
		pointer begin_, end_, end_of_storage_;

		pointer allocate (size_type count)
		{
			return MyAlloc<T>::allocate (count);
		}

		void deallocate () noexcept
		{
			deallocate (begin_, capacity ());
		}

		void deallocate (pointer begin, size_type count) noexcept
		{
			if (begin != nullptr) MyAlloc<T>::deallocate (begin, count);
		}
};

template <typename T, typename Allocator>
MyVector <T, Allocator>::MyVector (const typename MyVector <T, Allocator>::allocator_type &alloc) noexcept : Allocator (alloc),
begin_ (nullptr), end_ (nullptr), end_of_storage_ (nullptr)
{}
template <typename T, typename Allocator>
MyVector <T, Allocator>::MyVector (typename MyVector <T, Allocator>::size_type count, const T &value, const typename MyVector <T, Allocator>::allocator_type &alloc) :
Allocator (alloc), begin_ (allocate (count)), end_ (begin_ + count), end_of_storage_ (end_)
{
	std::uninitialized_fill_n <pointer, typename MyVector <T, Allocator>::size_type>(begin_, count, value);
}
template <typename T, typename Allocator>
MyVector <T, Allocator>::MyVector (typename MyVector <T, Allocator>::size_type count, const typename MyVector <T, Allocator>::allocator_type &alloc) :
Allocator (alloc), begin_ (allocate (count)), end_ (begin_ + count), end_of_storage_ (end_)
{}
template <typename T, typename Allocator>
MyVector <T, Allocator>::MyVector (const MyVector <T, Allocator> &other, const typename MyVector <T, Allocator>::allocator_type &alloc) : Allocator (alloc),
begin_ (allocate (other.size ())), end_ (begin_ + other.size ()), end_of_storage_(end_)
{
	memcpy (begin_, other.begin_, other.size () * sizeof (pointer));
}
template <typename T, typename Allocator>
MyVector <T, Allocator>::MyVector (MyVector &&other, const typename MyVector <T, Allocator>::allocator_type &alloc) noexcept : Allocator (alloc),
begin_ (other.begin_), end_ (other.end_), end_of_storage_ (other.end_of_storage_)
{
	other.begin_ = nullptr;
	other.end_ = nullptr;
	other.end_of_storage_ = nullptr;
}
template <typename T, typename Allocator>
MyVector <T, Allocator>::~MyVector () noexcept
{
	deallocate ();
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::begin () noexcept {return begin_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_pointer MyVector <T, Allocator>::begin () const noexcept {return begin_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::end () noexcept {return end_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_pointer MyVector <T, Allocator>::end () const noexcept {return end_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::reference MyVector <T, Allocator>::at (typename MyVector <T, Allocator>::size_type index)
{
	if (index >= size ())
		throw std::out_of_range ("Access to element in vector after end\n");
	return begin_[index];
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_reference MyVector <T, Allocator>::at (typename MyVector <T, Allocator>::size_type index) const
{
	if (index >= size ())
		throw std::out_of_range ("Access to element in vector after end\n");
	return begin_[index];
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::reference MyVector <T, Allocator>::operator [] (typename MyVector <T, Allocator>::size_type index) {return begin_[index];}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_reference MyVector <T, Allocator>::operator [] (typename MyVector <T, Allocator>::size_type index) const {return begin_[index];}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::reference MyVector <T, Allocator>::front () noexcept {return begin_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_reference MyVector <T, Allocator>::front () const noexcept {return begin_;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::reference MyVector <T, Allocator>::back () noexcept {return end_ - 1;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::const_reference MyVector <T, Allocator>::back () const noexcept {return end_ - 1;}

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::size_type MyVector <T, Allocator>::size () const noexcept { return end_ - begin_; }

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::size_type MyVector <T, Allocator>::max_size () const noexcept { return Allocator::max_size (); }

template <typename T, typename Allocator>
typename MyVector <T, Allocator>::size_type MyVector <T, Allocator>::capacity() const noexcept { return end_of_storage_ - begin_; }

template <typename T, typename Allocator>
bool MyVector <T, Allocator>::empty () const noexcept { return begin_ == end_; }

template <typename T, typename Allocator>
void MyVector <T, Allocator>::assign (typename MyVector <T, Allocator>::size_type count, const T &value)
{
	if (count > capacity ())
	{
		pointer new_storage = allocate (count);
		deallocate ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + count;
	}
	end_ = begin_ + count;
	std::uninitialized_fill_n <pointer, typename MyVector <T, Allocator>::size_type> (begin_, count, value);
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::insert (typename MyVector <T, Allocator>::const_pointer pos, const T &value)
{
	if (end_ == end_of_storage_)
	{
		typename MyVector <T, Allocator>::size_type index = pos - begin_;
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, index * sizeof (value_type));
		memcpy (new_storage + index + 1, begin_ + index, (size () - index) * sizeof(value_type));
		deallocate ();
		end_ = new_storage + size () + 1;
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
		pos = begin_ + index;
	}
	else
	{
		memmove (const_cast <pointer> (pos) + 1, pos, (end_ - pos) * sizeof (value_type));
		end_++;
	}
	*const_cast <pointer> (pos) = value;
	return const_cast <pointer> (pos);
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::insert (typename MyVector <T, Allocator>::const_pointer pos, T &&value)
{
	if (end_ == end_of_storage_)
	{
		typename MyVector <T, Allocator>::size_type index = pos - begin_;
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, index * sizeof (value_type));
		memcpy (new_storage + index + 1, begin_ + index, (size () - index) * sizeof(value_type));
		deallocate ();
		end_ = new_storage + size () + 1;
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
		pos = begin_ + index;
	}
	else
	{
		memmove (const_cast <pointer> (pos) + 1, pos, (end_ - pos) * sizeof (value_type));
		end_++;
	}
	*const_cast <pointer> (pos) = std::move (value);
	return const_cast <pointer> (pos);
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::erase (typename MyVector <T, Allocator>::const_pointer pos)
{
	end_--;
	memmove (const_cast <pointer> (pos), pos + 1, (end_ - pos) * sizeof (value_type));
	return const_cast <pointer> (pos);
}
template <typename T, typename Allocator>
typename MyVector <T, Allocator>::pointer MyVector <T, Allocator>::erase (typename MyVector <T, Allocator>::const_pointer first, typename MyVector <T, Allocator>::const_pointer last)
{
	typename MyVector <T, Allocator>::size_type count = last - first;
	end_-= count;
	memmove (const_cast <pointer> (first), first + count, (end_ - first) * sizeof (value_type));    /// std copy
	return const_cast <pointer> (first);
}
template <typename T, typename Allocator>
void MyVector <T, Allocator>::push_back (const T &value)
{
	*end_ = insert (end_, value);
	/*
	if (end_ == end_of_storage_)
	{
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, size () * sizeof (value_type));
		deallocate ();
		end_ = new_storage + size ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
	}
	*end_ = value;
	end_++;
	*/
}
template <typename T, typename Allocator>
void MyVector <T, Allocator>::push_back (T &&value)
{
	*end_ = insert (end_, value);
	/*
	if (end_ == end_of_storage_)
	{
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, size () * sizeof (value_type));
		deallocate ();
		end_ = new_storage + size ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
	}
	*end_ = std::move (value);
	end_++;
	*/
}
template <typename T, typename Allocator>
void MyVector <T, Allocator>::pop_back () {end_--;}

template <typename T, typename Allocator>
void MyVector <T, Allocator>::resize (typename MyVector <T, Allocator>::size_type count)
{
	if (capacity () < count)
	{
		typename MyVector <T, Allocator>::size_type new_size = size () + count;
		pointer new_storage = allocate (new_size);
		memcpy (new_storage, begin_, size() * sizeof(value_type));
		deallocate ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + new_size;
	}
	end_ = begin_ + count;
}
template <typename T, typename Allocator>
void MyVector <T, Allocator>::reserve (typename MyVector <T, Allocator>::size_type new_cap)
{
	if (capacity () < new_cap)
	{
		const size_t cur_size = size ();
		pointer new_storage = allocate (new_cap);
		memcpy (new_storage, begin_, cur_size * sizeof (value_type));
		deallocate ();
		begin_ = new_storage;
		end_ = new_storage + cur_size;
		end_of_storage_ = begin_ + new_cap;
	}
}
template <typename T, typename Allocator>
void MyVector <T, Allocator>::clear () noexcept {end_ = begin_;}
