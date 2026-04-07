#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct treeNode{
    ElemType data;
    struct treeNode *left ;
    struct treeNode *right ;
}treeNode;

typedef treeNode* biTree;

char str[]="sc##s#I";
int idx = 0;
void createTree(biTree* T){
    ElemType e=str[idx++];
    if(e == '\0'){
        idx--;
        *T = NULL;
    }
    else if(e == '#'){
        *T = NULL;
    }
    else{
        *T = (biTree)malloc(sizeof(treeNode));
        (*T)->data = e;
        createTree(&((*T)->left));
        createTree(&((*T)->right));
    }
}

void preorder(biTree T){
    if(T == NULL){
        printf("-");
        return;
    }
    printf("%c",T->data);
    preorder(T->left);
    preorder(T->right);
}

void inorder(biTree T){
    if(T == NULL){
        printf("-");
        return;
    }
    inorder(T->left);
    printf("%c",T->data);
    inorder(T->right);
}

void postorder(biTree T){
    if(T == NULL){
        printf("-");
        return;
    }
    postorder(T->left);
    postorder(T->right);
    printf("%c",T->data);

}

int main(){
    biTree T;
    createTree(&T);
    preorder(T);
    printf("\n");
    inorder(T);
    printf("\n");
    postorder(T);
    return 0;
}