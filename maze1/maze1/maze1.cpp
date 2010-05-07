/*
ID: eclipse5
PROG: maze1
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int infinity = 99999999;

int w,h;
char maze[2*100+1][2*38+1];
int exits[2][2],ecnt=0;
int dist1[100][38];
int dist2[100][38];
int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   

bool isexit(int i,int j,int d)
{
	switch(d)
	{
	case 0:if (i==0) return true;break;
	case 1:if (j==w-1) return true;break;
	case 2:if (i==h-1) return true;break;
	case 3:if (j==0) return true;break;
	}
	return false;
}

void init()		//input data and create graph
{
	int i,j,k;
	int x,y;
	scanf("%d%d\n",&w,&h);
	for (i=0;i<h*2+1;i++)
	{
		for (j=0;j<w*2+1;j++)
			maze[i][j]=getchar();
		getchar();
	}
	for (i=0;i<h;i++)
		for (j=0;j<w;j++)
		{
			for (k=0;k<4;k++)
			{
				x=2*i+1+dir[k][0];
				y=2*j+1+dir[k][1];
				bool used = false;
				if (maze[x][y]==' '&&!used&&isexit(i,j,k))
				{
					exits[ecnt][0]=i;
					exits[ecnt][1]=j;
					ecnt++;
					used=true;											
				}
			}
		}
}

void getmin(int &x,int &y,int dist[100][38],bool vis[100][38])
{
	int mincost = INT_MAX;
	int i,j;
	for (i=0;i<h;i++)
		for (j=0;j<w;j++)
			if (!vis[i][j]&&dist[i][j]<mincost)
			{
				mincost = dist[i][j];
				x=i;
				y=j;
			}
}

void dijkstra(int srcx, int srcy,int distance[100][38])
{
	bool visited[100][38];
	int i,j,k;
	int x,y,x1,y1;

	for (i=0;i<h;i++)
		for (j=0;j<w;j++)
		{
			distance[i][j]=infinity;
			visited[i][j]=false;
		}
	distance[srcx][srcy]=0;

	for (i=0;i<h;i++)
		for (j=0;j<w;j++)
		{
			getmin(x,y,distance,visited);
			visited[x][y]=true;
			for (k=0;k<4;k++)
			{
				x1=2*x+1+dir[k][0];
				y1=2*y+1+dir[k][1];
				if (x1>=0&&x1<2*h+1&&y1>=0&&y1<2*w+1)	//û�ڱ߽���
					if (maze[x1][y1]==' ') //��ͨ
					{
						x1=x+dir[k][0];
						y1=y+dir[k][1];
						if (!visited[x1][y1]&&distance[x][y]+1<distance[x1][y1])
							distance[x1][y1]=distance[x][y]+1;
					}	
			}
		}	
}

void solve()
{
	int i,j,d;
	int ans=0;
	dijkstra(exits[0][0],exits[0][1],dist1);
	dijkstra(exits[1][0],exits[1][1],dist2);
	for (i=0;i<h;i++)
		for (j=0;j<w;j++)
		{
			d=min(dist1[i][j],dist2[i][j]);
			if (d<infinity&&d>ans) ans=d;
		}
	printf("%d\n",ans+1);
}

int main()
{
	freopen("maze1.in","r",stdin);
	freopen("maze1.out","w",stdout);
	init();
	solve();
	return 0;
}