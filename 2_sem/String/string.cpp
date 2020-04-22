#include "string.hpp"
#include <string.h>

String::String () : capacity_ (0), data_ (nullptr), size_ (0)
{}
String::String (String::size_type sz, String::CharT dt) : capacity_ (sz + 1), data_ (new CharT[capacity_]), size_ (sz)
{
	for (size_t i = 0; i < sz; ++i)
		data_[i] = dt;
	data_[size_] = '\0';
}
String::String (String const &str) : capacity_ (str.capacity_), data_ (nullptr), size_ (str.size_)
{
	if (str.data_ != nullptr)
	{
		data_ = new CharT[capacity_ + 1];
		strcpy (data_, str.data_);
	}
}
String::String (CharT const *str) : capacity_ (strlen (str) + 1), data_ (new CharT[capacity_]), size_ (capacity_ - 1)
{
	strcpy (data_, str);
}
String::~String ()
{
	capacity_ = 0;
	delete[] data_;
	size_ = 0;
}
String &String::operator = (String const &str)
{
	if (&str == this)
		return *this;
	this -> ~String ();
	new (this) String (str);
	return *this;
}
String::CharT &String::operator [] (String::size_type i)
{
	return data_[i];
}
String::CharT const &String::operator [] (String::size_type i) const
{
	return data_[i];
}
String::CharT &String::front ()
{
	return data_[0];
}
String::CharT const &String::front () const
{
	return data_[0];
}
String::CharT &String::back ()
{
	return data_[size_ - 1];
}
String::CharT const &String::back () const
{
	return data_[size_ - 1];
}
String::CharT const *String::c_str () const
{
	return data_;
}
bool String::empty () const
{
	return (size_ == 0);
}
String::size_type String::size () const
{
	return size_;
}
String::size_type String::capacity () const
{
	return capacity_;
}
void String::reserve (String::size_type cap)
{
	if (cap <= capacity_)
		return;
	if (data_ == nullptr)
	{
		data_ = new CharT[cap];
		*data_ = '\0';
	}
	else
	{
		CharT *newdata = new CharT[cap];
		strcpy (newdata, data_);
		delete[] data_;
		data_ = newdata;
	}
	capacity_ = cap;
}
void String::resize (String::size_type sz)
{
	reserve(sz);
	size_ = sz;
	data_[size_] = '\0';
}
void String::shrink_to_fit ()
{
	CharT *newdata = new CharT[capacity_];
	strcpy (newdata, data_);
	delete[] data_;
	data_ = newdata;
	capacity_ = size_ + 1;
}
void String::clear ()
{
	size_ = 0;
}
String &String::erase (String::size_type index, String::size_type count)
{
	if (count == npos)
		count = size_ - index;
	for (String::size_type i = index; i < size_ - count; ++i)
		data_[i] = data_[i + count];
	size_ -= count;
	data_[size_] = '\0';
	return *this;
}
void String::push_back (String::CharT chr)
{
	if (size_ == capacity_)
		reserve((capacity_ + 1) * 2);
	data_[size_++] = chr;
	data_[size_] = '\0';
}
void String::pop_back ()
{
	if (size_ != 0)
	{
		data_[--size_] = '\0';
	}
	else
	{
		std::cout << "Empty string!\n";
	}
}
String &String::append (String const &str)
{
	reserve (size_ + str.size_);
	for (int i = 0; i < str.size_; ++i)
		data_[size_ + i] = str.data_[i];
	size_ += str.size_;
	data_[size_] = '\0';
	return *this;
}
String &String::append (String::CharT const *str)
{
	reserve (size_ + strlen (str));
	strcat (data_, str);
	size_ += strlen (str);
	return *this;
}
String &String::operator += (String const &str)
{
	append (str);
	return *this;
}
String &String::operator += (String::CharT const *str)
{
	append (str);
	return *this;
}
int String::compare (String const &str) const
{
	return strcmp (data_, str.data_);
}
int String::compare (String::CharT const *str) const
{
	return strcmp (data_, str);
}
int String::compare (String::size_type pos, String::size_type count, String const &str)
{
	return strncmp (data_ + pos, str.data_, count);
}
int String::compare (String::size_type pos, String::size_type count, String::CharT const *str)
{
	return strncmp (data_ + pos, str, count);
}
String String::substr (String::size_type pos, String::size_type count) const
{
	String s (data_ + pos);
	if (count != npos)
		s.resize (count);
	return s;
}
String::size_type String::find (String::CharT chr) const
{
	for (int i = 0; i < size_; ++i)
	{
		if (chr == data_[i])
			return i;
	}
	return npos;
}
String::size_type String::find (String const &str, String::size_type pos) const
{
	for (String::size_type i = pos; i < size_ - str.size (); ++i)
		if (!strncmp (data_ + i, str.data_, str.size ()))
			return i;
	return npos;
}
String::size_type String::find (String::CharT const *str, String::size_type pos) const
{
	for (String::size_type i = pos; i < size_ - strlen (str); ++i)
		if (!strncmp (data_ + i, str, strlen (str)))
			return i;
	return npos;
}
bool String::operator == (String const &str) {return !compare (str);}

bool String::operator == (String::CharT const *str) {return !compare (str);}

bool operator == (String::CharT const *str_ch, String const &str_st) {return !str_st.compare (str_ch);}

String String::operator + (String const &str) const
{
	String s (*this);
	return s.append (str);
}
String String::operator + (String::CharT const *str) const
{
	String s (*this);
	return s.append (str);
}
String operator + (String::CharT const *str_ch, String const &str_st)
{
	String s (str_ch);
	s.append (str_st);
	return s;
}
std::ostream &operator << (std::ostream &ostr, String const &str)
{
	ostr << str.data_;
	return ostr;
}
std::istream &operator >> (std::istream &istr, String &str)
{
	String::CharT buf[1024];
	istr >> buf;
	str = String (buf);
	return istr;
}
