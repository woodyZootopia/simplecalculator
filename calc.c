#include <stdio.h>
#include <ctype.h>
#include <string.h>

static char *p;

static int skipspace(){
  while(isspace(*p)) p++;
  return 0;
}

static int evalint() {
  int val=0;
  while(isdigit(*p) || *p == '*' || *p == '/') {
    switch (*p) {
      case '*':
        p++;
        skipspace();
        val*=evalint();
        break;
      case '/':
        p++;
        skipspace();
        val/=evalint();
        break;
      default:
        val = *p-'0';
        p++;
        while(isdigit(*p)){
          val = val*10 + *p-'0';
          p++;
        }
    }
    skipspace();
  }
  return val;
}

static int eval() {
  skipspace();
  if(isdigit(*p)) {
    int val = evalint();
    skipspace();
    while(*p == '+' || *p == '-') {
      if (*p == '+'){
      p++;
      skipspace();
      val += evalint();
      }
      else {
      p++;
      skipspace();
      val -= evalint();
      }
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
