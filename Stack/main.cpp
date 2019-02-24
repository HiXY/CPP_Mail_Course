#include "stack.hpp"
#include <iostream>

int main ()
{
	std::cout << "Constructor with size" << std::endl;
	Stack <int> s1 (4);
	std::cout << s1.size () << " size;" << std::endl;
	std::cout << s1.empty () << " empty or not;" << std::endl;

	std::cout << "Constructor from Stack" << std::endl;
	Stack <int> s2 (s1);
	std::cout << s2.size () << " size;" << std::endl;
	std::cout <<  s2.empty () << " empty or not;" << std::endl;

	return 0;
}
