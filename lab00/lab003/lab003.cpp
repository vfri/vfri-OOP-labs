// lab003.cpp: определяет точку входа для консольного приложения.
//	Выписывает числа Фибоначчи, не превосходящие n.
// n задается через аргумент командной строки

#include "stdafx.h"


int main(int argc, char* argv[])
{
	unsigned long n, prev, next, counter;

	printf(" Program writes Fibonacci series up to border n.\n Do set n as argument of command prompt\n");

	if (argc < 2)
	{
		printf("Border is setted to 1000. Another border you may set in command prompt\n");
		n = 1000;
	}
	else
	{
		n = std::stoi(argv[1]);
		if (n < 1)
		{
			printf("Border must be positive integer!\n");
			return 0;
		}
	}

	printf(" Fibonacci numbers less of equal then %d:\n", n);
	counter = 0;
	prev = 1;
	next = 1;
	printf("%10d", prev);
	counter++;
	while (next <= n - prev)
	{
		printf(",");
		if (counter % 5 == 0)
		{
			printf("\n");
		}
		printf("%10d", next);
		counter++;
		next += prev;
		prev = next - prev;
		
	}

	printf("\n");
	
	return 0;
}

