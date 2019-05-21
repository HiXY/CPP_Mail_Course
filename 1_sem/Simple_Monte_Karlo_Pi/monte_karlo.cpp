#include <iostream>
#include <random>

#define RADIUS 100

bool in_circle (double x, double y, double r)
{
	std::cout << "point: " << (x * x + y * y) << " radius: " << r * r << std::endl;
	return (x * x + y * y) <= (r * r);
}

int main ()
{
	int N, N_in_circle = 0;

	std::cout << "Input amount of points:" << std::endl;
	std::cin >> N;
	double lower_bound = 0;
	double upper_bound = 100;
	std::uniform_real_distribution <double> unif (lower_bound, upper_bound);
	std::default_random_engine rand_engine;

	for (int i = 0; i < N; i++)
	{
   		double rand_x = unif(rand_engine);
		double rand_y = unif(rand_engine);
		if (in_circle (rand_x, rand_y, RADIUS))
		{
			N_in_circle++;
		}
	}
	std::cout << static_cast <double> (N_in_circle) / static_cast <double> (N) * 4 << std::endl;
	return 0;
}
