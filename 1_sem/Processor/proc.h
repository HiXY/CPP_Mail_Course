#include "stack.h"

/*
1 - push element
2 - out
3 - add
4 - sub
5 - mul
6 - div
7 - cmp element
8 - input from console
10 - popr ax
11 - pushr ax
12 - popr bx
13 - pushr bx
14 - inc ax
15 - dec ax
16 - inc bx
17 - dec bx

30 - jne mark_adress
31 - je mark_adress
32 - call mark_adress
33 - ret (result from stack)
((99 - end)) default now
*/

class Proc
{
	private:
		int ax = 0, bx = 0;
		Stack <int> data;
	
	public:
		Proc (){};
		~Proc (){};
		
		void start (int code[]);
};
	void Proc::start (int code[])
	{
		int command = 0;
		for (int i = 0;; i++)
		{
			switch (command = code[i])
			{
				case 1:
				{
					data.push (code[i + 1]);
					////std::cout << "pushed_" << code[i + 1] << std::endl;
					i++;
					break;
				}
				case 2:
				{
					std::cout << data.peek () << std::endl;
					////std::cout << "outed_" << data.peek () << std::endl;
					data.pop ();
					break;
				}
				case 3:
				{
					auto add1 = data.peek ();
					////std::cout << "add1_" << add1 << std::endl;
					data.pop ();
					auto add2 = data.peek ();
					////std::cout << "add2_" << add2 << std::endl;
					data.pop ();
					add1 += add2;
					////std::cout << "added__" << add1 << std::endl;
					data.push (add1);
					break;
				}
				case 4:
				{
					auto sub = data.peek ();
					data.pop ();
					auto min = data.peek ();
					data.pop ();
					min -= sub;
					////std::cout << "subed_" << min << std::endl;
					data.push (min);
					break;
				}
				case 5:
				{
					auto mult1 = data.peek ();
					data.pop ();
					auto mult2 = data.peek ();
					data.pop ();
					mult1 *= mult2;
					////std::cout << "multed_" << mult1 << std::endl;
					data.push (mult1);
					break;
				}
				case 6:
				{
					auto dvdr = data.peek ();
					data.pop ();
					auto dvdnd = data.peek ();
					data.pop ();
					dvdnd /= dvdr;
					////std::cout << "divided_" << dvdnd << std::endl;
					data.push (dvdnd);
					break;
				}
				case 7:
				{
					
					auto cmprtr = code[i + 1];
					auto el = data.peek ();
					data.pop ();
					i++;
					////std::cout << "compared_" << el << "_and_" << cmprtr << std::endl;
					if (el == cmprtr)
					{
						data.push (1);
					}
					else
					{
						data.push (0);
					}
					break;
				}
				case 8:
				{
					int inpt = 0;
					std::cout << "Input number" << std::endl;
					std::cin >> inpt;
					data.push (inpt);
					break;
				}
				case 10:
				{
					ax = data.peek ();
					////std::cout << ax << " poped in ax" << std::endl;
					data.pop ();
					break;
				}
				case 11:
				{
					data.push (ax);
					////std::cout << data.peek () << " pushed from ax" << std::endl;
					break;
				}
				case 12:
				{
					bx = data.peek ();
					////std::cout << bx << " poped in bx" << std::endl;
					data.pop ();
					break;
				}
				case 13:
				{
					data.push (bx);
					////std::cout << data.peek () << " pushed from bx" << std::endl;
					break;
				}
				case 14:
				{
					ax++;
					////std::cout << ax << " ax inced" << std::endl;
					break;
				}
				case 15:
				{
					ax--;
					////std::cout << ax << " ax deced" << std::endl;
					break;
				}
				case 16:
				{
					bx++;
					////std::cout << bx << " bx inced" << std::endl;
					break;
				}
				case 17:
				{
					bx--;
					////std::cout << bx << " bx deced" << std::endl;
					break;
				}
				case 30:
				{
					auto res = data.peek ();
					if (res == 1)
					{
						data.pop ();
						std::cout << ax << " result!" << std::endl;
						i++;
					}
					else if (res == 0)
					{
						data.pop ();
						int mark = code[i + 1];
						i = code[mark];
					}
					break;

				}
				case 31:
				{
					auto res = data.peek ();
					if (res == 1)
					{
						data.pop ();
                        int mark = code[i + 1];
                        i = mark - 1;
                        ////std::cout << i << " i" << std::endl;
					}
					else if (res == 0)
					{
						data.pop ();
						i++;
					}
					break;
				}
				case 32:
				{
					int mark = code[i + 1];
						////std::cout << code[mark] << " code[mark]" << std::endl;
					i = mark - 1;
						////std::cout << i << " i" << std::endl; 
					
					break;
				}
				case 33:
				{
					std::cout << data.peek () << " result!" << std::endl;
					data.pop ();
					break;
				}
				default:
				{
					std::cout << "Programm finished!" << std::endl;
					////std::cout << ax << " ax " << bx << " bx" << std::endl;
					exit (0);
				}
			}
		}
	}
