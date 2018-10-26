#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <iostream>

int Solver (double a, double b, double c, double *x1, double *x2)
{
	assert (std::isfinite (a));
	assert (std::isfinite (b));
	assert (std::isfinite (c));
	
	assert (x1 != NULL);
	assert (x2 != NULL);
	assert (x1 != x2);
	
	int d = 0;

	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (c == 0)
			{
				*x1 = 0;
				return 1;
			}
			else
			{
				*x1 = -c / b;
				return 1;
			}
		}
	}
	else
	{
		if (b == 0)
		{
			if (c == 0)
			{
				*x1 = 0;
				return 1;
			}
			else
			{
				if ((-c / a) > 0)
				{
					*x1 = sqrt (-c / a);
					*x2 = -sqrt (-c / a);
					return 2;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (c == 0)
			{
				*x1 = 0;
				*x2 = -b / a;
				return 2;
			}
			else
			{
				d = b * b - 4 * a * c;
				if (d > 0)
				{
					*x1 = (-b + sqrt (d)) / (2 * a);
					*x2 = (-b - sqrt (d)) / (2 * a);
					return 2;
				}
				if (d == 0)
				{
					*x1 = -b / (2 * a);
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
}

int main ()
{
	int res;
	bool ok = false;
	double a = 0, b = 0, c = 0;
	while (true)
	{
		printf ("Input a, b, c \n");
		std::cin >> a >> b >> c;
		if (!std::cin)
		{
			std::cout << "Shlyapa hoooooy" << std::endl;
			std::cin.clear ();
			while (std::cin.get () != '\n');
		}
		else break;
	}
	double x1 = 0, x2 = 0;

	int Q_roots = Solver (a, b, c, &x1, &x2);

	switch (Q_roots)
	{
		case 0: printf ("0 roots\n");
		break;

		case 1: printf ("x = %lg\n", x1);
		break;
		
		case 2: printf ("x1 = %lg, x2 = %lg\n", x1, x2);
		break;

		case -1: printf ("Any number\n");
		break;

		default: printf ("In function main () ERROR: Q_roots = %d\n", Q_roots);
		return 1;
	}
	return 0;
}

