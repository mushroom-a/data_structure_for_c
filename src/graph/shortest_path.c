#include<stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 9999

typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType edge[MAXSIZE][MAXSIZE];
    int vertexNum;
    int edgeNum;
} Graph;

void createGraph(Graph* G) {
    G->vertexNum = 9;
    G->edgeNum = 16;
    for(int i=0; i < G->vertexNum; i++) {
        G->vertex[i] = i;
    }

    //初始化邻接矩阵
    for (int i=0; i < G->vertexNum; i++) {
        for (int j=0; j < G->vertexNum; j++) {
            if(i == j){
                G->edge[i][j] = 0;
            }
            else{
                G->edge[i][j] = MAX;
            }
        }
    }

    G->edge[0][1] = 1;
    G->edge[0][2] = 5;

    G->edge[1][2] = 3; 
    G->edge[1][3] = 7;
    G->edge[1][4] = 5;

    G->edge[2][4] = 1;
    G->edge[2][5] = 7;

    G->edge[3][4] = 2;
    G->edge[3][6] = 3;

    G->edge[4][5] = 3;
    G->edge[4][6] = 6;
    G->edge[4][7] = 9;

    G->edge[5][7] = 5;

    G->edge[6][7] = 2;
    G->edge[6][8] = 7;

    G->edge[7][8] = 4;

    for(int i=0; i < G->vertexNum; i++) {
        for(int j=i+1; j < G->vertexNum; j++) {
            G->edge[j][i] = G->edge[i][j];
        }
    }
}

int minDist(Graph G, int dist[], int found[]) {
    int min = MAX;
    int minIndex = -1;
    for(int i=0; i < G.vertexNum; i++) {
        if(!found[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(Graph G, int start, int end) {
    int found[MAXSIZE];
    int path[MAXSIZE];
    int dist[MAXSIZE];
    for(int i=0; i < G.vertexNum; i++) {
        found[i] = 0;
        path[i] = -1;
        dist[i] = G.edge[start][i];
    }

    found[start] = 1;
    dist[start] = 0;

    int next;
    //每次找到一个距离最短的顶点，并更新start到其余顶点的距离
    //最后得到从start到每个顶点的最短路径长度和路径信息
    for(int i=1; i < G.vertexNum; i++) {
        next = minDist(G, dist, found);
        found[next] = 1;
        for(int j=0; j < G.vertexNum; j++) {
            if(found[j] == 0) {
                if(dist[next] + G.edge[next][j] < dist[j]) {
                    dist[j] = dist[next] + G.edge[next][j];
                    path[j] = next;
                }
            }
        }
    }

    int j=end;
    printf("Shortest path from %d to %d is:%d \n", start, end, dist[end]);
    printf("V%d <-", end);
    while(path[j] != -1) {
        printf("V%d <-", path[j]);
        j = path[j];
    }
    printf("V%d\n", start);

}

void floyd(Graph G) {
    int dist[MAXSIZE][MAXSIZE];
    int path[MAXSIZE][MAXSIZE];
    for(int i=0; i < G.vertexNum; i++) {
        for(int j=0; j < G.vertexNum; j++) {
            dist[i][j] = G.edge[i][j];
            path[i][j] = j;
        }
    }

    //k为中间顶点，i为起点，j为终点
    //中间顶点在外层循环，保证每次更新dist[i][j]时，dist[i][k]和dist[k][j]已经是最短路径长度
    for(int k=0; k < G.vertexNum; k++) {
        for(int i=0; i < G.vertexNum; i++) {
            for(int j=0; j < G.vertexNum; j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    printf("Shortest path matrix:\n");
    for(int i=0; i < G.vertexNum; i++) {
        for(int j=0; j < G.vertexNum; j++) {
            if(dist[i][j] == MAX) {
                printf("INF ");
            }
            else {
                printf("%3d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    Graph G;
    createGraph(&G);
    dijkstra(G, 0, 8);
    floyd(G);
}