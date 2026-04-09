#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef int VertexType;
typedef int EdgeType;

typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType edge[MAXSIZE][MAXSIZE];
    int vertexNum;
    int edgeNum;
} Mat_Graph;

typedef struct EdgeNode {
    int edge_vex;
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

void createMatGraph(Mat_Graph* G) {
    G->vertexNum = 14;
    G->edgeNum = 20;

    for(int i=0; i<G->vertexNum; i++) {
        G->vertex[i] = i;
    }

    for(int i=0; i<G->vertexNum; i++) {
        for(int j=0; j<G->vertexNum; j++) {
            G->edge[i][j] = 0;
        }
    }
    
    G->edge[0][4] = 1;
    G->edge[0][5] = 1;
    G->edge[0][11] = 1;
    G->edge[1][2] = 1;
    G->edge[1][4] = 1;

    G->edge[1][8] = 1;
    G->edge[2][5] = 1;
    G->edge[2][6] = 1;
    G->edge[2][9] = 1;
    G->edge[3][2] = 1;

    G->edge[3][13] = 1;
    G->edge[4][7] = 1;
    G->edge[5][8] = 1;
    G->edge[5][12] = 1;
    G->edge[6][5] = 1;

    G->edge[8][9] = 1;
    G->edge[9][10] = 1;
    G->edge[9][11] = 1;
    G->edge[10][13] = 1;    
    G->edge[12][9] = 1;
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
            if(G->edge[i][j] == 1) {
                node = malloc(sizeof(EdgeNode));
                node->edge_vex = j;
                //头插法
                node->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = node;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
   
}

void topologicalSort(Adj_list_Graph ALG) {
    int top=0;
    int data[MAXSIZE];
    int curr;
    int k;


    for(int i=0; i < ALG->vertexNum; i++) {
        if(ALG->adj_list[i].in == 0) {
            data[top++] = i;
        }
    }

    while(top > 0) {
        curr = data[--top];
        printf("%d ", ALG->adj_list[curr].vertex);
        EdgeNode* node = ALG->adj_list[curr].head;
        while(node != NULL) {
            k = node->edge_vex;
            ALG->adj_list[k].in--;
            if(ALG->adj_list[k].in == 0) {
                data[top++] = k;
            }
            node = node->next;
        }
    }
}

int main() {
    Mat_Graph G;
    Adj_list_Graph ALG;

    createMatGraph(&G);
    createAdjGraph(&G, &ALG);
    topologicalSort(ALG);

    return 0;
}