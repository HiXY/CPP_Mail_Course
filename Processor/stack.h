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
		const T &peek () const;
};
template <typename T> 
Stack <T>::Stack (size_t size) : size_ (size)
{
	ptr_ = new T[size];
	top_ = 0;
}
template <typename T> 
Stack <T>::Stack (const Stack <T> &origin) : size_ (origin.size_)
{
	ptr_ = new T[size_];
	top_ = origin.top_;
	for (int i = 0; i < top_; i++)
		ptr_[i] = origin.ptr_[i];
}
template <typename T>
Stack <T>::~Stack ()
{
	delete [] ptr_;
}
template <typename T>
void Stack <T>::push (const T &el)
{
	if (top_ == size_)
	{
		////std::cout << "resize" << std::endl;
		Stack tmp (*this);
		size_ *= 2;
		ptr_ = new T[size_];
		for (int i = 0; i < top_; i++)
			tmp.ptr_[i] = ptr_[i];
	}
	ptr_[top_++] = el;
}
template <typename T>
void Stack <T>::pop ()
{
	assert (top_ > 0 && "Stack is EMPTY!\n");
	ptr_[--top_];
	
}
template <typename T> 
const T &Stack <T>::peek () const
{
	assert (top_ > 0 && "Stack is EMPTY!\n");
	return ptr_[top_ - 1];
}
