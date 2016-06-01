memory changes:
$ make test
./t
a=17055760, b=17055792
*a=1, *b=1
foo_func = 4197724
int* g; g=17055760; *g=100; g=17055792; *g=200;
int* g; g=17055760; *g=100; g=17055792; *g=200;
#include <stdio.h>
int main() {
    int* g; g=17055760; *g=100; g=17055792; *g=200;return 0; }

runner.c: In function ‘main’:
runner.c:3: warning: assignment makes pointer from integer without a cast
runner.c:3: warning: assignment makes pointer from integer without a cast
55 48 89 e5 48 c7 45 f8 10 40 04 01 48 8b 45 f8
*a=100, *b=200


run a function
$ make test
./t
a=38256656, b=38256688
*a=1, *b=1
foo_func = 4197724
int*(*func)() = 4197724;(*func)(38256656,38256688);
int*(*func)() = 4197724;(*func)(38256656,38256688);
#include <stdio.h>
int main() {
    int*(*func)() = 4197724;(*func)(38256656,38256688);return 0; }

runner.c: In function ‘main’:
runner.c:3: warning: initialization makes pointer from integer without a cast
55 48 89 e5 48 83 ec 10 48 c7 45 f8 5c 0d 40 00
*a=2, *b=1
