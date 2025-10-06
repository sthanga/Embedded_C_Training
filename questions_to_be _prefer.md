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
##  strcpy, strcmp, strlen code
```c
// String length
int my_strlen(const char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// String copy
void my_strcpy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // add null terminator
}

// String compare
int my_strcmp(const char str1[], const char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return (str1[i] - str2[i]); // difference in ASCII values
        }
        i++;
    }
    return (str1[i] - str2[i]); // also handles length difference
}
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
```c
#include <stdio.h>
int main()
{
    char str[] ="hi i am aks thangaraj";
    for(int i=0; str[i] != '\0'; i++)
    {
        if (str[i]>='a' && str[i] <='z')
        {
            str[i]= str[i] - 32 ;
        }
    }
    printf("%s \n", str);
    return 0;
}
/*
Outputs:
    HI I AM AKS THANGARAJ
*/
```
## String lowers
``` c
#include <stdio.h>

int main()
{
    char str[] ="hI i am AKS thangaraj";
    for(int i=0; str[i] != '\0'; i++)
    {
        if (str[i]>='A' && str[i] <='Z')    // here the condition
        {
            str[i]= str[i] + 32 ;
        }
    }
    printf("%s \n", str);
    return 0;
}

/* Output :
hi i am aks thangaraj 
*/
```
## String first letter caps
``` c
#include <stdio.h>

int main()
{
    char str[] ="hI i am AKS thangaraj";
    int count =1;
    for(int i=0; str[i] != '\0'; i++)
    {
        if (count ==0)
        {
            if (str[i] >= 'A' && str[i] <='Z')
                str[i]= str[i] + 32;
        }  
        if (count ==1 ) 
        {
            if (str[i] >= 'a' && str[i] <='z')
            {
                str[i]= str[i] - 32 ;
                count = 0;
            }
            count = 0;
        }
        if (str[i] ==' ')
            count = count +1;
    }
    printf("%s \n", str);
    return 0;
}
/*
output:
Hi I Am Aks Thangaraj 
*/
```
## String duplicate find and max & repeated letter
```c
#include <stdio.h>
#define MAX 126

void mostRepeatedChar(const char *str)
{
    int count[MAX]={0};
    int max =0;
    char result;
    for(int i=0; str[i]; i++)
    {
        count[(unsigned char)str[i]]++;
        
        if (count[(unsigned char)str[i]] > max && str[i] != ' ')
        {
            result=str[i];
            max= count[(unsigned char)str[i]];
        }
    }
    
    printf("The Max Count :: %d, Char:: %c", max , result );
}

int main()
{
    char str[] ="banana apple mango apple banana mango banana";  
    char a[MAX]= {'a'};  // a[0] is a and others are allocate with null;
    int count[MAX] = {10};  // count[0] is 10 and other are will 0;
    mostRepeatedChar(str);
}

/*
outputs:
The Max Count :: 13, Char:: a
*/
```
## String duplicate find and max repeated word
``` c
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define WORD_LEN 50

void mostRepeatedWord(const char* input) {
    char str[1000];
    strcpy(str, input);
    
    char* words[MAX_WORDS];
    int count[MAX_WORDS] = {0};
    int total = 0;
    
    char* token = strtok(str, " ");
    while (token) {
        int found = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(words[i], token) == 0) {
                count[i]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            words[total] = token;
            count[total++] = 1;
        }
        token = strtok(NULL, " ");
    }

    int max = 0;
    int maxIdx = 0;
    for (int i = 0; i < total; i++) {
        if (count[i] > max) {
            max = count[i];
            maxIdx = i;
        }
    }

    printf("Most repeated word: '%s' (%d times)\n", words[maxIdx], max);
}

int main() {
    const char* text = "banana apple mango apple banana mango banana";
    mostRepeatedWord(text);
    return 0;
}

```
## String Manupulating list of keywords (like strlen, strcat etc)
``` bash
From <string.h>, these are commonly used string-related functions (not keywords, but essential):

| Function                   | Description                               |
| -------------------------- | ----------------------------------------- |
| `strlen(str)`              | Returns length of string (excluding `\0`) |
| `strcpy(dest, src)`        | Copies string from `src` to `dest`        |
| `strncpy(dest, src, n)`    | Copies first `n` characters               |
| `strcat(dest, src)`        | Appends `src` to end of `dest`            |
| `strcmp(s1, s2)`           | Compares two strings                      |
| `strncmp(s1, s2, n)`       | Compares first `n` characters             |
| `strchr(str, c)`           | Finds first occurrence of char `c`        |
| `strstr(haystack, needle)` | Finds substring                           |
| `strtok(str, delim)`       | Tokenizes string using delimiters         |
| `memset(ptr, value, size)` | Sets memory (can be used for strings)     |
| `memcpy(dest, src, n)`     | Copies `n` bytes                          |

```

# From bit sets:

## Set reset toggle the bit
```c
#include <stdio.h>

int main() {
    unsigned char x = 0b00000101;

    // Set bit 2
    x |= (1 << 2);

    // Clear bit 0
    x &= ~(1 << 0);

    // Toggle bit 1
    x ^= (1 << 1);

    // Print result
    printf("Result: %u\n", x);  // Output as decimal
}

