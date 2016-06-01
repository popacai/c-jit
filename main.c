#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>


void test_foo(int* a, int* b);
unsigned char* read_foofunc();

int main() {
    int* a;
    int* b;
    int d;
    unsigned char* buffer;
    a = (int*)malloc(sizeof(int));
    b = (int*)malloc(sizeof(int));
    *a = *b = 1;
    printf("a=%u, b=%u\n", a, b);
    printf("*a=%u, *b=%u\n", *a, *b);
    test_foo(a, b);

    read_stdin_and_compile();

    unsigned char* shell = read_foofunc();
    //buffer = (unsigned char*) malloc(1024);
    buffer = (unsigned char*) valloc(1024);

    memcpy(buffer, shell, 1024);
    if (d = mprotect(buffer, 1024, PROT_EXEC | PROT_WRITE)) {
        printf("error=%d\n", errno);
    }

    int* (*func)() = (void*)buffer;
    printf("foo_func = %u\n", test_foo);
    printf("func = %u\n", func);
    *a += *b;

    (*func)(a, b);
    printf("*a=%u, *b=%u\n", *a, *b);

    free(buffer);
    free(a);
    free(b);

    return 0;
}

unsigned char* read_foofunc() {
    char* filename = "./runner";
    int i;
    unsigned char* buffer;
    buffer = (unsigned char*) malloc(1024);
    FILE* fp = fopen(filename, "r+");
    fseek(fp, 0x474, SEEK_CUR);
    fread(buffer, 1024, 1, fp);
    for (i = 0; i < 16; i++) {
        printf("%02x ", *(buffer + i));
    }
    printf("\n");
    fclose(fp);
    return buffer;
}

int read_stdin_and_compile() {
    char buffer [1024];
    char* headers = "#include <stdio.h>\n";
    char* main_def = "int main() { \n";
    char* main_end = "return 0; } \n";
    scanf("%[^\n]s", buffer);
    printf("%s\n", buffer);

    char* new_string = malloc(10240);
    char* offset = new_string;
    strcpy(offset, headers);
    offset += strlen(headers);
    strcpy(offset, main_def);
    offset += strlen(main_def);
    strcpy(offset, buffer);
    offset += strlen(buffer);
    strcpy(offset, main_end);
    offset += strlen(main_end);

    printf("%s\n", new_string);
    FILE* f = fopen("runner.c", "w");
    fprintf(f, new_string, strlen(new_string));
    fclose(f);
    system("gcc runner.c -o runner");
    free(new_string);
    return 0;
}

void test_foo(int* a, int* b) {
    *a += *b;
}
