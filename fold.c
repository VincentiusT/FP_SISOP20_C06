#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];
const char *inside;

void fold(int limit, int fd){
  int n;
  n = read(fd, buf, sizeof(buf));
  inside = buf;
  int length = strlen(inside);

  for(int i=0;i<length;i++){
    printf(1,"%c",inside[i]);
    if((i+1)%limit==0)printf(1,"\n");
  }
  printf(1,"\n");
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  int fd;

  if(argc <= 2){
    printf(1,"Argumen Salah\n");
    exit();
  } 
  const char *temp = argv[1];

  if(temp[0]=='-' && temp[1]=='w'){
      if((fd=open(argv[2], 0))<0){
          printf(1,"cannot open\n");
          exit();
      }
      int limit=0;
      if(strlen(temp)==3){
        limit = atoi(&temp[2]);
      }
      else if(strlen(temp)==4){
        int t1;
        t1 = atoi(&temp[2]);
        limit = t1;
      }
      fold(limit, fd);
  }
  exit();
}
