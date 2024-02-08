#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main()
{
    int n = 0b11110000;  // binary value assinged to integer
    printf("%d\n",n);

    // Print the fibonacci series : concept sum of previous two numbers
    int fib_num, fib_value =0, pri_val=0, cur_val=1;

    scanf("%d", &fib_num);

    for (int i=0; i<fib_num; i++)
    {
        if ((i<=0) || (fib_num==0) )
        {
            printf ("%d - ",i);
        }
        else if((i==1) || (fib_num==1))
        {
            printf ("%d - ",i); 
        }
        else
        {
            fib_value = cur_val + pri_val;
            pri_val = cur_val;   // this is the important step ;
            cur_val = fib_value ;  // this is also otherwise will error value will return;
            printf("%d - ",fib_value);
        }
    }
    printf("\n");
    return 0;
}
