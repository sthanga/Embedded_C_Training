# List of questions to be prefered for interview:

# From Strings:
### strings are used store the array opf characters 
## String Polidrom
```c
#include <stdio.h>
#include <string.h>

void reverseStr(char name[])
{
    int len = strlen(name);
    printf("len %d \n", len);
    for(int i=0; i<len/2; i++)
    {
        char temp = name [i];
        name[i]=name[len-i-1];
        name[len-i-1] = temp;
    }
    printf("%s \n", name);
}

int main()
{
    char name[]="h22h" ;
    char str[100];
    strcpy(str, name);
    printf("name : %s \n", name);
    printf("str :%s \n", str);
    reverseStr(str);
    if (strcmp(name, str) == 0)
        printf("The string is palindrom");
    else
        printf("It is not a palindrom");

    return 0;
}
```
## String reverse
## String caps
## String lowers
## String first letter caps
## String duplicate find and max repeated letter/word
## String no.of Repeated given word/chars
## String Manupulating list of keywords (like strlen, strcat etc)

# From bit sets:
## Set the bit
## reset the bit
## toggle the bit
## bit swaping
## reverse the bit
## find the no of one's in the number contains bit
# find the no of Zero's in the number contains bit

# From others:
## Number Pilidrom
## Print the array
## print the sorted array
## print the deasscending oreder array
## find the max repated/duplicate of the array
## find the min no of array
## find the max no of array
## Binary search
## linear search
## Sort algrithms of Merge
## Sort algrithms of selections
## Sort algrithms of bubble
