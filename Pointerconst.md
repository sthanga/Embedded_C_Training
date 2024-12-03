# TYPES OF POINTER with const
### const int *p;     ->
### int const *p;     ->
### int *const p;     ->
### const int const *p   ->
### const int *const p   ->


## const int *p

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
