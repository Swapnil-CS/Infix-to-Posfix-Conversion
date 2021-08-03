#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node     //ADT for the stack 
{
    char data;
    struct node *next;
}NODE;

NODE *createnode(char item)     //function for creating each node of stack
{
    NODE *p;
    p=(NODE*)malloc(sizeof(NODE));  //allocating memory for a node
    p->data=item;           
    p->next=NULL;
    return p;
}

void push(NODE **top,char symb)    //push function of stack
{
    NODE *p;
    p=createnode(symb);     
    if(*top==NULL)       // when stack is empty
    {
         *top=p;          //adding new node at top
    }   
    else                    //when stack is non-empty
    {
        p->next=*top;        //linking new node to top
        *top=p;              //setting top at the last inserted node
    } 
    return;   //returning the control
}

int pop(NODE **top)
{
    NODE *p;
    if(*top!=NULL)       //when stack is non-empty
    {
        p=*top;          //pop the top element
        *top=(*top)->next;      //top goes to the next element
    }
    return p->data;     //returning the popped character
}

int prcd(char symb)     //function for checking precedence of the operators
{
    if(symb=='^')       //^ has the highest precedence
    {
        return 3;
    }
    else if (symb=='*' || symb=='/')        //* and / have same precedence but less than ^
    {
        return 2;
    }
    else if(symb=='+' || symb=='-')     //+ and - have least precedence
    {
        return 1;
    }
    else
    {
        return -1;      //returning -1 whenever something other than operators found i.e "("
    }
}

void post_convert(char str[])   //infix to pstfix convert function
{
    int i,j=0;
    char symb,topsymb,pstr[50];
    NODE *top=NULL;         //initialising top as NULL i.e stack is empty
    
    for(i=0;str[i]!='\0';i++)       //scanning the input string until end
    {
        symb=str[i];
        if((symb>='a' && symb<='z')||(symb>='A' && symb<='Z'))  //checking if the symbol scanned is a operand
        {
            pstr[j]=symb;   //adding the symbol to postfix string
            j++;
        }
        else if(symb=='(')      //if symbol scanned is a "("
        {
            push(&top,symb);     //adding it to the stack
        }
        else if(symb==')')  //if symbol is a ")"
        {
            while(top!=NULL && top->data!='(')  //checking until stack is empty and the top element of stack is a "("
            {
                topsymb=pop(&top);      //popping each operators until the loop becomes false
                pstr[j]=topsymb;        //adding symbol to postfix string
                j++;
            }
            if(top!=NULL)       
            {
                pop(&top);      //popping the "(" symbol
            }
        }
        else    //when symbol scanned is a operator
        {
            while(top!=NULL && prcd(top->data)>=prcd(symb))  //checking until stack is empty and comparing if the precedence of the operator at top is greater than the operator scanned or not
            {
                topsymb=pop(&top);  //pop the operator from top of stack
                pstr[j]=topsymb;    //adding the popped operator to postfix string
                j++;
            }
            push(&top,symb);     //adding the scanned operator to stack
        }       
    }
    while(top!=NULL)    
    {
        topsymb=pop(&top);  //popping the remaining characters
        pstr[j]=topsymb;    //adding to postfix string
        j++;
    }

    printf("\nThe resultant Postfix expression is: ");
    puts(pstr);     //printing the resultant postfix expression
}

void main()     
{
    char str[50];
    printf("Enter your Infix Expression:");
    gets(str);
    post_convert(str);
}