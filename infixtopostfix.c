#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char data;
    struct node *next;
}NODE;

NODE *top=NULL;

NODE *createnode(char item)
{
    NODE *p;
    p=(NODE*)malloc(sizeof(NODE));
    p->data=item;
    p->next=NULL;
}

void push(char symb)
{
    NODE *p;
    p=createnode(symb);
    if(top==NULL)
        top=p;
    else
    {
        p->next=top;
        top=p;
    } 
    return;   
}

int pop()
{
    NODE *p;
    if(top!=NULL)
    {
        p=top;
        top=top->next;
    }
    return p->data;
}

int prcd(char symb)
{
    if(symb=='^')
    {
        return 3;
    }
    else if (symb=='*' || symb=='/')
    {
        return 2;
    }
    else if(symb=='+' || symb=='-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void post_convert(char str[])
{
    int i,j=0;
    char symb,topsymb,pstr[50];
    for(i=0;str[i]!='\0';i++)
    {
        symb=str[i];
        if((symb>='a' && symb<='z')||(symb>='A' && symb<='Z'))
        {
            pstr[j]=symb;
            j++;
        }
        else if(symb=='(')
        {
            push(symb);
        }
        else if(symb==')')
        {
            while(top!=NULL && top->data!='(')
            {
                topsymb=pop();
                pstr[j]=topsymb;
                j++;
            }
            if(top!=NULL)
            {
                pop();
            }
        }
        else
        {
            while(top!=NULL && prcd(top->data)>prcd(symb))
            {
                topsymb=pop();
                pstr[j]=topsymb;
                j++;
            }
            push(symb);
        }       
    }
    while(top!=NULL)
    {
        topsymb=pop();
        pstr[j]=topsymb;
        j++;
    }
    puts(pstr);
}

void main()
{
    char str[50];
    printf("Enter your infix expression:");
    gets(str);
    post_convert(str);
}