#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct TreeNode{
    ElemType data;
    struct TreeNode *left ;
    struct TreeNode *right ;
}TreeNode;

typedef TreeNode* BiTree;

// void createTree(BiTree* T){
//     ElemType e=data[index++];
//     if(e == -1){
//         *T = NULL;
//     }
//     else{
//         *T = (BiTree)malloc(sizeof(TreeNode));
//         (*T)->data = e;
//         createTree(&((*T)->left));
//         createTree(&((*T)->right));
//     }
// }

void preorder(BiTree T){
    if(T == NULL){
        printf("-1 ");
        return;
    }
    printf("%d ",T->data);
    preorder(T->left);
    preorder(T->right);
}

/*
    * 在二叉搜索树中查找值为value的节点
    * BiTree T: 二叉搜索树的根节点
    * ElemType value: 要查找的值
    * BiTree parent: 查找到的节点的父节点
    * BiTree* pos: 查找到的节点的地址(传入指针的指针便于修改BiTree自身)
    * 返回值: 1表示找到，0表示未找到
*/
int searchBST(BiTree T, ElemType value, BiTree parent, BiTree* pos, BiTree* front){
    if(T == NULL){
        *pos = parent; // pos指向父节点，便于插入新节点
        *front = parent;
        return 0;
    }
    if(T->data == value){
        *pos = T;
        return 1;
    }
    else if(T->data > value){
        *front = T; // front指向当前节点，便于删除节点时连接父节点和子节点 
        return searchBST(T->left, value, T, pos, front);
    }
    else{
        *front = T; // front指向当前节点，便于删除节点时连接父节点和子节点 
        return searchBST(T->right, value, T, pos, front);
    }
}

int insertBST(BiTree* T, ElemType value){
    BiTree parent=NULL, pos=NULL;
    BiTree curr;

    int isexist = searchBST(*T, value, NULL, &pos, &parent);
    if(isexist){ return 0; }// 已存在，不插入
    else{// 不存在，插入新节点
        curr = (BiTree)malloc(sizeof(TreeNode));
        curr->data = value;
        curr->left = NULL;
        curr->right = NULL;
        if(pos == NULL) {// pos为空说明是空树，插入为根节点
            *T = curr;
        } else if(pos->data > value){
            pos->left = curr;
        } else{
            pos->right = curr;
        }
    }
    return 1;// 插入成功
}

int deleteBST(BiTree* T, ElemType value){
    BiTree parent=NULL, pos=NULL;
    BiTree temp=NULL, record=NULL, front=NULL;
    int isexist = searchBST(*T, value, NULL, &pos, &parent);

    if(!isexist){ return 0; }// 不存在，不删除
    else {
        if(pos->left == NULL && pos->right == NULL) {
            if(parent == NULL) { // 删除根节点
                *T = NULL;
                free(pos);
            } else {
                temp = pos;
                if(parent->left == pos) {parent->left = NULL;} // 将父节点的对应子节点指向NULL
                else {parent->right = NULL;}
                free(temp);
            }
            
        } else if(pos->right != NULL && pos->right != NULL) {// 有两个子节点，找到右子树的最左节点替换pos

            // 找到右子树的最左节点
            front = pos; 
            record = pos->right; 
            while(record->left != NULL) {
                front = record; // front指向record的父节点，便于删除record
                record = record->left; // record指向右子树的最左节点，用于替换pos
            }
            
            //record继承pos的左右子树,并把record从原位置删除
            if(front != pos) { front->left = NULL; } 
            else { pos->right = NULL; } 
            record->left = pos->left; 
            record->right = pos->right; 

            //删除pos节点
            temp = pos;
            if(parent == NULL) { *T = record; } // 如果删除的是根节点，更新根节点指向record
            else if(parent->left == pos) { parent->left = record; } 
            else { parent->right = record; }

            free(temp);
        } else {// 只有一个子节点，直接用子节点替换pos
            temp = pos;
            if(pos->left != NULL) {
                if(parent->left == pos) {parent->left = pos->left;}
                else {parent->right = pos->left;}
            } else {
                if(parent->left == pos) {parent->left = pos->right;}
                else {parent->right = pos->right;}
            }
            free(temp);
        }
    }
    return 1;// 删除成功
}

int main(){
    
    int data[] = {70, 55, 49, 30, 39, 53, 80, 75,98, 95, 100};
    BiTree T=NULL;
    for(int i=0; i<sizeof(data)/sizeof(data[0]); i++){
        insertBST(&T, data[i]);
    }

    printf("--------------------------------------\n");
    preorder(T);

    deleteBST(&T, 55);
    printf("\n--------------------------------------\n");
    preorder(T);

    return 0;
}