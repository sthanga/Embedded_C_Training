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
```c
#include <stdio.h>
#include <string.h>

void main ()
{
    char name[] ="haodbsdb";
    printf("Actual ::  = %s \n", name);
    int len = strlen(name);
    printf("len %d \n", len);
    for(int i=0; i<len/2; i++)
    {
        char temp = name [i];
        name[i]=name[len-i-1];
        name[len-i-1] = temp;
    }
    printf("Reverse ::  = %s \n", name);
}
/*
output:

Actual ::  = haodbsdb 
len 8 
Reverse ::  = bdsbdoah

*/
```
## String Reverse word
``` c
#include <stdio.h>
#include <string.h>

// Helper function to reverse part of a string
void reverseRange(char *str, int start, int end)
{
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void reword(char *input)
{
    int len = strlen(input);
    // Step 1: Reverse the entire string
    reverseRange(input, 0, len - 1);
    // Step 2: Reverse each word back in-place
    int start = 0;
    for (int i = 0; i <= len; i++) {
        if (input[i] == ' ' || input[i] == '\0') {
            reverseRange(input, start, i - 1);
            start = i + 1;
        }
    }
}
int main()
{
    char input[] = "I am Thangaraj is good";
    reword(input);
    printf("%s\n", input);  // Output: good is Thangaraj am I
    return 0;
}

/*
good is Thangaraj am I
*/

```
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
## Binary search -ok
## linear search ok
## Sort algrithms of Merge
## Sort algrithms of selections
## Sort algrithms of bubble