```
## Interview Questions from eversan:
```c
// Given a 64-bit number, count how many unique nibbles are present.
 
// Ex: Input: 0x1234567890ABCDEF output as 16
 
// Ex: 0x1224567890ABCDEF output as 15


#include <stdio.h>
#include <stdint.h>

void foundUniqeNipple(int arr[])
{
	int uniqueNo=16, temp=0;
	
	for(int i=0; i<16;i++)
	{
		temp=0;
		for(int j=i; j<16; j++)
		{
			if (arr[i]==arr[j])
				temp++;	
		}
        // printf("%d   ", temp);
		if (temp >1)
			uniqueNo--;
	}
	printf("no. of unique of nipples : %d", uniqueNo);
} 
 
 int main()
 {
 	
 	uint64_t data = 0x1234567890ABCDEF;
 	int arr[16];
 	int nipple = 4;
 	for(int i=0; i<16; i++)
 	{
 		if (i==0)
 			arr[i]= data & 0x0F;
 		else {
 			arr[i]= data >> nipple & 0x0F;
 			nipple +=4;
 		}
 	}
//  	for(int i=0;i<16; i++)
//  	    printf("%x \t",arr[i]);
 	
 	foundUniqeNipple(arr);
  	return 0;
 }
```


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

# G
# O
# O
# G
# L
# E
Here’s a curated list of **Google interview questions** specifically for the role of an **Embedded Software Engineer**, broken down by topic area:

---

### 🔧 **Core Embedded Systems Questions**

1. **What are the differences between a microcontroller and a microprocessor?**
2. **Describe the boot process of an embedded system.**
3. **How does interrupt handling work?**
4. **What’s the difference between polling and interrupts?**
5. **Explain memory-mapped I/O vs port-mapped I/O.**
6. **What is a watchdog timer and how is it used?**
7. **How do you reduce power consumption in an embedded system?**
8. **Explain how DMA works. When would you use it?**
9. **What is the difference between volatile and const keywords in C?**
10. **How do you debug an embedded system with limited resources?**

---

### 💻 **C/C++ Programming (Systems Level)**

1. **Write a C function to reverse a linked list.**
2. **What is the difference between stack and heap?**
3. **What is undefined behavior in C? Give examples.**
4. **Implement `memcpy()` without using library functions.**
5. **Explain the difference between `malloc()` and `calloc()`.**
6. **How would you prevent memory leaks in embedded code?**
7. **What’s the size of an empty struct in C?**
8. **What happens when you dereference a NULL pointer?**
9. **How do function pointers work in C?**
10. **Why is it important to avoid dynamic memory allocation in embedded systems?**

---

### 🧵 **RTOS / Multithreading**

1. **What is a race condition?**
2. **What are semaphores and how do they differ from mutexes?**
3. **How does priority inversion occur? How can you prevent it?**
4. **Explain the difference between a task, thread, and process.**
5. **How does context switching work in an RTOS?**
6. **What’s the typical latency of task switching in FreeRTOS or Zephyr?**
7. **How would you implement a periodic task that runs every 100ms?**

---

### 🔌 **Drivers and Peripheral Interfaces**

1. **How would you write a device driver for a custom I2C sensor?**
2. **Describe the SPI protocol and how it differs from I2C.**
3. **How would you detect and recover from a bus hang on I2C?**
4. **Write code to toggle a GPIO pin using memory-mapped I/O.**
5. **How do you handle interrupt-driven UART communication?**

---

### 📶 **Low-Level Debugging & Optimization**

1. **How do you debug a system that hangs randomly after 5 minutes of operation?**
2. **What tools do you use for embedded debugging?**
3. **How do you trace a hard fault on ARM Cortex-M?**
4. **How would you analyze and reduce CPU load in a constrained embedded system?**
5. **How would you debug a sporadic I2C communication failure?**

---

### 📁 **System Design / Architecture**

1. **Design a simple embedded system to control a smart thermostat.**
2. **How would you architect firmware updates over-the-air (OTA)?**
3. **Design a power-efficient remote sensor node.**
4. **How would you ensure safe software update with rollback on failure?**
5. **Describe how to design for deterministic latency.**

---

### ⚙️ **Google-Specific Focus Areas**

Google tends to focus on:

* Strong understanding of **systems programming**
* Clean, bug-free **C/C++** code
* **Multithreaded design**
* **Scalability** and **reliability**
* **Performance analysis** and **memory efficiency**

So expect deeper questions like:

* **Explain the memory layout of a C program.**
* **How do you ensure thread safety in a lock-free circular buffer?**
* **Write a bounded queue using semaphores.**
* **Design a firmware module that communicates with a WiFi chip via UART.**

---

### 🧠 **Behavioral Questions (Googliness)**

1. **Tell me about a time you optimized embedded code for performance.**
2. **Describe a challenging bug you fixed in production hardware.**
3. **How do you prioritize tasks when you’re under tight deadlines?**
4. **Have you mentored junior engineers? What’s your approach?**
5. **Tell me about a time you had to work across hardware/software boundaries.**

---

Would you like **mock interview answers**, **coding examples**, or **system design diagrams** for any of the questions above?



