#include<stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



int main (void)
{
    char a[] = "abcdefgacbdarjanshfksuashfnklfhienn";
    int n = strlen(a), temp, tot=1, locat ;

    for(int i=0; i<n; i++)
    {
        temp =0;
        for(int j=1+i; j<n; j++)   // here i+1 is impotrtant 
        {
            if (a[i]==a[j])
            {
                temp++;
            }
        }
     if (tot<temp)  // check the condition number of charecter exsiting ;
     {
        tot =temp;
        locat=i;
        printf("%c:%d \n",a[i],i);
     }

    }
    printf(" charecter:-> %c location:-> %d \n", a[locat],locat);
}
