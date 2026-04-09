#include<stdio.h>
#include<stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define INF 0x7fffffff

typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType edge[MAXSIZE][MAXSIZE];
    int vertexNum;
    int edgeNum;
} Mat_Graph;

typedef struct {
    int begin;
    int end;
    int weight;
} Edge;

typedef struct EdgeNode {
    int edge_vex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct {
    int in;
    VertexType vertex;
    EdgeNode* head;
} VertexNode;

typedef struct {
    VertexNode adj_list[MAXSIZE];
    int vertexNum;
    int edgeNum;
} Adj_Graph;

typedef Adj_Graph* Adj_list_Graph;


void createMat_Graph(Mat_Graph* G){
    G->vertexNum = 10;
    G->edgeNum = 13;

    for(int i=0; i < G->vertexNum; i++){
        G->vertex[i] = i;
    }
    //初始化邻接矩阵
    for (int i=0; i < G->vertexNum; i++)
    {
        for (int j=0; j < G->vertexNum; j++)
        {
            if(i == j){
                G->edge[i][j] = 0;
            }
            else{ 
                G->edge[i][j] = INF;
            }
        }
    }

    G->edge[0][1] = 3;
    G->edge[0][2] = 4;
    G->edge[1][3] = 5;
    G->edge[1][4] = 6;      
    G->edge[2][3] = 8;

    G->edge[2][5] = 7;
    G->edge[3][4] = 3;
    G->edge[4][6] = 9;
    G->edge[4][7] = 4;
    G->edge[5][7] = 6;

    G->edge[6][9] = 2;
    G->edge[7][8] = 5;
    G->edge[8][9] = 3;
 
}

void createAdjGraph(Mat_Graph* G, Adj_list_Graph* ALG) {
    (*ALG) = (Adj_list_Graph)malloc(sizeof(Adj_Graph));
    (*ALG)->vertexNum = G->vertexNum;
    (*ALG)->edgeNum = G->edgeNum;

    for(int i=0; i<(*ALG)->vertexNum; i++) {
        (*ALG)->adj_list[i].vertex = G->vertex[i];
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].head = NULL;
    }

    for(int i=0; i < G->vertexNum; i++) {
        for(int j=0; j < G->vertexNum; j++) {
            EdgeNode* node;
            if(G->edge[i][j] != INF && G->edge[i][j] != 0) {
                node = malloc(sizeof(EdgeNode));
                node->edge_vex = j;
                node->weight = G->edge[i][j];
                //头插法
                node->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = node;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
   
}

void criticalPth(Adj_list_Graph ALG){
    EdgeNode* node;
    int top1 = 0, top2 = 0;
    int stack1[MAXSIZE], stack2[MAXSIZE];
    int ve[MAXSIZE], vl[MAXSIZE];
    int curr;
    int k;

    for(int i=0; i < ALG->vertexNum; i++){
        if(ALG->adj_list[i].in == 0){
            stack1[top1++] = i;
        }
    }

    //初始化最早发生时间数组
    for(int i=0; i < ALG->vertexNum; i++){
        ve[i] = 0;
    }

    while(top1 != 0){
        curr = stack1[--top1];
        stack2[top2++] = curr;

        node = ALG->adj_list[curr].head;
        while(node != NULL){
            k = node->edge_vex;
            ALG->adj_list[k].in--;
            if(ALG->adj_list[k].in == 0){
                stack1[top1++] = k;
            }
            
            if(ve[curr] + node->weight > ve[k]){
                ve[k] = ve[curr] + node->weight;
            }

            node = node->next;
        }
    }

    //初始化最晚发生时间数组
    for(int i=0; i < ALG->vertexNum; i++){
        vl[i] = ve[ALG->vertexNum - 1];
    }

    while(top2 != 0){
        //从后往前遍历拓扑序列，更新最晚发生时间数组
        curr = stack2[--top2];

        node = ALG->adj_list[curr].head;
        while(node != NULL){
            k = node->edge_vex;
            
            if(vl[k] - node->weight < vl[curr]){
                vl[curr] = vl[k] - node->weight;
            }

            node = node->next;
        }
    }

    //关键路径上的活动满足ve[i] == vl[i]
    printf("Critical path is:");
    for(int i=0; i < ALG->vertexNum; i++){
        if(ve[i] == vl[i]){
            printf("V%d ->", ALG->adj_list[i].vertex);
        }
    }
    printf("End\n");

}

int main() {
    Mat_Graph G;
    Adj_list_Graph ALG;

    createMat_Graph(&G);
    createAdjGraph(&G, &ALG);
    criticalPth(ALG);

    return 0;
}