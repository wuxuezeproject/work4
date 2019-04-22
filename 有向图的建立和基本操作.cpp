#include "stdio.h"
#include<stdlib.h>
#include<iostream>
using namespace std;
#define max 20
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode
{
	char date;
	ArcNode *firstarc;
}VNode,AdjList[max];
typedef struct
{
  AdjList vertices;
  int vexnum,arcnum;
}Graph;
typedef struct
{
	int Date[max];
	int front,rear;
}Queue;
void initqueue(Queue &Q)
{
	Q.rear=Q.front=0;
}
void enqueue(Queue &Q,int e)
{
	if((Q.rear+1)%max==Q.front)return;
	Q.Date[Q.rear]=e;
	Q.rear++;
}

void dequeue(Queue &Q,int &e)
{
	e=Q.Date[Q.front];
	Q.front++;
}
void createG(Graph &G)
{
	char m,n;
	int tail=0,head=0,j;
	for(int i=0;i<G.arcnum;i++)
	{
         cin>>m>>n;
		for(j=0;j<G.vexnum;j++)
		{
			if(G.vertices[j].date==m)
				tail=j;
			if(G.vertices[j].date==n)
				head=j;
		}
		ArcNode *q,*p=new ArcNode;
		p->adjvex=head;
		p->nextarc=NULL;
        q=G.vertices[tail].firstarc;
		G.vertices[tail].firstarc=p;
		p->nextarc=q;
	}
}
bool visited1[max];
int FirstAdjvex(Graph &G,int v)
{
	if(v<0||v>max)return -1;
	ArcNode *p=G.vertices[v].firstarc;
	if(p!=NULL)
		return p->adjvex;
	else
		return -1;
}

int NextAdjvex(Graph &G,int v,int w)
{
	if(v<0||v>max)return -1;
	if(w<0||w>max)return -1;
	ArcNode *p=G.vertices[v].firstarc;
	while(p!=NULL&&p->adjvex!=w)
		p=p->nextarc;
	if(p->nextarc!=NULL)
		return p->nextarc->adjvex;
	else return -1;
}

void DFS(Graph &G,int v)
{
	visited1[v]=true;
	cout<<G.vertices[v].date<<" ";
	for(int w=FirstAdjvex(G,v);w!=-1;w=NextAdjvex(G,v,w))
		if(!visited1[w])
        DFS(G,w);
}
void DFSTravel(Graph &G)
{
	int v;
	for(v=0;v<G.vexnum;v++)
	visited1[v]=false;
	for(v=0;v<G.vexnum;v++)
	{
		if(!visited1[v])
			DFS(G,v);
	}
}

bool visited2[max];
void BFSTravel(Graph &G)
{
    int v,u,w;
	Queue Q;
	for(v=0;v<G.vexnum;v++)
	visited2[v]=false;
	initqueue(Q);
	for(v=0;v<G.vexnum;v++)
	if(visited2[v]==false)
	{
		visited2[v]=true;
		cout<<G.vertices[v].date<<" ";
		enqueue(Q,v);//
		while(Q.rear!=Q.front)
		{
			dequeue(Q,u);
		for(int w=FirstAdjvex(G,u);w!=-1;w=NextAdjvex(G,u,w))
		  if(!visited2[w])
		  {
           visited2[w]=true;
		  cout<<G.vertices[w].date<<" ";
		   enqueue(Q,w);
		  }
		}
	}
}
int main()
{
	Graph G;
	cin>>G.vexnum;
	for(int i=0;i<G.vexnum;i++)
	{
	 cin>>G.vertices[i].date;
	 G.vertices[i].firstarc=NULL;
	}
	cin>>G.arcnum;
    createG(G);
	DFSTravel(G);
	cout<<"\n";
	BFSTravel(G);
	system("pause");
	return 0;
}