#define MaxSize 100
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct 
{
    ElemType *data;
    int length;
}Seqlist;


Seqlist* initList(){
    Seqlist *L = (Seqlist*)malloc(sizeof(Seqlist));
    L->data = (ElemType*)malloc(sizeof(ElemType) * MaxSize);   
    L->length = 0;
    return L;
}

int appendElem(Seqlist* L,ElemType e){
    if(L->length > MaxSize){
        printf("顺序表已满");
        return 0;
    }
    L->data[L->length]= e;
    L->length++;
    return 1;
}

void listElem(Seqlist* L){
    printf("\n");
    for(int i=0;i<L->length;i++){
        printf("%-5d",L->data[i]);
    }
    printf("\n");
}

int insertElem(Seqlist* L,int pos,ElemType e){
    if(L->length > MaxSize-1){
        printf("顺序表已满");
        return 0;
    }
    if(pos>L->length || pos < 0){
        printf("位置不正确");
        return 0;
    }
    for(int i = L->length-1;i >= pos;i--){
        L->data[i+1] = L->data[i];
    }
    L->data[pos] = e;
    L->length++;
    return 1;
}

int deleteElem(Seqlist* L,int pos/*,ElemType* e*/){
    if(L->length < 0){
        printf("空表");
        return 0;
    }
    if(pos>L->length || pos < 0){
        printf("位置不正确");
        return 0;
    }
   /* e = &L->data[pos];*/
    for(int i = pos;i<L->length;i++){
        L->data[i] = L->data[i+1];
    }
    L->length--;
    return 1;
}

int findElem(Seqlist* L,ElemType AimedElem){
    for(int i=0;i<L->length;i++){
        if(L->data[i] == AimedElem)
            return i+1;
    }
    return 0;
}

int main(){
    Seqlist* a = initList();
    appendElem(a,15);
    appendElem(a,45);
    appendElem(a,4568);
    insertElem(a,1,65);
    listElem(a);
    return 0;
}
