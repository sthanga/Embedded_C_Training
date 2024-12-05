# TYPES OF POINTER with const
### 1. const int *p;     -> constant to pointer
### 2. int const *p;     -> constant to pointer
### 3. int *const p;     -> constant pointer 
### 4. const int const *p   -> pointer constant
### 5. const int *const p   -> constant to contant pointer

### constant pointer. 
### pointer to constant.
### constant pointer to constant.

## 1.  const int *p   (constant to pointer)

```cpp
/*
          const int            *P
             ^                  ^
             ^                  ^
             ^                  ^
    variable is constant    pointer is not constant
    or not
*/
#include <iostream>
int main()
{
    const int a = 10;
    const int *p ;   // const variable assign with const pointer only;
    p = &a ;  
    std::cout<<"address of a = " << p << std::endl;
    int b =20;
    p = &b;  // pointer is not constant so we can assing any variable at any time;
             // constant pointer can get assign constant variable and non constant variable
    std::cout<<"address of b = " << p << std::endl;
    return 0;
} 
``` 

```bash
output :
   address of a = 0x7ffc812ca408
   address of b = 0x7ffc812ca40c
```

## 2. int const *p   (constant to pointer)
```cpp
/*
          int const            *P
             ^                  ^
             ^                  ^
             ^                  ^
    variable is constant    pointer is not constant
    or not
*/
#include <iostream>

int main()
{
    const int a = 10;
    int const *p ;   // const variable assign with const pointer only;
                    //  here pointer is not constant, but variable is constant i.e int const;  above part also same
    p = &a ;  
    std::cout<<"address of a = " << p << std::endl;
    
    int b =20;
    p = &b;  // pointer is not constant so we can assing any variable at any time;
             // constant pointer can get assign constant variable and non constant variable
    std::cout<<"address of b = " << p << std::endl;
    return 0;
}
```
``` bash
output:
   address of a = 0x7ffdf18b3db8
   address of b = 0x7ffdf18b3dbc
```
## 3. int *const p;     -> constant pointer 

```cpp
/*
          int *              const P
             ^                  ^
             ^                  ^
             ^                  ^
    variable is not constant    pointer is constant
    
*/
#include <iostream>

int main()
{
    int a = 10;
    int * const p  = &a; // const variable assign with const pointer only;
                         //  here pointer is not constant, but variable is constant i.e int const;
    //p = &a ;  // we cant assign after intialization  
    std::cout<<"address of a = " << p << std::endl;
    
    //int b =20; // another variable cannot assign after initialization , throw error;
    //p = &b;  // pointer is not constant so we can assing any variable at any time;
             // constant pointer can get assign constant variable and non constant variable
    // std::cout<<"address of b = " << p << std::endl;
    return 0;
}
```
``` bash

```
