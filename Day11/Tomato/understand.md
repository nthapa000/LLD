*  We have divided the code into modules

* .h extension is used for header file in C++

### Concept of Header Guard

* a mechanism used in C++ to prevent a header file from being included multiple times during compilation.

* You have a file Restaurant.h with a class definition

<!-- ```cpp// ```  -->

```cpp
// Restaurant.h
class Restaurant {
public:
    void serveFood();
};

``` 
* Now include this file in two other files
```cpp
// File1.cpp
#include "Restaurant.h"
```
```cpp
// File1.cpp
#include "Restaurant.h"
```

*  We have a third file,main.cpp, that includes both of those
```cpp
// main.cpp
#include "File1.cpp"
#include "File2.cpp"
```
* Now here's the problem:
main.cpp ends up including Restaurant.h twice — once through File1.cpp and once through File2.cpp.

* Without them, the compiler may see duplicate class/function/variable declarations, and throw errors.

#### Specially important in the large projects

In big projects:
We have many .cpp and .h files.
* Multiple files include the same headers.
* Indirect inclusions (A includes B, B includes C, etc.) are very common.

Without header guards (or alternatives),we will almost always get multiple definition errors.