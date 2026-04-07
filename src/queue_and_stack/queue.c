#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100
typedef int ElemType;

typedef struct 
{
    ElemType *data;
    int front;
    int rear;
}Queue;

void initQueue(Queue *q, int size){
    q->data = (ElemType *)malloc(MAX_SIZE * sizeof(ElemType));
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue *q, ElemType e){
    if((q->rear + 1) % MAX_SIZE == q->front){
        printf("Queue is full!\n");
        return;
    }
    
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAX_SIZE;
}

void dequeue(Queue *q, ElemType *e){
    if(q->front == q->rear){
        printf("Queue is empty!\n");
        return;
    }

    *e = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
}
