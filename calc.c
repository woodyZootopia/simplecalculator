#include <stdio.h>
#include <ctype.h>
#include <string.h>

static char *p;
char funcbuf[26][100];

static int skipspace(){
    while(isspace(*p)) p++;
    return 0;
}

static int expect(char c){
    while(*p != c) p++;
    return 0;
}

static int evalint() {
    int val=0;
    while(isdigit(*p) || *p == '*' || *p == '/' || isupper(*p)) {
        if (*p == '*') {
            p++;
            skipspace();
            val*=evalint();
        }
        else if (*p == '/') {
            p++;
            skipspace();
            val/=evalint();
        }
        else if (isupper(*p)) {
            int funcid=*p-'A';
            p++;
            skipspace();
            if(*p == '{') {
                int i;
                p++;
                skipspace();
                for(i=0;*p!='}';p++,i++){
                    funcbuf[funcid][i]=*p;
                }
                funcbuf[funcid][i+1]='\0'; // 同じ関数が複数回定義されたときのために終端文字で埋めておく
                p++;
                skipspace();
            }
            else if(*p == '(') {
                char* tmp = p;
                p=funcbuf[funcid];
                val=evalint();
                p=tmp+1;
                skipspace();
                p++;
                skipspace();
            }
        }
        else {
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
    p++;
    return 0;
}

int main(int argc, char **argv) {
    for(int i=0;i<26;i++){
        for(int j=0;j<100;j++){
            funcbuf[i][j]='\0';
        }
    }
    p=argv[1];
    if(argc!=2){
        printf("input not one\n");
        return 0;
    }
    while(*p) printf("%d\n",eval());
    return 0;
}
