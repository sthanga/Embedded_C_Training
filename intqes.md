### 07/02/2024 
max-lnr qstn
  1. Asked bit swapping like get a interger number then convert into binary then all odd digit goes to even digit and even 
  digit goes to odd places; Ans one right shift;
  2. asked string polidrom : of given string with count of polidrom 
    string reverse  methiod : strrev(stri_var)
  3. Network of ethernet /Tcpip, UDP
  4. spinlock, mutex,semaphore, deadlock, ipc etc;
  5. common process sharing a data with different process
  6. multithreading -> Multiprocess


spinlock - to fetch the data from the shared resource through locking mechanism
that is spin lock

### dead lock  - to fetch the 
``  bash
**†*************†**†****************"
Hear constant pointer and pointer to constant 

const int a;

int const a;

const int *a;

int * const a;

int const * a const;

*******************************"***********"

```
``` c
// pointer assignment and address of the variable
#include <stdio.h>

int main()
{
    int a =10;   // const int a =10 ;
    int*p = &a;  // const int *p = &a;   it is possible in C but c will not const variable to  const pointer variable assignment

    printf("pointer address : %p\n", &a);
    printf("pointer address : %p\n", p);
    printf("pointer address : %p\n", &p);

    return 0;
}
output
pointer address : 0x7ffe5ef9d80c
pointer address : 0x7ffe5ef9d80c
pointer address : 0x7ffe5ef9d810

```
