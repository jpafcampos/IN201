//definir ici les prototypes des fonctions

#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>

//on utilise la syntaxe AT&T pour l'assembleur

#define STACK_SIZE 4096

char pile1 [STACK_SIZE];
char pile2 [STACK_SIZE];
char pile3 [STACK_SIZE];
char pile4 [STACK_SIZE];

typedef void * coroutine_t;

coroutine_t init_coroutine(void *stack_begin, unsigned int stack_size,
void (*initial_pc)(void))
{
char *stack_end = ((char *)stack_begin) + stack_size;
void **ptr = stack_end;
ptr--;
*ptr = initial_pc;
ptr--;
*ptr = stack_end; //rbp
ptr--;
*ptr = 0;
ptr--;
*ptr = 0;
ptr--;
*ptr = 0;
ptr--;
*ptr = 0;
ptr--;
*ptr = 0;

return ptr;
}

void tester(){
    int counter = 0;
    while(1){
        printf("counter : %d\n", counter);
        counter++;
    }
}

int main(){
    coroutine_t cor = init_coroutine (pile1, STACK_SIZE, tester);

    return 0;
}