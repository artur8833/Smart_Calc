#include <stdio.h>

void funch(char *str,int *i);
int main(){
    char str[]="cos(3)";
    int i=0;
    printf("i1==%d\n",i);
    funch(&str[i],&i);
    printf("str[i]==%c\n",str[i]);
    printf("i2==%d\n",i);

    // for(int i=0;i<4;i++){
    //     printf("str[i]==%c\n",str[i]);
    //     funch(&str[i],&i);
    //     printf("str[i]==%d\n\n",i);
    // }
    return 0;
}

void funch(char *str,int *i){
    int flag=0;
    if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's'){
        *i=*i+2;
    }
    // str[*p++];
    // if(str[*p]){
    //     flag=1;
    // }
}