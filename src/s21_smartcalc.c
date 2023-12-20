#include "s21_smartcalc.h"

void print(stack *head){
    for (stack *p=head;p!=NULL;p=p->next_operators){
        printf("%f ", p->num);
        printf("%d ", p->priority);
        printf("%d ", p->type);
        printf("%c",p->symbol);
        printf("| ");
    }
    printf("\n");
}

void append(stack ** phead, double num, int priority,int type, char symbol){
    stack *p=malloc(sizeof(stack));  
    p->priority=priority;
    p->num=num;
    p->type=type;
    p->symbol=symbol;
    p->next_operators=*phead;
    *phead= p;
}

double pop(stack **phead){
    stack *p=*phead;
    *phead = p->next_operators;
    free(p);
    return 0;
}

double s21_calculator(char *str,double x){
    stack *head_stack=NULL;
    stack *rpn=NULL;
    double result=0;
    if(strlen(str)!=0){
        parcer(str,&head_stack,x);
        // printf("head_stack_after_parce\n");
        // print(head_stack);
        convert_in_RPN(&head_stack,&rpn);
        result=calculation(&rpn);
        // print(rpn);
    }
    return result;
}

void parcer(char *str,stack **head_stack,double x){
    char numbers_buf[255]="";
    char operators_mas[] = "+-*/^mcstal()";
    int len=strlen(str);
    int j=0;
    double num=0;
    for (int i=0; i<len; i++){
        //printf("str[%d]==%c\n",i,str[i]);
        while (char_is_number(str[i])){
            numbers_buf[j]=str[i];
            j++;
            i++;
        }
        if(!char_is_number(str[i]) && j>0){
            to_number(numbers_buf,&num);
            append(head_stack,num,0,NUMBERS,' ');
            memset(&numbers_buf, 0, sizeof(numbers_buf));
            j=0;
        }
        if (str[i] == 'x' || str[i] == 'X') {
            append(head_stack,x,0,NUMBERS,' ');
        }
        
        if(strchr(operators_mas, str[i]) != NULL){
            parce_operators(str,&i,head_stack);
        }

    }
}

void parce_operators (char *str,int *i, stack **head){

    if(str[*i]=='+'){
        append(head,0,1,PLUS,'+');
    }
    if (str[*i]=='-'){
        append(head,0,1,MINUS,'-');
    }
    if (str[*i]=='*'){
        append(head,0,2,MULT,'*');
    }
    if (str[*i]=='/'){
        append(head,0,2,DIV,'/');
    }
    if (str[*i]=='^'){
        append(head,0,3,EXP,'^');
    }
    if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd'){
        *i=*i+2;
        append(head,0,3,MOD,'m');
    }
    if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's'){
         *i=*i+2;
        append(head,0,4,COS,'c');
    }
    if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n'){
        *i=*i+2;
        append(head,0,4,SIN,'s');
    }
    if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n'){
         *i=*i+2;
        append(head,0,4,TAN,'t');
    }
    if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' && str[*i + 3] == 's'){
        *i=*i+3;
        append(head,0,4,ACOS,'C');
    }
    if (str[*i] == 'a' && str[*i+1] == 's' && str[*i+2] == 'i' && str[*i+3] == 'n'){
        *i=*i+3;
        append(head,0,4,ASIN,'S');
    }
    if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' && str[*i + 3] == 'n'){
        *i=*i+3;
        append(head,0,4,ATAN,'T');
    }
    if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' && str[*i + 3] == 't'){
        *i=*i+3;
        append(head,0,4,SQRT,'Q');
    }
    if (str[*i] == 'l' && str[*i + 1] == 'n'){
        *i=*i+1;
        append(head,0,4,LN,'L');
    }
    if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g'){
        *i=*i+2;
        append(head,0,4,LOG,'g');
    }
    if (str[*i] == '('){
        append(head,0,1,BRAC_OPEN,'(');
    }
    if (str[*i] == ')'){
        append(head,0,1,BRAC_CLOSE,')');
    }
}

void convert_in_RPN(stack **head, stack **result)
{
    stack *reverses_stack=reverse_stack(*head);
    stack *support=NULL;

    // printf("reverses_stack\n");
    // print(reverses_stack);
    while(reverses_stack!=NULL){ // иду по перевернутому стеку
        //printf("reverses_stack->symbol==%c\n",reverses_stack->symbol);
        if(reverses_stack->type==0) // если приходит число то добавляю его в основной стек и убираю из перевернутого
        {
            append(result,reverses_stack->num,reverses_stack->priority,reverses_stack->type,reverses_stack->symbol);
            pop(&reverses_stack);
        }
        else if((*result==NULL)&&(reverses_stack->symbol=='-')){ //если результат пуст то добавляю 0 чтобы обработать -9 в самом начале
            append(result,0,0,NUMBERS,' ');
        }
        else
        {
            if(support==NULL){ //если вспомогательный стек пуст то добавляю в него первый символ 
                append(&support,reverses_stack->num,reverses_stack->priority,reverses_stack->type,reverses_stack->symbol);
                pop(&reverses_stack);
            }
            else  if(reverses_stack->type!=8){ // если не встретилась закрывающаяся скобка
                if((reverses_stack->symbol=='(')&&(reverses_stack->next_operators->symbol=='-')){ // если в скобки перый символ -, то добавляю 0
                    append(result,0,0,NUMBERS,' ');
                }

                append(&support,reverses_stack->num,reverses_stack->priority,reverses_stack->type,reverses_stack->symbol); // добавляю в вспомагательный стек текущий символ
                pop(&reverses_stack);

                if((support->type!=7)){
                    removeStack(&support->next_operators,result,support->priority);
                }

                // printf("\n");
                // printf("support\n");
                // print(support);

                // printf("result\n");
                // print(*result);
                
            }
            else  if(reverses_stack->type==8){ // если скобка закрывающаяся 
               
                pop(&reverses_stack);
                //print(support);
                while ((support!=NULL))
                {
                    if(support->type==7)
                    {
                        pop(&support);
                        break;
                    }

                    append(result,support->num,support->priority,support->type,support->symbol);
                    pop(&support);
                }
            }
        }
    }

    while(support!=NULL)
    {
        append(result,support->num,support->priority,support->type,support->symbol);
        pop(&support);
    }
    // print(*result);

}

