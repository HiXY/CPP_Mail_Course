#include "stack.hpp"

bool testConstr ()
{
	Stack <int> stk1;
	Stack <int> stk2 (stk1);
	Stack <int> stk01 = std::move (Stack <int> (555));
	return stk1.size () == 16 && stk1.capacity () == 0 && stk2.size () == 16 && stk2.capacity () == 0 && stk01.size () == 555 && stk01.capacity () == 0;
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
	stk.pop ();
	stk.push (10);
	stk.push (14);
	stk.pop ();
	return stk.capacity () == 1;
}
bool testPopException ()
{
	Stack <int> stk;

	try
	{
		stk.push (44);
		stk.pop ();
		stk.pop ();
	}
	catch (const std::out_of_range &ex)
	{
		////std::cerr << ex.what () << std::endl;
		return true;
	}
}
bool testTop ()
{
	Stack <int> stk;

	stk.push (-545);
	stk.push (1012);
	return stk.top () == 1012;
}
bool testTopException ()
{
	Stack <int> stk;

	try
	{
		int el = stk.top ();
	}
	catch (const std::out_of_range &ex)
	{
		////std::cerr << ex.what () << std::endl;
		return true;
	}
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
	Stack <int> stk3;
	stk1.push (5);
	stk1.push (11);
	stk2.push (9);
	stk3 = Stack <int> (3);
	stk2 = stk1;
	return stk1.size () == stk2.size () && stk1.capacity () == stk2.capacity () && stk1.top () == stk2.top () && stk3.size () == 3 && stk3.empty ();
}
bool testMoveAssignExcept ()
{
	try
	{
		Stack <int> stk1;
		stk1 = std::move (stk1);
	}
	catch (const std::logic_error &ex)
	{
		////std::cerr << ex.what () << std::endl;
		return true;
	}
}
const char *testname [] = {"Constructor", "Push", "Pop", "PopException", "Top", "TopException", "Empty", "Size", "Operator =", "Move assignment Exception"};
bool (*tests[])(void) = {testConstr, testPush, testPop, testPopException, testTop, testTopException, testEmpty, testSize, testOperEqual, testMoveAssignExcept};
int main ()
{
	for (std::size_t i = 0; i < sizeof (tests) / sizeof (char *); i++)
    {
        if (tests[i]())
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): ok" << std::endl;
        else
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): failed" << std::endl;
    }
	return 0;
}
