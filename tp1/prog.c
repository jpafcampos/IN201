#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

struct fs_header
{
    uint64_t rom1fs;
    uint32_t fullsize;
    uint32_t checksum;
    uint32_t volume_name;
};


void decode(struct fs_header *p, size_t size)
{
    char *str = p->rom1fs;
    printf("%s\n", &str);
}

uint32_t big_to_litte(char*addr) 
{
  char temp[4]; // char possui 1 byte, portanto char[4] possui 4 bytes=32b
  int i;
  for (int i = 0; i < 4; i++)
  {
    temp[i] = addr[4 - i - 1];
  }
  return (uint32_t)temp;
  
}

int round(int val) {
  return (val %16 == 0) ? val : (val + 16 - (val % 16));
}

int main(void)
{
    int fd = open("tp1fs.romfs", O_RDONLY);
    assert(fd != -1);
    off_t fsize;
    fsize = lseek(fd, 0, SEEK_END);
    //
    printf("size is %d", fsize);
    char *addr = mmap(addr, fsize, PROT_READ, MAP_SHARED, fd, 0);
    assert(addr != MAP_FAILED);
    decode(addr, fsize);
    return 0;
}