void removeStack(stack** support, stack** head , int current_priority) {
    // Если список пустой или имеет только один элемент, ничего не делаем
    stack* current = *support;
    stack* previous = NULL;
    // проходим по вспомогательному массиву и если приоритет следующиго символа больше текущего, то вытаскиваем его
    while ((current != NULL)) { 

        if(current->type==7){
            break;
        }
        if ((current->priority >= current_priority)) {
            //printf("current->symbol==%c\n",current->symbol);
            if(current->type==7){
                break;
            }
            // Если удаляемый узел находится в начале списка
            if (previous == NULL) {
                stack* next = current->next_operators;
                append(head,current->num,current->priority,current->type,current->symbol);
                pop(&current);
                *support = next;
                current = next;
            }
            // Если удаляемый узел находится в середине или конце списка
            else {
                stack* next = current->next_operators;
                append(head,current->num,current->priority,current->type,current->symbol);
                pop(&current);
                previous->next_operators = next;
                current = next;
            }
        } else {
            previous = current;
            current = current->next_operators;
        }
    }
}


stack *reverse_stack(stack *original){
    stack *reverse=NULL;
    while(original!=NULL){ //переворачиваю стек
        append(&reverse,original->num,original->priority,original->type,original->symbol);
        pop(&original);
    }
    return reverse;
}

double calculation(stack **rpn){
    stack *rpn_reverse_stack = reverse_stack(*rpn);
    stack *support=NULL;
    double n1,n2,res=0;

    // printf("rpn_reverse_stack\n");
    // print(rpn_reverse_stack);

    while(rpn_reverse_stack!=NULL){
        //print(support);
        //printf("rpn_reverse_stack->symbol==%c\n\n",rpn_reverse_stack->symbol);
        //printf("rpn_reverse_stack->priority==%d\n\n",rpn_reverse_stack->priority);

        // printf("rpn_reverse_stack\n");
        // print(rpn_reverse_stack);

        if(rpn_reverse_stack->type==0){
            append(&support,rpn_reverse_stack->num,rpn_reverse_stack->priority,rpn_reverse_stack->type,rpn_reverse_stack->symbol);
            pop(&rpn_reverse_stack);
        }
        else{
            if((rpn_reverse_stack->priority==1)||(rpn_reverse_stack->priority==2)||(rpn_reverse_stack->priority==3)){
                n2=support->num;
                pop(&support);
                n1=support->num;
                pop(&support);
                res=calculate(n1,n2,rpn_reverse_stack->symbol);
                append(&support,res,0,NUMBERS,' ');
                pop(&rpn_reverse_stack);
            }
            else if(rpn_reverse_stack->priority==4){
                n1=support->num;
                pop(&support);
                res=calculate(n1,0,rpn_reverse_stack->symbol);
                append(&support,res,0,NUMBERS,' ');
                pop(&rpn_reverse_stack);
            }
        }

        //printf("res===%f\n",res);
    }
    if(support!=NULL){
        res=support->num;
        pop(&support);
    }
    // printf("res===%f\n",res);

    return res;
}

double calculate(double a1, double a2, char operator){
    double result=0;
    if(operator=='+'){
        result=a1+a2;
    }
    else if(operator=='-'){
        result=a1-a2;
    }
    else if(operator=='*'){
        result=a1*a2;
    }
    else if(operator=='/'){
        result=a1/a2;
    }
    else if(operator=='^'){
        result=pow(a1,a2);
    }
    else if(operator=='m'){
        result=fmod(a1,a2);
    }
    else if(operator=='c'){
        result=cos(a1);
    }
    else if(operator=='s'){
        result=sin(a1);
    }
    else if(operator=='t'){
        result=tan(a1);
    }
    else if(operator=='C'){
        result=acos(a1);
    }
    else if(operator=='S'){
        result=asin(a1);
    }
    else if(operator=='T'){
        result=atan(a1);
    }
    else if(operator=='Q'){
        result=sqrt(a1);
    }
    else if(operator=='L'){
        result=log(a1);
    }
    else if(operator=='g'){
        result=log10(a1);
    }
    return result;
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

// int main(){ 
//     //char str[]="2+4+3-cos(7*4)";

//     char str[]="5";
//     //char str[]="asin(0.6)+1";
//     double num=s21_calculator(str,0);
//     printf("num==%f\n", num);


//     // stack* support = NULL;
//     // stack* head = NULL;
//     // append(&head,2,0,0,' ');
//     // append(&head,3,0,0,' ');
//     // append(&head,0,2,3,'*');
//     // append(&head,3,0,0,' ');
//     // append(&support,0,1,1,'+');
//     // append(&support,0,4,9,'c');
//     // append(&support,0,1,7,'(');
//     // append(&support,0,1,1,'+');

//     // printf("\n");
//     // print(support);
//     // print(head);

//     // append(&support,0,2,3,'*');
    
//     // printf("\n");
//     // print(support);
//     // print(head);
    
//     // removeStack(&support->next_operators,&head,support->priority);
    
//     // printf("\n");
//     // print(support);
//     // print(head);

//     return 0;
// }