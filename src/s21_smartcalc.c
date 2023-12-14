#include "s21_smartcalc.h"

int char_is_number(char c);
void append(stack ** phead, double num, int priority,int type);
double pop( stack **phead);
void reverse_stack(stack *head,  stack **result);
void parce_operators (char *str,int *i, stack **support);

void print(stack *head){
    for (stack *p=head;p!=NULL;p=p->next_operators){
        printf("%f ", p->num);
        printf("%d ", p->priority);
    }
    printf("\n");
}

void append(stack ** phead, double num, int priority,int type){
    stack *p=malloc(sizeof(stack));  
    p->priority=priority;
    p->num=num;
    p->type;
    p->next_operators=*phead;
    *phead= p;
}

double pop(stack **phead){
    stack *p=*phead;
    double res = p->num;
    *phead = p->next_operators;
    free(p);
    return res;
}

void reverse_stack(stack *head,  stack **result){
    while(head!=NULL){
        append(result,head->num,head->priority,head->type);
        pop(&head);
    }
}

int s21_calculator(char *str,double x){
    if(strlen(str)!=0){
        parcer(str,x);
    }
}

void parcer(char *str,double x){
    stack *head_stack=NULL;
    stack *support=NULL;

    char numbers_buf[255]="";
    char operators_mas[] = "+-*/^mcstal()";
    int len=strlen(str);
    int j=0;
    double num=0;
    for (int i=0; i<len; i++){
        //printf("char_ins===%c\n", str[i]);

        while (char_is_number(str[i])){
            numbers_buf[j]=str[i];
            j++;
            i++;
        }
        if(!char_is_number(str[i]) && j>0){
            to_number(numbers_buf,&num);
            append(&head_stack,num,0,NUMBERS);
            memset(&numbers_buf, 0, sizeof(numbers_buf));
            j=0;
        }
        
        if(strchr(operators_mas, str[i]) != NULL){
            parce_operators(&str[i],&i,&support);
            
        }
        
        
    }
    print(head_stack);
}

void parce_operators (char *str,int *i, stack **support){
    if (str[*i]=='+'){
        append(support,0,1,PLUS);
    }
    if (str[*i]=='-'){
        append(support,0,1,MINUS);
    }
    if (str[*i]=='*'){
        append(support,0,2,MULT);
    }
    if (str[*i]=='/'){
        append(support,0,2,DIV);
    }
    if (str[*i]=='^'){
        append(support,0,3,EXP);
    }
    if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd'){
        append(support,0,3,MOD);
    }
    if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's'){
        append(support,0,4,COS);
    }
    if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n'){
        append(support,0,4,SIN);
    }
    if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n'){
        append(support,0,4,TAN);
    }
    if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' && str[*i + 3] == 's'){
        append(support,0,4,ACOS);
    }
    if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' && str[*i + 3] == 'n'){
        append(support,0,4,ASIN);
    }
    if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' && str[*i + 3] == 'n'){
        append(support,0,4,ATAN);
    }
    if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' && str[*i + 3] == 't'){
        append(support,0,4,SQRT);
    }
    if (str[*i] == 'l' && str[*i + 1] == 'n'){
        append(support,0,4,LN);
    }
    if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g'){
        append(support,0,4,LOG);
    }
    if (str[*i] == '('){
        append(support,0,1,BRAC_OPEN);
    }
    if (str[*i] == ')'){
        append(support,0,1,BRAC_CLOSE);
    }
}


int char_is_number(char c){
    int res=0;
    if(((c >= '0' && c <= '9') || (c == '.') || (c == ',') || (c == 'e')))
    {
        res=1;
    }
    return res;
}

void to_number(char *str, double *num) {
  *num = 0;
  *num = atof(str);
}



int main(){ 
    char str[]="1+2+3-cos(1*6+54-89)";
    s21_calculator(str,0);

    return 0;
}