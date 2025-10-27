# C Int Training = Important memorable of C coding

## Types of Memory
### In embedded systems and general computing, memory is categorized based on how it's used, accessed, stored, and retained. Here's a breakdown of the main types of memory

``` bash

🔹 1. RAM (Random Access Memory)
	Volatile: Loses data when power is off.
	Fast and used for temporary storage during program execution.
	Types:
	Type	Use Case	Example
	SRAM (Static RAM)	CPU registers, small fast buffers	Used inside microcontrollers (e.g., stack, variables)
	DRAM (Dynamic RAM)	Main system RAM in computers	DDR3, DDR4 in PCs

🔹 2. ROM (Read-Only Memory)
	Non-volatile: Retains data after power off.
	
	Stores firmware or boot code.
	
	Types:
	Type	Description
	ROM	Pre-programmed at factory
	PROM	Programmable once after manufacture
	EPROM	Erasable with UV light
	EEPROM	Electrically erasable and writable
	Flash	Fast, common EEPROM variant

🔹 3. Flash Memory
	Non-volatile, reprogrammable.
	Common in microcontrollers to store code and constants.
	Also used in SD cards, SSDs.
	🧠 Example: In STM32, the program is stored in internal Flash memory.

🔹 4. Cache Memory
	Small, fast memory inside CPU.
	Temporarily stores frequently used data or instructions.
	Types: L1, L2, L3 (based on hierarchy).

🔹 5. Registers
	Tiny memory units inside the CPU.
	Fastest memory.
	Used for immediate operations, like addition, branching.

🔹 6. Virtual Memory (In OS like Linux)
	Not a real memory type, but a technique.
	Maps memory to disk (swap space) when RAM is full.
	Enables large program support.

🔹 7. Memory-Mapped I/O
	Peripherals mapped into addressable memory space.
	Accessed using pointers to fixed addresses.
	Requires volatile access in C.

🧠 Summary Table:
	Memory Type		Volatile		Speed			Use Case
	Registers		✅			🔥 Fastest		CPU instructions
	Cache (L1/L2/L3)	✅			🔥🔥			CPU performance
	SRAM			✅			🔥			MCU stack, global vars
	DRAM			✅			Fast			Main RAM (PCs)
	ROM/EPROM		❌			Slow			Fixed firmware
	EEPROM			❌			Medium			Config, calibration data
	Flash			❌			Medium			Program storage
	Memory-mapped I/O	⚠️ Mixed		Hardware Dependent	Peripheral control
	Virtual Memory		❌			Slow (Disk)		Swap area in OS
```
## Register memory
In C or C++, you **can’t directly control CPU registers** like `R0`, `R1`, etc., from standard code — the **compiler handles that automatically** for optimization. However, you can **influence** or **hint** usage, and in **embedded systems**, you can also **access peripheral registers** via **memory-mapped I/O**.

Let’s cover both cases:

---

## 🧠 1. **Using CPU Registers (Implicitly)**

### ✅ Example in C

```c
int add(int a, int b) {
    return a + b;
}
```

The compiler will use CPU registers to hold `a` and `b` during the addition. On an **ARM Cortex-M**, it might compile to:

```assembly
MOV R0, a
MOV R1, b
ADD R0, R0, R1  ; result in R0
```

> You don’t need to do anything — the compiler handles register usage for fast execution.

---

## ⚠️ 2. **Explicit Control (Advanced)**

### 🔧 Using `register` keyword (Hint only)

```c
void example() {
    register int x = 5;  // Suggests storing x in a CPU register
    x++;
}
**************************************************
register int a = 5;
int *p = &a ;

compiler show error:
volati2.c: In function ‘main’:
volati2.c:38:5: error: address of register variable ‘a’ requested
   38 |     int *p = &a;
      |     ^~~
*************************************************
register int a = 5;
printf("%p",&a);

compiler show error:
volati2.c: In function ‘main’:
volati2.c:38:5: error: address of register variable ‘a’ requested
   38 |     printf("%p",&a);
      |     ^~~~~~
***************************************************
```

* Modern compilers **ignore `register`** because they already optimize better than a human can.
* You **can’t take the address** of a `register` variable (`&x` is not allowed).

---

## 🧭 3. **Accessing Hardware Registers (Embedded C)**

In embedded programming, **registers of peripherals** (e.g., GPIO, UART) are accessed via fixed **memory addresses** — this is known as **memory-mapped I/O**.

### ✅ Example: Accessing GPIO register (STM32-like)

```c
#define GPIOA_ODR (*(volatile uint32_t *)0x48000014)

int main() {
    GPIOA_ODR |= (1 << 5);  // Set GPIOA pin 5 high
    return 0;
}
```

* This is **not a CPU register**, but a **hardware register**.
* `volatile` ensures the compiler **does not optimize away** access to this address.
* Used commonly in bare-metal firmware or RTOS-based systems.

---

## 🚫 Direct CPU Register Access in C?

If you really want to access CPU registers directly (e.g., special registers like control/status registers), you must:

* Use **assembly (`asm`) inline**
* Or use **intrinsics** (compiler-specific)

### Example: Inline Assembly (GCC)

```c
int read_psr() {
    int psr;
    __asm__("MRS %0, APSR" : "=r" (psr));
    return psr;
}
```

> This reads the Program Status Register on ARM Cortex-M.

---

## ✅ Summary

| Goal                                 | How to Do It                                 |
| ------------------------------------ | -------------------------------------------- |
| Use CPU registers                    | Write efficient C code — compiler handles it |
| Suggest CPU register usage           | Use `register` keyword (rarely useful now)   |
| Access hardware peripheral registers | Use pointer to memory-mapped addresses       |
| Access CPU system registers          | Use inline assembly or intrinsics            |

---

Would you like to see register usage in **compiled assembly** for one of your C functions? I can generate it.


## Questions On Storage Class Specifier

