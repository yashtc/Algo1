/*
Question 1:
Download the text file here. Zipped version here. (Right click and save link as)

The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714.
Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex).
So for example, the 11th row looks liks : "2 47646".
This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646

Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.

Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, separated by commas (avoid any spaces).
So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100".
If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms.
Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0".

WARNING: This is the most challenging programming assignment of the course.
Because of the size of the graph you may have to manage memory carefully.
The best way to do this depends on your programming language and environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>
#define SIZE 875714
#define FILENAME "SCC.txt"

using namespace std;

struct edge
{
       long head;
       edge* next;
};

edge* g[SIZE+1];
bool visited[SIZE+1];
long t[SIZE+1];
long curr_time=0;
static long sccs[6];

void insert(long size)
{
     for(int i=1; i<6; i++)
         if(sccs[i]<size)
         {
                 for(int j=5; j>i; j--)sccs[j]=sccs[j-1];
                 sccs[i]=size;
                 break;
         }
}

long DFS(long i, long size)
{
     visited[i]=true;
     size++;
     edge *temp=g[i];
     while(temp!=NULL)
     {
         if(!(visited[temp->head])) size=DFS(temp->head, size);
         temp=temp->next;
     }
     t[SIZE-curr_time]=i;
     curr_time++;
     return size;
}

void DFSloop()
{
     long size=0;
     long times_dfs_done=0;
     for(long i=SIZE; i>0; i--)
     {
             size=0;
             if(!visited[i])
             {
                 times_dfs_done++;
                 size=DFS(i, 0);
             }
             insert(size);
     }
}

int main(int argc, char *argv[])
{
    FILE *f=fopen(FILENAME,"r");
	for(int i=1; i<=SIZE; i++)
    {
            g[i]=NULL;
            visited[i]=false;
    }
	char *a=new char[20];
    while(fgets(a,20,f))
	{
            long n1, n2;
            n2=atol(a);
            while(a[0]!=' ') a++;
            n1=atol(++a);
            edge *newedge=new edge;
            newedge->head=n2;
            newedge->next=g[n1];
            g[n1]=newedge;
            a=new char[20];
    }
    fclose(f);
    DFSloop();
    FILE *fp=fopen("times.txt","w");
    for(int k=1; k<=SIZE; k++)
    {
            a=new char[20];
            sprintf(a,"%lu\n",t[k]);
            fputs(a, fp);
    }
    fclose(fp);
    system("PAUSE");
    return EXIT_SUCCESS;
}
