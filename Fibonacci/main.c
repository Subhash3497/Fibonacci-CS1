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
//Checking for NUll and memory leaks.
    if (str == NULL)
    {
        return NULL;
    }
    else if (big_num == NULL)
    {
        puts("Out of Memory");
        free(big_num);
        return NULL;
    }
    else if (strcmp(str, ""))
    {
        str = "0";
    }
//Setting the length of the huge number array.
    string_length = strlen(str);
    big_num->length = string_length;
    big_num->digits = calloc(string_length + 1,sizeof(int));
//Converts string ASCII values to integers.
    for (i = string_length; i >= 0; i--, j++)
    {
        temp = str[i - 1];
        big_num->digits[j] = temp - 48;
    }

    return big_num;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
//Returns Null if the input is Null.
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
    
//Creation and Allocation
    HugeInteger *big_num;
    big_num = malloc(sizeof(HugeInteger));
    big_num->digits = calloc(11,sizeof(int));

//Finds the number of digits in the unsigned int.
    for(temp = n; temp >= 1; decimalPlaces++)
    {
        temp/=10;
    }
//Sets the basecase decimal place.
    if (decimalPlaces == 0)
    {
        big_num->length = 1;
    }
    else//Sets the length in the hugeinteger struct.
        big_num->length = decimalPlaces;
//Checks for null cases.
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
//Splits up the interger into digit values and puts it into the array.
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
    unsigned int *inputnum = malloc(sizeof(unsigned int));
//Checks for NULL cases.
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
//Checks to see if conversion to unsinged int is possible.
        if(number > UINT_MAX)
        {
            free(inputnum);
            return NULL;
        }
//Converts number in array to unsigned int.
        number += (p->digits[i] % 10) * j;
        j *= 10;
    }

    *inputnum = number;
    return inputnum;
}

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    HugeInteger *sum_array = malloc(sizeof(HugeInteger));
    int sum_length = 0;
    int carry_num = 0;
    int sum_of_digits = 0;
    int i = 0;
    int digit1 = 0,digit2 = 0;
    
    sum_length = p->length > q->length ? p->length + 1: q->length + 1;
    sum_array->length = sum_length;
    sum_array->digits = calloc(sum_length, sizeof(int));
    
    
    for (i = 0; i < sum_length; i++)
    {
        digit1 = (i > p->length - 1) ? 0 : p->digits[i];
        digit2 = (i > q->length - 1) ? 0 : q->digits[i];
        
        sum_of_digits = digit1 + digit2 + carry_num;
        
        if (sum_of_digits >= 10)
        {
            sum_of_digits -= 10;
            carry_num = 1;
        }
        else
        {
            carry_num = 0;
        }
        
        sum_array->digits[i] += sum_of_digits;
    }
    if (carry_num == 1)
    {
        sum_array->digits[i++] = 1;
    }
    
    if (i == sum_length && sum_array->digits[i - 1] == 0)
    {
        sum_array->length = sum_array->length - 1;
    }
    
    return sum_array;
}

HugeInteger *fib(int n)
{
    int i;

    //Struct to hold the final fib number
    HugeInteger *fib_num = malloc(sizeof(HugeInteger));
    fib_num->digits = calloc(10000,sizeof(int));

    //Struct to hold the previous fib number.
    HugeInteger *current = malloc(sizeof(HugeInteger));
    current->digits = calloc(10000,sizeof(int));
    current = parseInt(1);

    //Struct to hold the previous previous fib number.
    HugeInteger *previous = malloc(sizeof(HugeInteger));
    previous->digits = calloc(10000,sizeof(int));
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
        for(i = 0; i < n-1; i++)
        {
            fib_num = hugeAdd(current, previous);
            previous = current;
            current = fib_num;
        }
    }

    return fib_num;
}

double difficultyRating(void)
{
    return 3.8;
}

double hoursSpent(void)
{
    return 25;
    
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
    
    hugePrint(fib(15000));
    return 0;
}

