#include "stack.hpp"
#include <iostream>

bool testConstr ()
{
	Stack <int> stk1;
	Stack <int> stk2 (stk1);
	return stk1.size () == 16 && stk1.capacity () == 0 && stk2.size () == 16 && stk2.capacity () == 0;
}
bool testPush ()
{
	Stack <int> stk;
	stk.push (-4);
	stk.push (0);
	stk.push (11);
	return stk.capacity () == 3;
}
bool testPop ()
{
	Stack <int> stk;
	stk.push (-7);
	stk.push (10);
	stk.pop ();
	stk.push (14);
	stk.pop ();
	return stk.capacity () == 1;
}
bool testTop ()
{
	Stack <int> stk;
	stk.push (-545);
	stk.push (1012);
	return stk.top () == 1012;
}
bool testEmpty ()
{
	Stack <int> stk1;
	Stack <int> stk2;
	stk1.push (-123);
	return stk1.empty () == false && stk2.empty () == true;
}
bool testSize ()
{
	Stack <int> stk1;
	Stack <int> stk2;
	for (int i = 0; i <= 16; i++)
		stk1.push (i);
	return stk1.size () == 32 && stk2.size () == 16;
}
bool testOperEqual ()
{
	Stack <int> stk1;
	Stack <int> stk2;
	stk1.push (5);
	stk1.push (11);
	stk2 = stk1;
	return stk1.size () == stk2.size () && stk1.capacity () == stk2.capacity () && stk1.top () == stk2.top ();
}
const char *testname[] = {"Constructor", "Push", "Pop", "Top", "Empty", "Size", "Operator ="};
bool (*tests[])(void) = {testConstr, testPush, testPop, testTop, testEmpty, testSize, testOperEqual};
int main ()
{
	for(std::size_t i = 0; i < sizeof(tests) / sizeof(char *); i++)
    {
        if(tests[i]())
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): ok" << std::endl;
        else
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): failed" << std::endl;
    }
	return 0;
}
