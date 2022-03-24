#include<stdio.h>
#include<string.h>

#define N_CHAR 128
#define MAX 1024
#define INF 9999

int dijsktra(int **,int ,int ,int );


int main(){
    int people_num,edges_num;
    char result[MAX][MAX];
    int n = 1;
    while(1){
        scanf("%d %d",&people_num,&edges_num);
        if(people_num==0)
            break;
        char name[people_num+1][N_CHAR];

        int cost[people_num+1][people_num+1];
        for(int i=0;i<people_num+1;i++){
            for(int j=0;j<people_num+1;j++)
                cost[i][j] = INF; // people can't pass the way.
        }
        int *p_cost[people_num+1];

        for(int i=1;i<people_num+1;i++)
            scanf("%s",name[i]);

        for(int i=0;i<edges_num;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            cost[a][b] = c;
            cost[b][a] = cost[a][b]; //it takes cost k to get from location i to location j,so cost[i][j]=cost[j][i].
        }

        for(int i=0;i<people_num+1;i++)
            p_cost[i] = cost[i];

        int tmp_des = 1;
        int des = 1;
        int sum[people_num+1];
        for(int i=0;i<people_num+1;i++)
            sum[i]  = 0;
        int min = MAX;
        while(tmp_des <= people_num){
            for(int i = 1;i <= people_num;i++){
                if(i==tmp_des)
                    continue;
                int shortest = dijsktra(p_cost,people_num,i,tmp_des);
                sum[tmp_des]+=shortest; //the total distance from everyone to the the meeting point.
            }
            if(sum[tmp_des] < min){//if the distance is shorter the the min one
                min = sum[tmp_des];
                des = tmp_des;
           }
           tmp_des++;
        }
     strcpy(result[n++],name[des]);//store the min sum's name to the result array.
    }

    for(int i=1;i<n;i++)
        printf("Case #%d %s\n",i,result[i]);
}

int dijsktra(int **cost,int people,int source,int target){
    int dist[people+1],selected[people+1];
    int start = source;

    for(int i=0;i<people+1;i++)
        selected[i] = 0; //all points have not been walked
    for(int i=1;i< people+1;i++)
        dist[i] = INF;

    selected[start]=1;//start point has been walked
    dist[start] = 0; //distance from start point to start point is 0
    while(selected[target] ==0){ //if does not arrive the target
        int min = INF;
        int m = 0;
        for(int i=1;i< people+1;i++){
            int d = dist[start] + cost[start][i]; //d = distance from start to the point
            if(d < dist[i] && selected[i]==0) //if d is shorter then the last way and i hasn't been walked
                dist[i] = d;
            if(min>dist[i] && selected[i]==0){//if dist[i] is shorter then the min and i hasn't been walked
                min = dist[i];
                m = i;
            }
        }
        start = m; //the shortest way is from the start point to m point
        selected[start] = 1; //the point has been walked
    }
    return dist[target];
}
