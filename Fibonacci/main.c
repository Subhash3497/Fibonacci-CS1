//  main.c
//  Fibonacci
//  Created by subhash naidu on 10/1/16.
//  Copyright © 2016 subhash naidu. All rights reserved.

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "Fibonacci.h"
#include <string.h>

HugeInteger *parseString(char *str)
{
    int i = 0, j = 0, temp = 0;
    int string_length;
    HugeInteger *big_num;
    big_num = malloc(sizeof(big_num));

    if (str == NULL)
        return NULL;

    else if (big_num == NULL)
    {
        puts("Out of Memory");
        free(big_num);
        return NULL;
    }

    string_length = strlen(str);
    big_num->length = string_length;
    big_num->digits = calloc(string_length + 1,sizeof(int));

    for (i = string_length; i >= 0; i--, j++)
    {
        temp = str[i - 1];
        big_num->digits[j] = temp - 48;
    }

    return big_num;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    else if (p->digits != NULL)
    {
        free(p->digits);
        free(p);
    }

    return NULL;
}

HugeInteger *parseInt(unsigned int n)
{
    int decimalPlaces = 0;
    unsigned int temp = 0;
    int i = 0;
    unsigned int number = n;

    HugeInteger *big_num;
    big_num = malloc(sizeof(big_num));
    big_num->digits = calloc(10,sizeof(int));


    for(temp = n; temp > 1; decimalPlaces++)
    {
        temp/=10;
    }

    if (decimalPlaces == 0)
    {
        big_num->length = 1;
    }
    else
        big_num->length = decimalPlaces;

    if (big_num->digits == NULL)
    {
        puts("Error! Could not allocate memory.");
        free(big_num->digits);
        return NULL;
    }
    else if (big_num == NULL)
    {
        puts("Error! Could not allocate memory.");
        free(big_num);
        return NULL;
    }

    for (i = 0; i < big_num->length; i++)
    {
        temp = (number % 10);
        big_num->digits[i] = temp;
        number = (int)(number / 10);
    }

    return big_num;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    int i, j = 1;
    unsigned int number = 0;
    unsigned int *inputnum =(unsigned int)malloc(sizeof(unsigned int));

    if (p == NULL)
    {
        return NULL;
    }
    else if (p->length > 10)
    {
        return NULL;
    }

    for (i = 0; i < p->length; i++)
    {
        if(number > UINT_MAX)
        {
            free(inputnum);
            return NULL;
        }
        number += (p->digits[i] % 10) * j;
        j *= 10;
    }

    *inputnum = number;
    return inputnum;
}

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    int i;
    HugeInteger *sum_of_ints;
    int sum;

    //Dynamic Memory allocation of digits to hold the sum
    sum_of_ints = malloc(sizeof(sum_of_ints) + 1);

    if (p->length > q->length)
    {
        sum_of_ints->length = p->length;
    }
    else if (q->length > p->length)
    {
        sum_of_ints->length = q->length;
    }
    else
    {
        sum_of_ints->length = q->length + 1;
    }

    sum_of_ints->digits = calloc(sum_of_ints->length, sizeof(int));


    for (i = 0; i < sum_of_ints->length; i++)
    {
        sum = p->digits[i] + q->digits[i];

        if (sum >= 10)
        {
            sum_of_ints->digits[i] += (sum % 10);
            sum_of_ints->digits[i+1] = 1;
        }
        else
        {
            sum_of_ints->digits[i] += sum;
        }
    }

    return sum_of_ints;
}

HugeInteger *fib(int n)
{
    int i;

    //Struct to hold the final fib number
    HugeInteger *fib_num = malloc(sizeof(HugeInteger));
    fib_num->digits = malloc(sizeof(int) * 300);

    //Struct to hold the previous fib number.
    HugeInteger *current = malloc(sizeof(HugeInteger));
    current->digits = malloc(sizeof(int) * 300);
    current = parseInt(1);

    //Struct to hold the previous previous fib number.
    HugeInteger *previous = malloc(sizeof(HugeInteger));
    previous->digits = malloc(sizeof(int) * 300);
    previous = parseInt(0);

    if (n == 0)
    {
        fib_num = parseInt(0);
        return fib_num;
    }

    if (n == 1)
    {
        fib_num = parseInt(1);
        return fib_num;
    }
    else
    {
        for(i = 0; i < n; i++)
        {
            fib_num = hugeAdd(current, previous);
            previous = current;
            current = fib_num;

        }
    }

    return fib_num;
}



// print a HugeInteger (followed by a newline character)
void hugePrint(HugeInteger *p)
{
	int i;

	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)\n");
		return;
	}

	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
	printf("\n");
}

int main(void)
{
	int i;
	HugeInteger *p;

	for (i = 0; i <= 10; i++)
	{
		printf("F(%d) = ", i);
		hugePrint(p = fib(i));
		hugeDestroyer(p);
	}

	return 0;
}

