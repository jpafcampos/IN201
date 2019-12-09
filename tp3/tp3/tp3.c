#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>


#define STACK_SIZE 4096
typedef void * coroutine_t;
void switch_coroutine(coroutine_t *p_from, coroutine_t to);
void enter_coroutine(coroutine_t cr);

//pilhas
char pile1[STACK_SIZE];
char pile2[STACK_SIZE];
char pile3[STACK_SIZE];
char pile4[STACK_SIZE];

//estruturas de dados
struct Thread
{
    coroutine_t *cor;
    int status; //prêt = 1
};


//variaveis globais
coroutine_t cor1, cor2;
coroutine_t cor_maitre;
coroutine_t th_courant;
struct Thread T1, T2, T3;


//metodos
void yield(void){
    switch_coroutine(&th_courant, cor_maitre);
}

void t1(){
    int t = 0;
    while (1)
    {
        printf("i'm thread 1; %d",t++);
        if (t % 3 == 0)
            yield();
    }
}

void t2(){
    int t = 0;
    while (1)
    {
        printf("i'm thread 2; %d",t++);
        if (t % 3 == 0)
            yield();
    }
}

void t3(){
    int t = 0;
    while (1)
    {
        printf("i'm thread 3; %d",t++);
        if (t % 3 == 0)
            yield();
    }
}

void teste(){
    int t = 0;
    while (1){
        printf("hello, world #%d\n", t);
        t++;
        //getchar();
        switch_coroutine(&cor1, cor2);
    }
}

void teste2(){
    int t = 0;
    while (1){
        printf("salut le monde #%d\n", t);
        t++;

        //getchar();
        switch_coroutine(&cor2, cor1);
    }
}

coroutine_t init_coroutine(void *stack_begin, unsigned int stack_size, void (*initial_pc)(void)){
    
    char *stack_end = ((char *)stack_begin) + stack_size;
    void **ptr = (void*)stack_end;

    *ptr = initial_pc;  //haut de la pile
    ptr--;
    *ptr = stack_end; //rbp
    ptr--;
    *ptr = 0;       //rbx
    ptr--;
    *ptr = 0;   //r12
    ptr--;
    *ptr = 0;   //r13
    ptr--;
    *ptr = 0;   //r14
    ptr--;
    *ptr = 0;   //r15


    return ptr;
}


struct Thread thread_create(void * func){
   struct Thread th;
   th.cor = init_coroutine(pile1, STACK_SIZE, func);
   th.status = 1;
   return th;  
}

void maitre(){
    if(th_courant == T1.cor){
        switch_coroutine(&th_courant, T2.cor);
    }
    else if(th_courant == T2.cor){
        switch_coroutine(&th_courant, T3.cor);
    }
    else{
        switch_coroutine(&th_courant, T1.cor);
    }
}

int main(){
    /*cor1 = init_coroutine(pile1, STACK_SIZE, teste);
    cor2 = init_coroutine(pile2, STACK_SIZE, teste2);
    enter_coroutine(cor1);
    */
printf("oi");
    T1 = thread_create(t1);
    printf("oi");
    T2 = thread_create(t2);
    printf("oi");
    T3 = thread_create(t3);
    printf("oi");
    th_courant = T1.cor;
    printf("oi2");
    cor_maitre = init_coroutine(pile4, STACK_SIZE, maitre);
    printf("oi3");
    enter_coroutine(th_courant);
    printf("oi");

    return 0;
}