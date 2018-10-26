#include <assert.h>
#include <math.h>
#include <iostream>
#include <sstream>

int Solver (double a, double b, double c, double *x1, double *x2)
{
	assert (std::isfinite (a));
	assert (std::isfinite (b));
	assert (std::isfinite (c));
	
	assert (x1 != NULL);
	assert (x2 != NULL);
	assert (x1 != x2);
	
	double d = 0;

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
	double a = 0, b = 0, c = 0;
	double x1 = 0, x2 = 0;
	
	std::string line;
	while (std::getline (std::cin, line))
	{
		std::istringstream iss (line);
		if(iss >> a >> b >> c)
			break;
		std::cout << "Try again!" << std::endl;
	}
	int Q_roots = Solver (a, b, c, &x1, &x2);

	switch (Q_roots)
	{
		case 0: std::cout << "0 roots" << std::endl;
		break;

		case 1: std::cout << "x = " << x1 << std::endl;
		break;
		
		case 2: std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;
		break;

		case -1: std::cout << "Any number" << std::endl;
		break;

		default: std::cout << "In function main () ERROR: Q_roots = " << Q_roots << std::endl;
		return 1;
	}
	return 0;
}

