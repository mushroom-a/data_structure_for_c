#include<stdlib.h>
#include<stdio.h>
typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node *next;
}Node;

//初始化
Node* initList(){
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}
//头插法
int insertHead(Node* L,ElemType e){
    Node *p = (Node*)malloc(sizeof(Node)); 
    p->data = e;
    p->next = L->next;
    L->next = p;
    L->data++;  
    return 1;
}
//遍历链表
void listNode(Node* L){
    Node* p = L->next;
    while(p != NULL){
        ElemType data = p->data;
        printf("%-5d",data);
        p = p->next;
    }
    printf("\n");
}
//获取指定节点前一节点(pos不包含头节点)
Node* get_pos(Node* L,int pos){
    for(int i=0;i<pos-1;i++){
        L = L->next;
        if(L == NULL)
            return NULL;
    }
    return L;
}
//尾插
int insertTail(Node* L,ElemType e){
    //获取指定位置前一个节点
    Node* p = get_pos(L,L->data+1);
    if(p == NULL)
        return 0;
    //插入新节点
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = e;
    new->next = p->next;
    p->next = new;
    L->data++;
    return 1;
}
//指定位置插入
int insertpos(Node* L,int pos,ElemType e){
    //获取指定位置前一个节点
    Node* p = get_pos(L,pos);
    if(p == NULL)
        return 0;
    //插入新节点
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = e;
    new->next = p->next;
    p->next = new;
    L->data++;
    return 1;
}
//删除指定位置
int deletepos(Node* L,int pos){
    //获取指定位置前一个节点
    Node* p = get_pos(L,pos);
    if(p == NULL)
        return 0;
    //删除节点
    Node* q = p->next;
    p->next = q->next;
    free(q);
    L->data--;
}
//释放链表
void freeList(Node* L){
    Node *p = L->next;
    while(p != NULL){
        Node* q = p->next;
        L->next = q->next;
        free(p);
        p = L->next;
    }
    L->data =  0;
}
//寻找倒数第k个节点（快慢指针）
Node* findnodeFS(Node* L,int k){
    Node *fast = L,*slow = L;

    for(int i=0;i<k;i++){
        fast = fast->next;
    }

    while(fast != NULL){
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}
//反转链表
void reverseList(Node* L){
    Node* first = NULL;
    Node* second = L->next;
    Node* third;

    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third; 
    }
    L->next = first;
}
//删除中间节点
int delMidNode(Node* L){
    Node *fast = L->next,*slow = L;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = temp->next;
    free(temp);
    return 1;
}

int main(){
    Node* test = initList();
    insertHead(test,10);
    insertHead(test,20);
    insertHead(test,30);
    insertTail(test,51);
    insertpos(test,2,55);
    listNode(test);
    return 0;
}   