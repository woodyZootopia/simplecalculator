#include <stdio.h>
#include <ctype.h>

static char *p;

static int eval() {
  if(isdigit(*p)) {
    int val = *p-'0';
    p++;
    while(isdigit(*p)) {
      val = val*10 + *p-'0';
      p++;
    }
    return val;
  }
  p++;
  return 0;
}

int main(int argc, char **argv) {
  p=argv[1];
  if(argc!=2){
  printf("input not one\n");
  return 0;
  }
  while(*p) printf("%d\n",eval());
  return 0;
}