### 1. What are storage class specifier?

   Storage class specifiers in C language tells the compiler where to store a variable, how to store the variable, what is the initial value of the variable and life time of the variable.
   
   **Syntax:** `storage_specifier data_type variable _name`

   Types of storage class specifier in c :
   
   There are four storage class specifier in C Language. They are,
   
   1. Automatic
   2. Register
   3. Static
   4. Extern
   
   
   Storage Specifier | Storage Place | Initial /Default value | Scope | Life Time |
   ----------------- | ------------- | ---------------------- | ----- | --------- |
     Auto | CPU Memory | garbage value | local | within block |
     static | CPU Memory | zero | local | Retains the value of the variable between different function calls. | 
     register | CPU Memory | garbage | local | within block | 
     extern | CPU Memory | zero | global | Till the end of the main program. Variable definition might be anywhere in the C program  |
     
   **Note:**
   
   * For faster access of a variable, it is better to go for register specifiers rather than auto specifiers.
   * Because, register variables are stored in register memory whereas auto variables are stored in main CPU memory.
   * Only few variables can be stored in register memory. So, we can use variables as register that are used very often in a C program.

### 1.1 difference between i++ and ++i 
``` bash
This incremental and decremental can cause some confusion,  but easily remember the working of ++i , i++ , --i , i--.
The ++i operator increments the value of i and then returns the incremented value.
For example, if i is initially 1, ++i will increment i to 2 and return 2.
On the other hand, the i++ operator also increments the value of i,
but it returns the original value of i before the increment.
Using the same initial value of 1, i++ will increment i to 2 but return 1.
```
``` c
1	#include <stdio.h>
2	
3	int main() {
4	  int i=1;
5	  int j=1;
6	  int l=1;
7	  int m=1;
8	  //i++;
9	  printf(" the value after i++ is : %d\n",i++);
10	  //++j;
11	  printf(" the value after ++j is : %d\n",++j);
12	  
13	  //l--;
14	  printf(" the value after l-- is : %d\n",l--);
15	  //--m;
16	  printf(" the value after --m is : %d\n",--m);
17	  return 0;
18	}
output is 
```
![image](https://github.com/user-attachments/assets/8ae11256-1041-4ef3-9f4a-bc637a8db5ba)

### 2. What is static variable?

There are 3 main uses for the static variable.

1. If it declares within a function:
  * It retains the value between function calls.
1. If it is declared for a function name:
  * By default function is extern, so it will be visible from other files if the function declaration is as static, it is invisible for the outer files.
1. Static for global variables:
  * By default we can use the global variables from outside files If it is static global..that variable is limited to with in the file.
### What is Extern variable?
The extern keyword in C is used to declare a global variable or function that is defined in another file or later in the same file. It tells the compiler that the variable or function exists but is defined elsewhere.
```c
c programs to expain on Extern
/************************************************************************************/
file.c
/************************************************************************************/
#include <stdio.h>
int globalVar = 100;  // Global variable definition

void printValue() {
    printf("Global Variable: %d\n", globalVar);
}

/************************************************************************************/
file2.c
/************************************************************************************/
#include <stdio.h>

extern int globalVar;  // Declare the variable (defined in file1.c)
extern void printValue();  // Function prototype

int main() {
    printf("Accessing globalVar in file2.c: %d\n", globalVar);
    printValue();  // Call function from file1.c
    return 0;
}

/************************************************************************************/
compile :

gcc file1.c file2.c -o output
./output

/************************************************************************************/



here two ".c" file interchaning the variable and function with single main only.
```
### 3. What is difference between static and extern?
 
#### Static:
  
   * The static storage class is used to declare an identifier that is a local variable either to a function or a file and that exists and   retains its value after control passes from where it was declared.
   * This storage class has a duration that is permanent.
   * A variable declared of this class retains its value from one call of the function to the next.
   * The scope is local. A variable is known only by the  function it is declared within or if declared globally in a file, it is known or seen only by the functions within that file. This storage class guarantees that declaration of the variable also initializes the variable to zero or all bits off.

#### Extern:
  
  * The extern storage class is used to declare a global variable that will be known to the functions in a file and capable of being known to all functions in a program.
  * This storage class has a duration that is permanent. Any variable of this class retains its value until changed by another assignment.
  * The scope is global.
  * A variable can be known or seen by all functions within a program.

Modifier		Scope				Accessible Outside File?	Retains Value?
static (global)		File-level (internal linkage)		❌ No			   ✅ Yes
static (local)		Function-level				❌ No  			   ✅ Yes (between calls)
extern			Global scope				✅ Yes			   ✅ Yes
### Key Takeaways:

static makes a variable/function file-private.
extern makes a variable/function visible across files.
They cannot be used together because they serve opposite purposes.
  
### 4. What is difference between static local and static global variable?

#### Static global :
 * Static variable has scope only in the file in which it is declared. it can't be accessed in any other file but its value remains intact if code is running in some other file means lifetime is in complete program .

#### Static local:
 * static local variable has scope in that function in which it is declared means it can't be used in other functions in the same file also, means scope is limited to the function in which it is declared while its life time is also through out the program.

### 5. Can we declare static variable in header file?
* You can’t declare a static variable without defining it as well (this is because the storage class modifiers static and extern are mutuallyexclusive). A static variable can be defined in a header file, but this would cause each source file that included the header file to have its own private copy of the variable, which is probably not what was intended.

### 6. Can we declare main() function as static?
 * No. The C spec actually says somewhere in it  that the main function cannot be static.
The reason for this is that static means "don't let anything outside this source file use this object". The benefit is that it protects against name collisions in C when you go to link (it would be bad bad bad if you had two globals both named "is_initialized" in different files... they'd get silently merged, unless you made them static). It also allows the compiler to perform certain optimizations that it wouldn't be able to otherwise. These two reasons are why static is a nice thing to have.
Since you can't access static functions from outside the file, how would the OS be able to access the main function to start your program? That's why main can't be static.
Some compilers treat "main" specially and might silently ignore you when you declare it static.

### 7. Draw memory layout of C program?
Refer This link:   http://cinterviewquestionandanswer.blogspot.in/2014/01/memory-layout-of-c-programs.html

### 8. What is volatile variable means?
 * volatile has nothing to deal with storage class.
 * volatile just tells the compiler or force the compiler to "not to do the optimization" for that variable. so compiler would not optimize the code for that variable and reading the value from the specified location, not through interal register which holds the previous value.
 * So, by declaring variable as volatile.. it gives garrantee that you will get the latest value, which may be alterred by an external event.
 * your code may be work fine if haven't declare that variable as volatile, but there may be chance of not getting correct value sometimes, so to avoid that we should declare variable as volatile.
volatile is generally used when dealing with external events, like interrupts of hardware related pins.

`Example. reading adc values`

 * const voltile means you can not modify or alter the value of that variable in code. only external event can change the value.
controller pins are generally defines as volatile. may be by declaring variable as volatile controller will do "read by pin" not "read by latch"... this is my assumtion. may be wrong...
but still there is lots of confusion when to choose variable as volatile..
A variable should be declared volatile whenever its value could change unexpectedly. In practice, only three types of variables could change:
Memory-mapped peripheral registers
Global variables modified by an interrupt service routine
Global variables within a multi-threaded application

``` bash
The **volatile** keyword in C (and C++) is used to tell the compiler that a variable's value can change at any time,
outside the control of the current code — for example, due to:
Hardware (e.g., GPIO, memory-mapped registers)
Interrupt Service Routines (ISRs)
Multithreading or shared memory

# Memory-mapped I/O registers:
volatile uint32_t *GPIO_DATA = (uint32_t *)0x40025038;
*GPIO_DATA = 0x01;
Flaged updated by ISR

volatile int button_pressed = 0;
void ISR() {
    button_pressed = 1;
}
int main() {
    while (!button_pressed);  // Without volatile, compiler might optimize this loop away
}
Shared variables in multithreading:
volatile int done = 0;

Note: When the program executed the volatile varible is storing into ram. When that varaiable called from program
it reads from that memory instead of like other variable.

Example:
Normal execution:
	int flag = 0;
	while (!flag);  // Compiler may optimize this into an infinite loop (if it assumes 'flag' never changes)
Volatile Execution:
	volatile int flag = 0;
	while (!flag);  // Compiler will check memory each time
```

### 9. What does keyword const means?
 * The const qualifier explicitly declares a data object as something that cannot be changed. Its value is set at initialization. You cannot use const data objects in expressions requiring a modifiable lvalue. For example, a const data object cannot appear on the lefthand side of an assignment statement
int const volatile var

### 10. What do the following declaration means?

```c
const int a;
int const a;
const int *a;
int * const a;
int const * a const;
```

### 11. Can we use const keyword with volatile variable?

Yes. The const modifier means that this code cannot change the value
of the variable, but that does not mean that the value cannot be
changed by means outside this code. For instance, in the example  the timer structure was accessed through a volatile const pointer. The function itself did not change the value of the timer, so it was declared const. However, the value was changed by hardware on the computer, so it was declared volatile. If a variable is both const and volatile, the two modifiers can appear in either order.

### 12. What are pointers?

A pointer is a variable whose value is the address of another variable, i.e., direct address of the memory location. Like any variable or constant, you must declare a pointer before you can use it to store any variable address. The general form of a pointer variable declaration is:

`type *var-name;`

Here, type is the pointer's base type; it must be a valid C data type and var-name is the name of the pointer variable. The asterisk * you used to declare a pointer is the same asterisk that you use for multiplication. However, in this statement the asterisk is being used to designate a variable as a pointer. Following are the valid pointer declaration:
`int    *ip;`    /* pointer to an integer */
`double *dp;`    /* pointer to a double */
`float  *fp;`    /* pointer to a float */
`char   *ch`     /* pointer to a character */

The actual data type of the value of all pointers, whether integer, float, character, or otherwise, is the same, a long hexadecimal number that represents a memory address. The only difference between pointers of different data types is the data type of the variable or constant that the pointer points to.

### 13. What is dangling pointer?

A dangling pointer points to memory that has already been freed. The storage is no longer allocated. Trying to access it might cause a Segmentation fault.

Common way to end up with a dangling pointer:

```c
char* func()
{
   char str[10];
   strcpy(str,"Hello!");
   return(str); 
}
```

//returned pointer points to str which has gone out of scope. 
You are returning an address which was a local variable, which would have gone out of scope by the time control was returned to the calling function. (Undefined behaviour)
Another common dangling pointer example is an access of a memory location via pointer, after free has been explicitly called on that memory.

```c
int *c = malloc(sizeof(int));
free(c);
*c = 3; //writing to freed location!
```

### 14. What is NULL pointer?

Null pointer is special reserved value of a pointer. A pointer of any type has such a reserved value. Formally, each specific pointer type (int*, char*) has its own dedicated null-pointer value. Conceptually, when a pointer has that null value it is not pointing anywhere.

### 15. What is void Pointer?

Void pointer or generic pointer is a special type of pointer that can be pointed at objects of any data type. A void pointer is declared like a normal pointer, using the void keyword as the pointer’s type.

Pointers defined using specific data type cannot hold the address of the some other type of variable i.e., it is incorrect in C++ to assign the address of an integer variable to a pointer of type float.

Example:
```
float *f; //pointer of type float
int i;  //integer variable
f = &i; //compilation error
```
The above problem can be solved by general purpose pointer called void pointer.

Void pointer can be declared as follows:

`void *v ` // defines a pointer of type void

The pointer defined in this manner do not have any type associated with them and can hold the address of any type of variable.

Example:

```
void *v;
int *i;
int ivar;
char chvar;
float fvar;
v = &ivar; // valid
v = &chvar; //valid
v = &fvar; // valid
i = &ivar; //valid
i = &chvar; //invalid
i = &fvar; //invalid  
```
5. What is memory leakage? How can we avoid it?
Ans :
Memory leak occurs when programmers create a memory in heap and forget to delete it.
Memory leaks are particularly serious issues for programs like daemons and servers which by definition never terminate.
/* Function with memory leak */
#include 

void f()
{
   int *ptr = (int *) malloc(sizeof(int));

   /* Do some work */

   return; /* Return without freeing ptr*/
}
To avoid memory leaks, memory allocated on heap should always be freed when no longer needed.
/* Function without memory leak */
#include ;

void f()
{
   int *ptr = (int *) malloc(sizeof(int));

   /* Do some work */

   free(ptr);
   return;
}
### Pointer read only memeory

```c
#include<stdio.h>
void swap (char *x, char *y) {
    char *t = x;
    x = y;
    y = t;
}
int main()
{
    char *x = "geeksquiz";
    char *y = "geeksforgeeks";
    char *t;
    swap(x, y);
    printf("(%s, %s)", x, y);
    t = x;
    x = y;
    y = t;
    printf("\\n(%s, %s)", x, y);
    return 0;
}

outputs :
(geeksquiz, geeksforgeeks)\n(geeksforgeeks, geeksquiz)

char *x = "geeksquiz";
char *y = "geeksforgeeks";

these are read only memory in the heap so the function call will not change,
if that has to swap then refefence to share to function
```
```c
#include <stdio.h>
void f(char**);
int main()
{
    char *argv[] = { "ab", "cd", "ef", "gh", "ij", "kl" };
    f(argv);
    return 0;
}
void f(char **p)
{
    char *t;
    t = (p += sizeof(int))[-1];
    printf("%s\\n", t);
}

output:
	gh
	i.e t = (0 + 4) [-1]
	    	ij[-1]
		gh
```

 ```c

```
‘ptrdata’ is a pointer to a data type. The expression *ptrdata++ is evaluated as (in C++) : *(ptrdata++)

### 16. What is the size of pointer in 32 bit machine?

Sizeof  of pointer in 32 bit machine is always 4 bytes.

### 17. Write a program to find weather machine is 32 bit or 64 bit?

```c
int main()
{
    int *p = NULL;
    if(sizeof(p) == 4)
        printf("Machine is 32 bit\n");
    else
        printf("Machine is 64 bit\n");
    return 0;
}
```

### 18. What is array?

In C programming, one of the frequently arising problem is to handle similar types of data. For example: If the user want to store marks of 100 students. This can be done by creating 100 variable individually but, this process is rather tedious and impracticable. These type of problem can be handled in C programming using arrays.
An array is a sequence of data item of homogeneous value(same type).

### 19. What is difference between array and pointer?

An array is an array and a pointer is a pointer, but in most cases array names are converted to pointers.
Here is an array:
`int a[7]`
a contains space for seven integers, and you can put a value in one of them with an assignment, like this:
`a[3] = 9;`
Here is a pointer:
`int *p;`
p doesn't contain any spaces for integers, but it can point to a space for an integer. We can for example set it to point to one of the places in the array a, such as the first one:
`p = &a[0];`
What can be confusing is that you can also write this:
`p = a;`
This does not copy the contents of the array a into the pointer p (whatever that would mean). Instead, the array name a is converted to a pointer to its first element. So that assignment does the same as the previous one.
Now you can use p in a similar way to an array:
`p[3] = 17;`
The reason that this works is that the array dereferencing operator in C, "[ ]", is defined in terms of pointers. x[y] means: start with the pointer x, step y elements forward after what the pointer points to, and then take whatever is there. Using pointer arithmetic syntax, x[y] can also be written as *(x+y).
For this to work with a normal array, such as our a, the name a in a[3] must first be converted to a pointer (to the first element in a). Then we step 3 elements forward, and take whatever is there. In other words: take the element at position 3 in the array. (Which is the fourth element in the array, since the first one is numbered 0.)
So, in summary, array names in a C program are (in most cases) converted to pointers. One exception is when we use the sizeof operator on an array. If a was converted to a pointer in this contest, sizeof(a) would give the size of a pointer and not of the actual array, which would be rather useless, so in that case a means the array itself.

### 20. Can we increment the base address of array? Justify your answer.
 
No, Because once we initialize the array variable, the pointer points base address only & it's fixed  and constant pointer.

### 21.  What is the output of program ?
int a[5] = {1,2,3,4,5};
int *ptr = (int*) (&a +1);
int *ptr = (int*) (a+1); 

you see, for your program above, a and &a will have the same numerical value,and I believe that's where your whole confusion lies.You may wonder that if they are the same,the following should give the next address after a in both cases,going by pointer arithmetic:

`(&a+1) and (a+1)`

But it's not so!!Base address of an array (a here) and Address of an array are not same! a and &a might be same numerically ,but they are not the same type. a is of type int* while &a is of type int (*)[5],ie , &a is a pointer to (address of ) and array of size 5.But a as you know is the address of the first element of the array.Numerically they are the same as you can see from the illustration using ^ below.
But when you increment these two pointers/addresses, ie as (a+1) and (&a+1), the arithmetic is totally different.While in the first case it "jumps" to the address of the next element in the array, in the latter case it jumps by 5 elements as that's what the size of an array of 5 elements.
 

### 22. What is output of the program?

```c
int main()
{
 int arr[10];
 int *ptr = arr;
 ptr++;
 arr++;
 return 0;
}
```
  
The statement `arr++` will give you lvalue error. Because hear you are trying to increment base address of array and by default base address of array is constant pointer(constant value) so,
`arr  =  arr+1;`
i.e according to rule on LHS of assignment operator there always should be lvalue i.e variable not constant.

### 23. What is string?

The string in C programming language is actually a one-dimensional array of characters which is terminated by a null character '\0'. Thus a null-terminated string contains the characters that comprise the string followed by a null.

### 24. What is difference between these two,

char ptr[] = "string";
char *ptr = "string";

The two declarations are not the same.
First one is the array of character i.e. string and second one is the string literals.
char ptr[] = "string"; declares a char array of size 7 and initializes it with the characters s ,t,r,i,n,g and \0. You are allowed to modify the contents of this array.
char *ptr = "string"; declares ptr as a char pointer and initializes it with address of string literal "string" which is read-only. Modifying a string literal is an undefined behavior. What you saw(seg fault) is one manifestation of the undefined behavior.

### 25. Write a program to find size of variable without using sizeof operator?

```c
#define sizeof(var)     ( (char*)(&var+1) - (char*) (&var))
int main()
{
    int val;
    printf("size of = %d\n", SIZEOF(val));
    return 0;
}
```

### 26. Write a program to find sizeof structure without using size of operator?

```c
#define SIZEOF(var)     ( (char*)(&var+1) - (char*) (&var))
int main()
{
 struct s {
  int a;
  char b;
  int c;
 };
 struct s obj[1];
 
 printf("size of = %ld\n", SIZEOF(obj));
 
 return 0;
}
```

### 27. What is the output of following program?

```c
int main()
{
  char str[] = "vishnu";
  printf("%d %d\n",sizeof(str),strlen(str));
}
```
Ans:
7 6

Here char str[] = " 'v'. 'i' ,'s','h','n',u','\0' ";

so sizeof operator always count null character whereas strlen skip null character.

### 28. Write a program to implement strlen(), strcpy(),strncpy(), strrev(),strcmp() function"?

#### 1. strlen:

```c
int my_strlen(const char * str)
{
    int count;
    while(* str != '\0') {
        count++;
        str++;
    }
    return 0;
}
```

#### 2. strcpy:

```c
void my_strcpy(char * dest, const char* src)
{
    while(* src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
```

### 3. strrev:

```c
void my_strrev(char *str,size)
{
    int i;
    char temp;
    for(i=0;i<=size/2;i++) {
        temp = str[i];
        str[i] = str[size-i];
        str[size-i] = temp;
    }
}
int main()
{
    char str[10] = "vishnu";
    int len;
    len = strlen(str);
    my_strrev(str,len-1);
    printf("strrev = %s\n",str);
    return 0;
}
```

#### 4. strcmp :

```c
void my_strcmp(char * dest, const char* src)
{
     while(*str != '\0' && *dest != '\0') {
        str++;
        dest++;
    }
    return (*src - *dest);
}

int main()
{
    char str[10];
    char dest[10];
    int i;
    i = my_strcmp(dest,src);
    if(i == 0 )
        printf("strings are equal\n");
    if(i < 0)
        printf(" string1 is less than string2\n");
    if(i > 0)
        printf("string2 is greter than string1\n");
    return 0;
} 
```

### 5. strncpy

```c
void my_strncpy(char * dest, const char* src,int n)
{
    while(*src != '\0' && n != 0) {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    while(n) {
        *dest = '\0';
        n--;
    }
}
```
### pointer with structure:

```c
1       #include <stdio.h>
2	#include <stdlib.h>
3	
4	struct a1 {
5	  int data ;
6	  struct a1 * test;
7	};
8	
9	int main()
10	{
11	    int a = 10;
12	    int *p  = &a;
13	    int *c;
14	    printf("pointer address p: %p \n", p);   // pointer pointing to memory
15	    printf("pointer address a: %p \n", &a);  // pointer pointing to a variable memeory
16	    printf("pointer address &p: %p \n", &p); // pointer memeory
17	    printf("pointer address p: %p \n", &c);  // pointer memeory
18          free(p);                                 // releasing the memory;  become dangling pointer
            p = NULL;                                // avoid dangling pointer with null allocation;
            struct a1 *l1 = (struct a1*)malloc(sizeof(struct a1));   // Dynamic memory allocation with 'malloc'to the structure 
19	    l1->data = 122;
20	    l1->test = NULL;
21	    if (l1->test == NULL)
22	    {
23	        printf("memory allocated \n");
24	    }
25	    else {printf("memory not allocated \n"); }
26	    printf("fdd %d", l1->data);
27	    
28	    l1->test =  (struct a1*)malloc(sizeof(struct a1));
29	    l1->test->data = 1122;
30	    printf("fdd %d", l1->test->data);
31	
32	    return 0;
33	}

output :
```
![image](https://github.com/user-attachments/assets/66917031-4b0d-4ef0-b013-ad4429f13bee)

```c 
#include <stdio.h>

int main() {
	  int x[] = {10, 20, 30};
	  int* p = &x[1]; // pointer into middle
	  char* fruit[3] = {"apples  jknd",     // note : the space will be '' '' like this
						//only end of the string will be allocate '\0'  refer the below image
	                    "bananas", 
	                    "cherries"};
	
	  printf("I have %d %s\n", *p, fruit[1]);
	return 0;
}
output :
```
![Screenshot from 2025-01-05 12-19-13](https://github.com/user-attachments/assets/d79244a1-0477-4c59-b677-bbc1551d7478)

The program return the number of repeated characters and which character is most repeated in the given string

# srting swap
``` c
// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

int main() {
    // Write C code here
   char str[30] ;
   //gets(str);
   fgets(str, sizeof(str), stdin);
   int l=strlen(str);
   for(int i=0; i<l/2; i++)
   {
       char swp = str[i];
       str[i] = str[l-i-1];
       str[l-i-1]= swp;
   }
   printf("%s", str);
    return 0;
}
o/p : dsdklsjfd
dfjslkdsd
```
### bit swapping in c
``` c
#include <stdio.h>
#include <stdint.h>
//swap bit 17 with bit 25 in a 64bit integer  ==> 17 =0 25 =1;
 
int main()
{
    uint64_t a =0x700ae, temp1, temp2; // 000{0} 0000 011{1} 0000 0000 1010 1110
    printf("%lx\n", a);
    int swap_bit1, swap_bit2 ;
    swap_bit1 = ( a>>17) & 1;
    swap_bit2 = (a >> 25) & 1;
    printf("swap_bit1 :%x\n", swap_bit1);
    printf("swap_bit2 :%x\n", swap_bit2);
    if ( swap_bit2 == swap_bit1)
        {
            printf("%lx \n", a);
            return 0 ;
        }
    else
    {
        //a = (a^(1 << 25));   // this two line ok
        //a = (a^(1 << 17));   // this two line ok
        a ^= (1 << 25) | (1 << 17);  // this is also fine 
    }   

    printf("%lx \n", a);
    return 0;
}

output :
	700ae
	swap_bit1 :1
	swap_bit2 :0
	20500ae 
```
### bit swapping in C++ cog tech ser
```cpp
#include <iostream>
#include <bitset>

int main()
{
    uint64_t a = 0x700ae; // 0000 0000 0000 0111 0000 0000 1010 1110
    printf("Before swap: %lx\n", a);

    int swap_bit1 = (a >> 17) & 1;  // Extract bit 17
    int swap_bit2 = (a >> 25) & 1;  // Extract bit 25

    printf("Bit 17: %x\n", swap_bit1);
    printf("Bit 25: %x\n", swap_bit2);

    // If the bits are different, toggle them
    if (swap_bit1 != swap_bit2)
    {
        a ^= (1ULL << 17);  // Toggle bit 17
        a ^= (1ULL << 25);  // Toggle bit 25
    }

    printf("After swap: %lx\n", a);
    return 0;
}
output

Before swap: 700ae
Bit 17: 1
Bit 25: 0
After swap: 20500ae
```
```c
#include <stdio.h>
#include <math.h>
// eg.  Input : 198701, output: 198711
// Swap the zeros in a given number to 1
int updateNum(int gNum,int changeNum, int upNum )
{
    int tempNum, count=0;
    tempNum = gNum ;
    while (gNum)
    {
        if(gNum%10 == changeNum)
        {
          tempNum = (tempNum + pow(10, count) )- (pow(10,count) *changeNum);  // ==> tempNum == 198700 +
          //printf ("%d\n", tempNum);
        }
        gNum = gNum/10;
        count++;
    }
    return tempNum;
}

int main()
{
    int num = 178707, cc =0;
    printf("Given No : %d\n", num);
    printf("Updated No : %d\n", updateNum(num, 7, 1));
    return 0;
}

```
### reverse the given string
```c
// reverse the given string
// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

void swap(char *s1, char *s2)
{
    char tmep = *s1;
    *s1=*s2;
    *s2=tmep;
} 
void reveseString(char str[])
{
    printf("%s\n", str);
    int len = strlen(str);
    printf("%d \n", len);
     char tmep;
    for (int i=0; i<len/2; ++i)
    {
        //tmep = str[i];
        //str[i] = str[len-i-1];
        //str[len-i-1] = tmep;
        swap (&str[i], &str[len-i-1]);
    }
    printf("%s\n", str);
}

int main() {
    // Write C code here
    printf("Try programiz.pro \n ");
    char str[] = "abcefgh";
    reveseString(str);
    
    return 0;
}


You're passing char *str[], which is actually interpreted as char **str (pointer to pointer).

But in main() you are passing char str[] = " Thangaraj";, which is a char* (pointer to char), not an array of pointers.
    char str[] = " Thangaraj aks";
    printf("%s \n", str);
    reverseof(str);
    printf("%s \n", str);

void reverseof(char str[])
{
    int len = strlen(str);
    printf("length of str : %d \n", len);

here passsing You're passing char *str[], which is actually interpreted as char **str (pointer to pointer).

this way also fine
void reverseof(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
```
```c
// C program for implementation of selection sort
#include <stdio.h>

void selectionSort(int arr[], int N) {

    // Start with the whole array as unsored and one by
      // one move boundary of unsorted subarray towards right
    for (int i = 0; i < N - 1; i++) {

        // Find the minimum element in unsorted array
        int min_idx = i;
        for (int j = i + 1; j < N; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first
        // element in the unsorted part
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}


int main() {
    int arr[] = {64, 25, 12, 22, -4, 11};
    int N = sizeof(arr) / sizeof(arr[0]);
    printf("Unsorted array %d: \n",N);
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
  
      // Calling selection sort
    selectionSort(arr, N);

    printf("Sorted array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
    

```


```c

// it is for adc voltage conversation 

#include <stdio.h>

#define V_REF 2.0       // ADC reference voltage (scaled)
#define ADC_MAX 1023    // 10-bit ADC max value
#define SCALE_FACTOR 5.0  // Scaling from 2V to 12V

// Function to convert ADC value to actual voltage
float adc_to_voltage(int adc_value) {
    return (adc_value * V_REF / ADC_MAX) * SCALE_FACTOR;
}

int main() {
    int adc_value = 512;  // Example ADC value

    float actual_voltage = adc_to_voltage(adc_value);
    printf("ADC Value: %d\n", adc_value);
    printf("Actual Input Voltage: %.2f V\n", actual_voltage);

    return 0;
}


```

```c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100  // Adjust based on expected unique strings

typedef struct {
    char *word;
    int count;
} HashEntry;

HashEntry hashTable[MAX];  // Simple hash table
int hashSize = 0;

void insert_to_hash(char *str) {
    for (int i = 0; i < hashSize; i++) {
        if (strcmp(hashTable[i].word, str) == 0) {
            hashTable[i].count++;
            return;
        }
    }
    hashTable[hashSize].word = str;
    hashTable[hashSize].count = 1;
    hashSize++;
}

void find_duplicates(char *arr[], int size) {
    for (int i = 0; i < size; i++) {
        insert_to_hash(arr[i]);
    }

    printf("Duplicate strings: ");
    for (int i = 0; i < hashSize; i++) {
        if (hashTable[i].count > 1) {
            printf("%s ", hashTable[i].word);
        }
    }
    printf("\n");
}

int main() {
    char *arr[] = {"apple", "banana", "cherry", "apple", "date", "banana"};
    int size = sizeof(arr) / sizeof(arr[0]);

    find_duplicates(arr, size);
    return 0;
}


```


```c

#include <stdio.h>
#include <string.h>

void find_duplicates(char *arr[], int size) {
    printf("Duplicate strings: ");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(arr[i], arr[j]) == 0) {  // Compare strings
                printf("%s ", arr[i]);
                break;  // Avoid multiple prints of the same duplicate
            }
        }
    }
    printf("\n");
}

int main() {
    char *arr[] = {"apple", "banana", "cherry", "apple", "date", "banana"};
    int size = sizeof(arr) / sizeof(arr[0]);

    find_duplicates(arr, size);
    return 0;
}


```

#### To print the duplicate is present in the array;
```c
#include <stdio.h>
#define MAX 100  // Adjust according to input range

void find_duplicates(int arr[], int size) {
    int hash[MAX] = {0};  // Hash table to store frequencies
    
    printf("Duplicate elements: ");
    for (int i = 0; i < size; i++) {
        hash[arr[i]]++;
        if (hash[arr[i]] == 2) {  // Print only when a duplicate is found
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 3, 4, 2, 5, 3, 6, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    find_duplicates(arr, size);
    return 0;
}


```
#### array print dulicate, max repeated, remover the duplicate, assign with same array
``` c
#include <stdio.h>
#define MAX 100  // Adjust if input range is larger

// Function to process array
void analyze_array(int arr[], int *size) {
    int hash[MAX] = {0};
    int max_count = 0;
    int max_element = -1;

    printf("Duplicate elements: ");
    for (int i = 0; i < *size; i++) {
        hash[arr[i]]++;
        if (hash[arr[i]] == 2) {
            printf("%d ", arr[i]);
        }
        if (hash[arr[i]] > max_count) {
            max_count = hash[arr[i]];
            max_element = arr[i];
        }
    }
    printf("\n");

    printf("Element with max frequency: %d (repeated %d times)\n", max_element, max_count);

    // Modify the array to remove duplicates
    int printed[MAX] = {0};
    int new_index = 0;

    for (int i = 0; i < *size; i++) {
        if (!printed[arr[i]]) {
            arr[new_index++] = arr[i];
            printed[arr[i]] = 1;
        }
    }

    *size = new_index;

    // Print the modified array without duplicates
    printf("Array without duplicates: ");
    for (int i = 0; i < *size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 3, 4, 2, 5, 3, 6, 2, 3, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    analyze_array(arr, &size);

    // Optional: use the modified array
    printf("Modified original array (in main): ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

```

#### To print binary and decimal values vice versa 

```c
    int bibpr = 0b11111111 ;
    printf ("%b", bibpr);  

    // output is : 11111111 

    
    int bibpr = 0b11111111 ;
    printf ("%d", bibpr);
    // output is 255

    
    int bibpr = 255;
    printf ("%b", bibpr);

    // output is 1111111

    int bibpr = 0x255;
    printf ("%b", bibpr);

    // output is 1001010101
    
```
### to find the machine is 64 or 32 bit
```c
// to find the machine is 64 or 32 bit

#include <stdio.h>

int main() {
    if (sizeof(void*) == 8) {
        printf("64-bit machine\n");
    } else if (sizeof(void*) == 4) {
        printf("32-bit machine\n");
    } else {
        printf("Unknown architecture\n");
    }
    return 0;
}

// case 2:

#include <stdio.h>

int main() {
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__ppc64__)
    printf("64-bit machine\n");
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__) || defined(__ppc__)
    printf("32-bit machine\n");
#else
    printf("Unknown architecture\n");
#endif
    return 0;
}

case 3:
//Checking sizeof(long) or sizeof(size_t)

#include <stdio.h>

int main() {
    printf("Size of long: %lu bytes\n", sizeof(long));
    printf("Size of size_t: %lu bytes\n", sizeof(size_t));

    if (sizeof(long) == 8) {
        printf("64-bit machine\n");
    } else {
        printf("32-bit machine\n");
    }
    return 0;
}
```


``` c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

struct my_request {
    int a;
    char b[10];
    void *ptr;
};

int main()
{
    struct my_request req;
    memset(&req, 0, sizeof(req));
    req.ptr = (int*)malloc(sizeof(int));
    //req.ptr = (char*)malloc(sizeof(char));
    //*req.ptr = 'a';   // it will not work;
    // *(char *)(req.ptr) = 'a';
    //printf("%p--- %x", (char *)(req.ptr), *(char *)(req.ptr));
    *(int *)(req.ptr) = 100;
    printf("%x -- %x -- %p--- %x", req.a, req.b[0],(int *)(req.ptr), *(int *)(req.ptr));
    return 0;
}
### else if (strncmp(argv[0], "time", 4) //string compare of 4 th word and time and argv[0] ;

```
### string of the word in a senstense reverse
``` c
	#include <stdio.h>
	#include <string.h>
	
	#define MAX_WORDS 100
	#define MAX_LENGTH 100
	
	int main() {
	    char str[] = "hi hello thanga pla";
	    char *words[MAX_WORDS];
	    int count = 0;
	
	    // Tokenize the string into words
	    char *token = strtok(str, " ");
	    while (token != NULL && count < MAX_WORDS) {
	        words[count++] = token;
	        token = strtok(NULL, " ");
	    }
	
	    // Print words in reverse order
	    for (int i = count - 1; i >= 0; i--) {
	        printf("%s", words[i]);
	        if (i > 0) printf(" ");
	    }
	    printf("\n");
	
	    return 0;
	}
```
### c pthread_t
``` c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func1(void* arg) {
    while (1) {
        printf("Thread 1 running\n");
        sleep(1);
    }
    return NULL;
}

void* thread_func2(void* arg) {
    while (1) {
        printf("Thread 2 running\n");
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create both threads
    pthread_create(&t1, NULL, thread_func1, NULL);
    pthread_create(&t2, NULL, thread_func2, NULL);

    // Optional: if you want main to wait for them later
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);

    // Instead, keep main alive so threads keep running
    while (1) {
        printf("Main thread doing something...\n");
        sleep(3);
    }

    return 0;
}
```
### first letter has to take capitalize
```c
#include <stdio.h>
#include <string.h>

//#define Max 50

int main()
{
    char a ='a';
    char ac = 'A';
    printf("%d-%d = %d\n",a,ac ,(a-ac));

    char str[] = "hello today is wenesday";
    int flag =0;
    int size = sizeof(str)/sizeof(str[0]);
    for (int i=0; i<size;i++)
    {
        if (i==0 || flag ==1)
        {
            str[i]= str[i]-32;
            flag=0;
        }
        if (str[i] == ' ')
        {
            flag=1;
        }
    }
    printf("%s", str);
    return 0;
}

```
## Reverse the number like 12345 to 54321
``` c
// reverse the number like 12345 to 54321 ;

#include <stdio.h>

int main()
{
    int a = 12345;
    int ret, rev=0;
    while(a)
    {
        ret = a%10;
        rev = rev*10 + ret;
        // rev = rev * 10 + a % 10;
        a= a/10;
        
    }
    
    printf("%d", rev);
    return 0;
}
```
## Recursion for factrial part
``` c
#include <stdio.h>
int facto(int n)
{
     if (n==0)   // recurtion stop condition
     {
         return 1;
     }
     return n*facto(n-1);  // this the recursion
}

int main() {
    int n=5;
    printf("%d", facto(n));
    return 0;
}
```
## Armstrong number or not.
``` c

int main()
{
    struct InchFeet arr[]
        = { { 11, 5.1 }, { 13, 4.5 }, { 6, 8.1 } };

    int N = sizeof(arr) / sizeof(arr[0]);

    findSum(arr, N);

    return 0;
}
```
### void pointer

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

struct my_request {
    int a;
    char b[10];
    void *ptr;
};

int main()
{
    struct my_request req;
    memset(&req, 0, sizeof(req));
    req.ptr = (int*)malloc(sizeof(int));
    //req.ptr = (char*)malloc(sizeof(char));
    //*req.ptr = 'a';   // it will not work;
    // *(char *)(req.ptr) = 'a';
    //printf("%p--- %x", (char *)(req.ptr), *(char *)(req.ptr));
    *(int *)(req.ptr) = 100;
    printf("%x -- %x -- %p--- %x", req.a, req.b[0],(int *)(req.ptr), *(int *)(req.ptr));
    return 0;
}

normally
/********************************************************************
void *ptr;           // Generic pointer
int a = 10;
ptr = &a;            // Assign address of int to void pointer

printf("%d\n", *(int *)ptr);   // Cast to int* before dereferencing

//also method call
void printValue(void *data, char type)
{
    if (type == 'i') {
        printf("Integer: %d\n", *(int *)data);   // here for print the data as interger
    } else if (type == 'f') { 
        printf("Float: %f\n", *(float *)data);   // here for print the data as float
    } else if (type == 'c') {
        printf("Char: %c\n", *(char *)data);   // here for print the data as char
    }
}


********************************************************************/
```
###  if (strncmp(argv[0], "time", 4) == 0)  // string compare time

### fprintf(stderr, "Usage: %s sensornumber\n", argv[0]);

``` bash

fprintf() is a function that prints formatted text.

stderr is the file stream representing the error output.

"Usage: %s sensornumber\n" is the format string.

argv[0] is the name of the program (usually the command used to run it).

Usage: ./myprogram sensornumber

```
## advanced Pointer 
```c
void fun(int *p) 
{ 
  int q = 10; 
  p = &q; 
}     
  
int main() 
{ 
  int r = 20; 
  int *p = &r; 
  fun(p); //here assigned pointer value to passing parameter. it is not getting back of any value.
  printf("%d", *p); 
  return 0; 
}
a:10  b:20  c: compiler error d: runtime error
But the o/p is 20 only.
/*
Inside fun(), q is a copy of the pointer p. So if we change q to point something else then p remains uneffected.
If we want to change a local pointer of one function inside another function, then we must pass pointer to the pointer.
By passing the pointer to the pointer, we can change pointer to point to something else. See the following program as an example.
*/
void fun(int **pptr) // pointer to pointer
{
  static int q = 10;
  *pptr = &q;     
}

int main()
{
  int r = 20;
  int *p = &r;
  fun(&p);    // reference send;
  printf("%d", *p);
  return 0;
}
/*
here o/p is : 10 
In the above example, the function fun() expects a double pointer (pointer to a pointer to an integer).
Fun() modifies the value at address pptr.  The value at address pptr is pointer p as we pass address of p to fun().
In fun(), value at pptr is changed to address of q.  Therefore, pointer p of main() is changed to point to a new variable q.
Also, note that the program won’t cause any out of scope problem because q is a static variable.
Static variables exist in memory even after functions return.
For an auto variable, we might have seen some unexpected output because auto variable may not exist in memory after functions return.
*/
```
### 2d pointer array
```c
#include <stdio.h>

#define R 2
#define C 3

int main()
{
    int matrix[R][C] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int (*p)[R][C] = &matrix;

    // Accessing elements using pointer
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%d ", (*p)[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// one more example 

#include <stdio.h>

#define R 10
#define C 20

int main()
{
   int (*p)[R][C];   
   printf("%ld",  sizeof(*p));   // return 800
   getchar();
   return 0;
}

/*
int *p[R][C];  	// p is a 2D array (of size [R][C]) of pointers to int.
               	// Array of int pointers (e.g. each row/column points elsewhere)
		// Each p[i][j] points to a different int (can be anywhere in memory).

int (*p)[R][C];  // p is a pointer to a 2D array of size [R][C] of int.
		//  Pointer to a real 2D array
		//  A contiguous 2D array in memory, and p points to the whole block.
*/
| Situation                                     | Use               |
| --------------------------------------------- | ----------------- |
| Each element points to different `int` values | `int *p[R][C];`   |
| You want to pass or manipulate a 2D array     | `int (*p)[R][C];` |

```
### Remove the special character in  the string 

``` c
#include <stdio.h>
#include <string.h>
void stringValue(char *str)
{
    int i, j = 0;
    for(i=0; str[i] != '\0'; i++)
    {
        if (str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z')
        {
           // printf("%c",get[i]);
           str[j++]=str[i];
        }
    }
    str[j] = '\0';
}

int main()
{
    char str[] ="&Hel&&*lo*(Worl*d";
    printf("%s \n", str);
    stringValue(str);
    printf("%s \n", str);
    return 0;
}
```

### git update patch

``` c

git add *
git commit -m "phosphorSoftManager"
git format-patch HEAD~1
Then it will generate patch under this foder
0001-phosphorSoftManager.patch
```

## https://bhanuprakasheagala.hashnode.dev/process-creation-in-linux
## i2ctransfer -f -y 6 w16@0x21 0x01 0x02 0x03 0x04 0x12 0x13 0x14 0x16 0x33 0x64 0x71 0x21 0x22 0x02 0x03 0x04
## i2ctransfer 6 wr 3@0x21 0x12 0x34 0x56
## ipmievd -C 17 -H 192.168.1.53 -I lanplus -U root -P 0penBmc sel daemon pidfile=/var/run/ipmievd.pid


``` cpp
1.usb drivers installation and how many ways are there to install USB 
2.dual video 
3.graphics installation 
4.directx 
5.graphic cards and tools used 
by burning tool for stress and stability ( ram,rom, 
directly we can install bios/change in bios settings ( ifwi) 
6.dediprog (flash cpld,ifwi) 
 
7.dangling pointer 
8.segmentation fault 
9.file systems 
10.deadlock 
11.page table 
12.function pointer and example to it 
13.stack and queue and example 
14.push and pop 
15.zoombie process 
16.critical section 
17.semaphore and mutex 
18.locking mechanism 
19.recursive function and compare between functions 
 
 
(Parikshit Shukla) 
Introduction 
Difference Between Class and structure 
Difference between Struct and union 
What is File-System 
What is DMA 
What are interrupts and its types 
What is Page-Table 
What is Deadlock 
Essential conditions for deadlock 
What is Cache memory 
Size of Cache Memory 
Real time scenario of cache memory 
About microcontrollers, how many address spaces in 8051? 
What are bitwise operators and its types 
Why we use bitwise operators 
What is dangling pointer 
What is break statement in C 
WAP TO SWAP TWO NUMBERS IN C 
What is extern keyword, its scope and lifetime 
Why we use algorithms in our program? 
Explain System booting process 
What is preprocessor, how to add another c file in a program 
What is typedef 
What is ternary operator 
Static and Global variable difference 
Difference between Single and double linked list 
What is OpenGL 
Why do we need IDE? 
What is breakpoint 
What is logfile 
How to import libraries in Python? 
WAP to find a number is even or odd in Python? 
Difference between list and tuple 
Difference between array and list 
About Project 
What is os.sep? 
How to include library which is not present in directory in Python? 

Kernel Driver Adds
Add the Kconfig at respective folder the placing new drivers
Add Makefile of the driver in the respective folder the placing new drivers
 
arch/arm/boot/linux/config file adding that names TBT
 
patch -p1 < ~/Downloads/ipmi-device.patch
 

```
