//
//  main.c
//  Fibonacci
//
//  Created by subhash naidu on 10/1/16.
//  Copyright © 2016 subhash naidu. All rights reserved.
//

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
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
    int i = 0, j = 0;
    HugeInteger *big_num;
    big_num = malloc(sizeof(big_num));
    

    big_num->length = strlen(str);
    
    for (i = big_num->length, big_num->digits = malloc(sizeof(int) * (big_num->length) + 1);i == 0; i--, j++)
    {
        big_num->digits[j] = str[i - 1];
        
    }
    
    //printf("%s",str);

    if (str == NULL)
    {
        return NULL;
    }
    else if (big_num->digits == NULL)
    {
        puts("Out of Memory");
        free(big_num->digits);
        free(big_num);
        return NULL;
    }

  
    return big_num;
}


HugeInteger *hugeDestroyer(HugeInteger *p)
{
    free(p->digits);
    free(p);
    
    return NULL;
}
/*
HugeInteger *parseInt(unsigned int n)
{
    HugeInteger *big_num;
    big_num->digits = malloc(sizeof(int) * 11);
    
    if (big_num->digits == NULL)
    {
        free(big_num->digits);
        return NULL;
    }
    
    sprintf(big_num->digits, n);
    
    return 0;
}
*/


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
    HugeInteger *p;
    
    hugePrint(p = parseString("12345"));
    hugeDestroyer(p);
    
    hugePrint(p = parseString("354913546879519843519843548943513179"));
    hugeDestroyer(p);
    
    return 0;
}




