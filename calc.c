#include <stdio.h>
#include <ctype.h>
#include <string.h>

static int evalint();
static int eval();

static char *p;
int arg[26];
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
    while(isdigit(*p) || *p == '*' || *p == '/' || isalpha(*p) || *p == '.') {
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
                funcbuf[funcid][i+1]='\0'; // 同じ関数が複数回定義されたときのために終端文字を埋めておく
                p++;
                skipspace();
            }
            else if(*p == '(') {
                p++;
                skipspace();
                if (*p != ')'){
                    int argbuf[26],i;
                    for(i=0;*p != ')' && i<26 ;i++){
                        argbuf[i]=arg[i];
                        arg[i]=eval();
                        skipspace();
                        if(*p == ','){p++;skipspace();}
                    }
                    char* tmp=p;
                    p=funcbuf[funcid];
                    val=eval();
                    p=tmp;
                    for(int j=0;j<i;j++){
                        arg[i]=argbuf[i];
                    }
                    p++;
                    skipspace();
                }
                else {
                    char* tmp=p;
                    p=funcbuf[funcid];
                    val=eval();
                    p=tmp;
                    skipspace();
                    p++;
                    skipspace();
                }
            }
        }
        else if (*p >= 'a' && *p <= 'z') {
            val = arg[*p-'a'];
            p++;
            skipspace();
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
    if(*p == '\0'){
        p++;
        return 0;
    }
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
