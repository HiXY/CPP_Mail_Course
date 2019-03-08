#include <cstdlib>
#include <cassert>

template <typename T>
class Stack
{
	private:
		T *ptr_;
		size_t size_;
		int top_;
	public:
		Stack (size_t = 16);
		Stack (const Stack <T> &);
		~Stack ();

		void push (const T &);
		void pop ();
		const T &top () const;
		bool empty ();
		size_t size ();
		int capacity ();
		Stack &operator = (Stack <T> &);
};

template <typename T>
Stack <T>::Stack (size_t size) : size_ (size)
{
	ptr_ = new T[size];
	top_ = 0;
}
template <typename T>
Stack <T>::Stack (const Stack <T> &origin)
{

	ptr_ = new T[origin.size_];
	size_ = origin.size_;
	top_ = origin.top_;
	for (int i = 0; i < top_; i++)
		ptr_[i] = origin.ptr_[i];
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
	assert (top_ > 0 && "Stack is EMPTY!!!!\n");
	top_--;
}
template <typename T>
const T &Stack <T>::top () const
{
	assert (top_ > 0 && "Stack is EMPTY!!!!\n");
	return ptr_[top_ - 1];
}
template <typename T>
bool Stack <T>::empty ()
{
	return this -> top_ == 0;
}
template <typename T>
size_t Stack <T>::size ()
{
	return this -> size_;
}
template <typename T>
int Stack <T>::capacity ()
{
	return this -> top_;
}
template <typename T>
Stack <T> &Stack <T>::operator = (Stack <T> &stk)
{
	if (&stk == this)
		return *this;
	delete[] ptr_;
	size_ = stk.size_;
	ptr_ = new T[size_];
	top_ = stk.top_;
	for (int i = 0; i < top_; i++)
		ptr_[i] = stk.ptr_[i];
	return *this;
}
