#include<stdio.h>

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
} Graph;

typedef struct {
    int begin;
    int end;
    int weight;
} Edge;

void createGraph(Graph* G){
    G->vertexNum = 9;
    G->edgeNum = 15;
    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

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
    
    //A-B,A-F
    G->edge[0][1] = 10;
    G->edge[0][5] = 11;

    //B-C,B-G,B-I
    G->edge[1][2] = 18; 
    G->edge[1][6] = 16;
    G->edge[1][8] = 12;

    //C-D,C-I
    G->edge[2][3] = 22;
    G->edge[2][8] = 8;

    //D-E,D-G,D-H,D-I
    G->edge[3][4] = 20;
    G->edge[3][6] = 24;
    G->edge[3][7] = 16;
    G->edge[3][8] = 21;

    //E-F,E-H
    G->edge[4][5] = 26;
    G->edge[4][7] = 7;

    //F-G
    G->edge[5][6] = 17;

    //G-H
    G->edge[6][7] = 19;

    for(int i=0; i < G->vertexNum; i++){
        for(int j=i+1; j < G->vertexNum; j++){
            G->edge[j][i] = G->edge[i][j];
        }
    }
}

//prim算法，依次找顶点
void prim(Graph G){
    int i, j, k;
    int min;
    int weights[MAXSIZE];//每次循环时下标对应点的可选边的最小权重
    int vex_index[MAXSIZE];//每次循环时权重数组中对应边的另一个端点

    weights[0] = 0;
    vex_index[0] = 0;
    for(i=1; i < G.vertexNum; i++){
        weights[i] = G.edge[0][i];
        vex_index[i] = 0;
    }

    for(i=1; i < G.vertexNum; i++){
        min = INF;
        j = 0;
        k = 0;//找到权值最小的边
        for(; j < G.vertexNum; j++){
            if(weights[j] != 0 && weights[j] < min){
                min = weights[j];
                k = j;
            }
        }

        printf("(%c, %c)\n", G.vertex[vex_index[k]], G.vertex[k]);
        weights[k] = 0;

        //更新权值数组
        for(j=0; j < G.vertexNum; j++){
            if(weights[j] != 0 && G.edge[k][j] < weights[j]){
                weights[j] = G.edge[k][j];
                vex_index[j] = k;
            }
        }
    }
}

void initEdge(Edge* edges, Graph G){
    int k = 0;
    for(int i=0; i < G.vertexNum; i++){
        for(int j=i+1; j < G.vertexNum; j++){
            if(G.edge[i][j] != INF){
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.edge[i][j];
                k++;
            }
        }
    }
}

//冒泡排序
void sortEdge(Edge* edges, int edgeNum){
    for(int i=0; i < edgeNum-1; i++){
        for(int j=0; j < edgeNum-1-i; j++){
            if(edges[j].weight > edges[j+1].weight){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

int find(int* parent, int f){
    while(parent[f] != f){
        f = parent[f];
    }
    return f;
}

void kruskal(Graph G){
    Edge edges[MAXEDGE];
    initEdge(edges, G);
    sortEdge(edges, G.edgeNum);

    int parent[MAXSIZE];
    for(int i=0; i < G.vertexNum; i++){
        parent[i] = i;
    }

    int n,m;
    for(int i=0; i < G.edgeNum; i++){
        n = find(parent, edges[i].begin);
        m = find(parent, edges[i].end);
        if(n != m){
            parent[n] = m;
            printf("(%c, %c)\n", G.vertex[edges[i].begin], G.vertex[edges[i].end]);
        }
    }
}

int main(){
    Graph G;
    createGraph(&G);

    prim(G);
    printf("\n");
    kruskal(G);
}