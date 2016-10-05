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

/*HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    int i;
    HugeInteger *sum_of_ints;
    
    //Dynamic Memory allocation of digits to hold the sum
    sum_of_ints->digits = malloc(sizeof(int) * 500);
    
    //Initialization of array digits
    for (i = 0; i < 500; i++)
    {
        sum_of_ints->digits[i] = 0;
    }
    
    for (i = 0; i < 500 ; i++)
    {
        sum_of_ints->digits[i] = p->digits[i] + q->digits[i];
    }
    
  
    return 0 ;
}
*/

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
    
    for(temp = n; temp >= 1; decimalPlaces++)
    {
        temp/=10;
    }
    
    HugeInteger *big_num;
    big_num = malloc(sizeof(big_num));
    big_num->digits = calloc(decimalPlaces,sizeof(int));
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
    unsigned int *this_is_not_a_signed_int_yo;
    this_is_not_a_signed_int_yo = calloc(p->length, sizeof(unsigned int));
    
    for (i = 0; i < p->length; i++)
    {
        temp = p->digits[i];
        this_is_not_a_signed_int_yo += temp * (int)pow(10, i);
    }
    
    
    
    
    return this_is_not_a_signed_int_yo;
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
    unsigned int *temp;
    HugeInteger *p;
    
    hugePrint(p = parseString("12345"));
    printf("%u\n", *(temp = toUnsignedInt(p)));
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseString("354913546879519843519843548943513179"));
    temp = toUnsignedInt(p);
    if (temp == NULL)
        printf("Good work.\n");
    else
        printf("Uh oh...\n");
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseString(NULL));
    temp = toUnsignedInt(p);
    if (temp == NULL)
        printf("Good work.\n");
    else
        printf("Uh oh...\n");
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(246810));
    printf("%u\n", *(temp = toUnsignedInt(p)));
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(0));
    printf("%u\n", *(temp = toUnsignedInt(p)));
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(INT_MAX));
    printf("%u\n", *(temp = toUnsignedInt(p)));
    free(temp);
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(UINT_MAX));
    printf("%u\n", *(temp = toUnsignedInt(p)));
    free(temp);
    hugeDestroyer(p);

    return 0;
}




