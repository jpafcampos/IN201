#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>

struct block{
  size_t size;
  struct block *next;
  int free;
  int magic; // For debugging only. TODO: remove this in non-debug mode.
};


#define _Q1_

#ifdef _Q1_
char tas[16*1024];
char *tas_ptr = tas;
long fin_tas = tas + 16*1024;

void * memalloc(int size){
    if (tas + size > fin_tas){
        printf("erreur : plus de memoire disponible\n");
        return;
    }
    char *memallouee = tas + size;
    //printf("%p\n", memallouee);
    tas_ptr = memallouee;
    return tas_ptr;
}
#endif


int main (int argc, char *argv[]){
    //printf("%p\n", tas_ptr);
    //memalloc(24);
    //printf("%p\n", tas_ptr);
    memalloc2(4);
}