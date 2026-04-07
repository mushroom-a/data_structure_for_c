#include<stdio.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct {
    ElemType* data;
    int top;
} Stack;

void initStack(Stack* S){
    S->data = (ElemType *)malloc(MAX_SIZE * sizeof(ElemType));
    S->top = -1;
}

void push(Stack* S, ElemType e){
    if(S->top == MAX_SIZE - 1){
        printf("Stack is full!\n");
        return;
    }
    S->top++;
    S->data[S->top] = e;
}

void pop(Stack* S, ElemType* e){
    if(S->top == -1){
        printf("Stack is empty!\n");
        return;
    }
    *e = S->data[S->top];
    S->top--;
}
