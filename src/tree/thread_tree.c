#include<stdlib.h>
#include<stdio.h>

typedef char ElemType;

typedef struct threadNode{
    ElemType data;
    struct threadNode *left ;
    struct threadNode *right ;
    int ltag;   //0表示孩子，1表示前驱
    int rtag;  //0表示孩子，1表示后继
}threadNode;

typedef threadNode* threadTree;

//函数声明
void createTree(threadTree* T);
void inOrderThreading(threadTree* head, threadTree T);
void myThreading(threadTree T);
void inOrder(threadTree T);


threadTree prev;

char str[]="sc##s#I";
int idx = 0;
void createTree(threadTree* T){

    ElemType e=str[idx++];

    if(e == '\0'){
        idx--;
        *T = NULL;
    }else if(e == '#'){
        *T = NULL;
    }else{

        *T = (threadTree)malloc(sizeof(threadNode));

        (*T)->data = e;

        createTree(&((*T)->left));
        if((*T)->left == NULL){
            (*T)->ltag = 1;
        }else{
            (*T)->ltag = 0;
        }

        createTree(&((*T)->right));
        if((*T)->right == NULL){
            (*T)->rtag = 1;
        }else{
            (*T)->rtag = 0;
        }
    }
}

void inOrderThreading(threadTree* head, threadTree T){
    
    *head = (threadTree)malloc(sizeof(threadNode));
    (*head) -> ltag = 0;
    (*head) -> rtag = 1;
    (*head) -> right = (*head);

    if(T == NULL){
        (*head) -> left = (*head);
    }else{
        (*head) -> left = T;
        (*head) -> ltag = 1;

        prev = (*head);

        myThreading(T);

        prev -> right = (*head);
        prev -> rtag = 1;

        (*head) -> right = prev;
    }
}

void myThreading(threadTree T){

    //防止空指针访问
    if(T == NULL){
        return;
    }
    //递归线索化左子树
    myThreading(T -> left);
    //线索化当前节点
    if((T -> left == NULL)){
        (T) -> left = prev;
        (T) -> ltag  = 1;
    }
    //线索化前驱节点
    if((prev -> right) == NULL){
        prev -> right = T;
        prev -> rtag = 1;
    }

    prev = T;
    //递归线索化右子树
    myThreading(T -> right);
}


/*
遍历时，如果当前节点的ltag为0，说明它有左子树，继续向左遍历；如果ltag为1，说明没有左子树，可以直接访问当前节点的数据。
访问完当前节点后，如果rtag为1，说明没有右子树，可以直接访问当前节点的右指针所指向的后继节点并输出数据；
如果rtag为0，说明有右子树，从该右子树继续遍历。
直到再次访问头结点为止，遍历结束。
*/
void inOrder(threadTree T){

    threadTree curr;
    curr = T->left;

    while(curr != T){
        //找到当前节点的最左子树
        while(curr -> ltag == 0){
            curr = curr -> left;
        }
        printf("%c ", curr -> data);

        //向后遍历直到遇到一个右子树
        while(curr -> rtag == 1 && curr -> right != T){
            curr = curr -> right;
            printf("%c ", curr -> data);
        }
        curr = curr -> right;
    }
}

int main(){

    threadTree T, head;
    // 创建树
    createTree(&T);
    
    inOrderThreading(&head, T);

    inOrder(head);//传入头节点遍历

    return 0;
}