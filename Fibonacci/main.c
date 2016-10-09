//  main.c
//  Fibonacci
//  Created by subhash naidu on 10/1/16.
//  Copyright © 2016 subhash naidu. All rights reserved.

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Fibonacci.h"
#include <string.h>

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    int i;
    HugeInteger *sum_of_ints;
    int sum;
    int size_of_num;
    
    if (p->length > q->length)
    {
        size_of_num = p->length + 1;
    }
    else if (q->length > p->length)
    {
        size_of_num = q->length + 1;
    }
    else
    {
        size_of_num = p->length + 2;
    }
    
    //Dynamic Memory allocation of digits to hold the sum
    sum_of_ints = malloc(sizeof(sum_of_ints));
    sum_of_ints->digits = calloc(size_of_num, sizeof(int));
    
    

    for (i = 0; i < size_of_num; i++)
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
    
    for (i = 0; i < size_of_num; i++)
    {
        printf("%d\n",sum_of_ints->digits[i]);
    }
    
    return sum_of_ints;
}

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
        return 0;
    }
    else if (p->digits != NULL || p != NULL)
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
    
    for(temp = n; temp > 1; decimalPlaces++)
    {
        temp/=10;
    }
    
    HugeInteger *big_num;
    big_num = malloc(sizeof(big_num));
    big_num->digits = calloc(10,sizeof(int));
    
    
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
        number = floor(number / 10);
    }
    
    return big_num;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    int i, temp = 0;
    unsigned int inputnum = malloc(sizeof(unsigned int));
    inputnum = 0;
    
    if (p == NULL)
    {
        return NULL;
    }
    else if (p->length >= 10)
    {
        return NULL;
    }
    
    for (i = 0; i < p->length; i++)
    {
        temp = p->digits[i];
        inputnum += (temp * (int)pow(10, i));
    }

    return &inputnum;
}

HugeInteger *fib(int n)
{
    int i,j;
    HugeInteger *fib_num = malloc(sizeof(HugeInteger));
    fib_num->digits = calloc(n, sizeof(int));
    
    HugeInteger *numprevious1;
    numprevious1 = malloc(sizeof(HugeInteger));
    numprevious1->digits = calloc(100, sizeof(int));
    
    HugeInteger *numprevious2;
    numprevious2 = malloc(sizeof(HugeInteger));
    numprevious2->digits = calloc(100, sizeof(int));
    
    numprevious2->digits[0] = 1;
    numprevious1->digits[0] = 1;
    
    if (n == 0)
    {
        fib_num->digits[0] = 0;
        return fib_num;
    }
    else if (n == 1)
    {
        fib_num->digits[0] = 1;
        return fib_num;
    }
    else if (n == 2)
    {
        fib_num->digits[0] = 1;
        return fib_num;
    }
    else
    {
        for (i = 2,j = 0; i <= n; i++)
        {
            fib_num = hugeAdd(numprevious1, numprevious2);
            numprevious2 = numprevious1;
            numprevious1 = fib_num;
        }
    }
    
    return 0;
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




