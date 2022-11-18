#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100
char stack[100];
int top = -1;
char temp[100];
void reverse(char str[])
{
    int len, i=0, j=0;
    len=strlen(str);
    j=len-1;
    while(j>=0)
    {
        if(str[j]=='(')
            temp[i]=')';
        else if(str[j]==')')
            temp[i]='(';
        else
            temp[i]=str[j];
        i++, j--;
    }
    temp[i]='\0';
}
void push(char stack[], char item)
{
    top++;
    stack[top] = item;
}

char pop(char stack[])
{
    char item;
    item = stack[top];
    top--;
    return item;
}

int precedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 3;
    else if (ch == '+' || ch == '-')
        return 2;
    else
        return 0;
}

int operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return 1;
    else
        return 0;
}
void infixtopostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        if (infix[i] == '(')
        {
            push(stack, infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while ((top != -1) && (stack[top] != '('))
            {
                postfix[j] = pop(stack);
                j++;
            }
            if (top == -1)
            {
                printf("\nIncorrect expression");
                exit(1);
            }
            pop(stack);
            i++;
        }
        else if (!operator(infix[i]))
        {
            postfix[j] = infix[i];
            i++;
            j++;
        }
        else
        {
            if (precedence(infix[i]) > precedence(stack[top]))
            {
                push(stack, infix[i]);
                i++;
            }
            else
            {
                postfix[j] = pop(stack);
                j++;
            }
        }
    }
    while (top != -1)
    {
        postfix[j] = pop(stack);
        j++;
    }
    postfix[j]='\0';
}

int main()
{
    char postfix[100];
    char infix[] = "A+B*C/(E-F)";
    reverse(infix);
    infixtopostfix(temp, postfix);
    strcpy(temp,"");
    reverse(postfix);
    printf("The Corresponding prefix expression is \n");
    puts(temp);
    return 0;
}