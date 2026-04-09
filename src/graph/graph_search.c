#include<stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType edge[MAXSIZE][MAXSIZE];
    int vertexNum;
    int edgeNum;
} Mat_Graph;

int visited[MAXSIZE];

void createMat_Graph(Mat_Graph* G){
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
            G->edge[i][j] = 0;
        }
    }
    
    //A-B,A-F
    G->edge[0][1] = 1;
    G->edge[0][5] = 1;

    //B-C,B-G,B-I
    G->edge[1][2] = 1; 
    G->edge[1][6] = 1;
    G->edge[1][8] = 1;

    //C-D,C-I
    G->edge[2][3] = 1;
    G->edge[2][8] = 1;

    //D-E,D-G,D-H,D-I
    G->edge[3][4] = 1;
    G->edge[3][6] = 1;
    G->edge[3][7] = 1;
    G->edge[3][8] = 1;

    //E-F,E-H
    G->edge[4][5] = 1;
    G->edge[4][7] = 1;

    //F-G
    G->edge[5][6] = 1;

    //G-H
    G->edge[6][7] = 1;

    for(int i=0; i < G->vertexNum; i++){
        for(int j=i+1;j < G->vertexNum; j++){
            G->edge[j][i] = G->edge[i][j];
        }
    }
}

//深度优先搜索
void dfs(Mat_Graph G, int i){
    visited[i] = 1;
    printf("%c ", G.vertex[i]);

    for(int j=0; j < G.vertexNum; j++){
        if(G.edge[i][j] == 1 && visited[j] == 0){
            dfs(G, j);
        }
    }
}

//广度优先搜索
void bfs(Mat_Graph G, int i){
    int queue[MAXSIZE];
    int front = 0;  
    int rear = 0;

    visited[i] = 1;
    printf("%c ", G.vertex[i]);
    queue[rear] = i;
    rear++;
    while(front != rear){
        int u = queue[front];//出队
        front++;
        //访问u的所有邻接点
        for(int j=0; j < G.vertexNum; j++){
            if(G.edge[u][j] == 1 && visited[j] == 0){
                visited[j] = 1;
                printf("%c ", G.vertex[j]);
                queue[rear] = j;//入队
                rear++;
            }
        }
    }
}

int main(){
    Mat_Graph G;
    createMat_Graph(&G);

    //深度优先搜索
    for(int i=0; i<G.vertexNum; i++){
        visited[i] = 0;
    }
    dfs(G, 0);

    printf("\n");
    
    //广度优先搜索
    for(int i=0; i<G.vertexNum; i++){
        visited[i] = 0;
    }
    bfs(G, 0);
}