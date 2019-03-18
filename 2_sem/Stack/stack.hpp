#include <cstdlib>
#include <stdexcept>
#include <iostream>

template <typename T>
class Stack
{
	private:
		T *ptr_;
		size_t size_;
		int top_;
	public:
		explicit Stack (size_t = 16) noexcept;
		Stack (const Stack <T> &) noexcept;
		Stack (Stack <T> &&) noexcept;
		~Stack ();

		void push (const T &);
		void pop ();
		const T &top () const;
		bool empty () const;
		size_t size () const;
		int capacity () const;
		Stack &operator = (const Stack <T> &) noexcept;
		Stack &operator = (Stack <T> &&);
};

template <typename T>
Stack <T>::Stack (size_t size) noexcept : size_ (size)
{
	ptr_ = new T[size];
	top_ = 0;
}
template <typename T>
Stack <T>::Stack (const Stack <T> &origin) noexcept
{

	ptr_ = new T[origin.size_];
	size_ = origin.size_;
	top_ = origin.top_;

	for (int i = 0; i < top_; i++)
		ptr_[i] = origin.ptr_[i];
	////std::cout << "CNSTRCTR WTH CPY" << std::endl;
}
template <typename T>
Stack <T>::Stack (Stack <T> &&origin) noexcept : ptr_ (std::move (origin.ptr_)), size_(origin.size_), top_(origin.top_)
{
	origin.ptr_ = nullptr;
	origin.size_ = 0;
	origin.top_ = 0;
	////std::cout << "CNSTRCTR WTHT CPY" << std::endl;
}
template <typename T>
Stack <T>::~Stack ()
{
	delete[] ptr_;
}
template <typename T>
void Stack <T>::push (const T &el)
{
	if (top_ == size_)
	{
		////std::cout << "Resize" << std::endl;
		Stack tmp (*this);
		size_ *= 2;
		ptr_ = new T[size_];
		for (int i = 0; i < top_; i++)
			ptr_[i] = tmp.ptr_[i];
	}
	ptr_[top_++] = el;
}
template <typename T>
void Stack <T>::pop ()
{
	if (top_ <= 0)
		throw std::out_of_range ("CAN'T POP FROM STACK!!!! IT'S EMPTY!!!!");
	top_--;
}
template <typename T>
const T &Stack <T>::top () const
{
	if (top_ <= 0)
		throw std::out_of_range ("NO TOP ELEMENT!!!! STACK IS EMPTY!!!!");
	return ptr_[top_ - 1];
}
template <typename T>
bool Stack <T>::empty () const
{
	return this -> top_ == 0;
}
template <typename T>
size_t Stack <T>::size () const
{
	return this -> size_;
}
template <typename T>
int Stack <T>::capacity () const
{
	return this -> top_;
}
template <typename T>
Stack <T> &Stack <T>::operator = (const Stack <T> &stk) noexcept
{
	if (&stk == this)
		return *this;

	delete[] ptr_;
	size_ = stk.size_;
	ptr_ = new T[size_];
	top_ = stk.top_;

	for (int i = 0; i < top_; i++)
		ptr_[i] = stk.ptr_[i];
	////std::cout << "= WTH CPY" << std::endl;
	return *this;
}
template <typename T>
Stack <T> &Stack <T>::operator = (Stack <T> &&stk)
{
	if (this == &stk)
		throw std::logic_error ("MOVING YOURSELF!!!!");

	ptr_ = nullptr;
	ptr_ = std::move (stk.ptr_);
	size_ = stk.size_;
	top_ = stk.top_;

	stk.ptr_ = nullptr;
	stk.size_ = 0;
	stk.top_ = 0;
	////std::cout << "= WTHT CPY" << std::endl;
	return *this;
}
