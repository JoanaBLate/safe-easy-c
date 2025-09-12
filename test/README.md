
### Compiling and running the SafeEasyC library test suite in Linux

Inside the folder "test":

~~~ bash
gcc test.c -o test -Wall -Wextra -Wpedantic -Wvla -Wsign-conversion -fsanitize=address
./test
~~~ 
 
It should compile without warnings, and run fine.

Note: the flag "-fsanitize=address" makes the executable file slow.
