/*
Question 1:
In this programming problem you'll code up Dijkstra's shortest-path algorithm. 
Download the text file here. (Right click and save link as). 
The file contains an adjacency list representation of an undirected weighted graph with 200 vertices labeled 1 to 200.
Each row consists of the node tuples that are adjacent to that particular vertex along with the length of that edge.
For example, the 6th row has 6 as the first entry indicating that this row corresponds to the vertex labeled 6.
The next entry of this row "141,8200" indicates that there is an edge between vertex 6 and vertex 141 that has length 8200.
The rest of the pairs of this row indicate the other vertices adjacent to vertex 6 and the lengths of the corresponding edges.

Your task is to run Dijkstra's shortest-path algorithm on this graph, using 1 (the first vertex) as the source vertex, and to compute the shortest-path distances between 1 and every other vertex of the graph.
If there is no path between a vertex v and vertex 1, we'll define the shortest-path distance between 1 and v to be 1000000. 

You should report the shortest-path distances to the following ten vertices, in order: 7,37,59,82,99,115,133,165,188,197.
You should encode the distances as a comma-separated string of integers.
So if you find that all ten of these vertices except 115 are at distance 1000 away from vertex 1 and 115 is 2000 distance away, then your answer should be 1000,1000,1000,1000,1000,2000,1000,1000,1000,1000.
Remember the order of reporting DOES MATTER, and the string should be in the same order in which the above ten vertices are given.
Please type your answer in the space provided.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation of Dijkstra's algorithm should work fine.
OPTIONAL: For those of you seeking an additional challenge, try implementing the heap-based version.
Note this requires a heap that supports deletions, and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap.
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define SIZE 200

using namespace std;

struct edge
{
       int n2;
       int weight;
       edge *next;
};

void dijkstra(edge **g, long *dist, int s)
{
     bool visited[SIZE+1];
     for(int i=1; i<=SIZE; visited[i++]=false);
     visited[s]=true;
     dist[s]=0;
     for(int i=2; i<=SIZE; i++)
     {
             int n2, wt=1000000;
             for(int i=1; i<=SIZE; i++)
             {
                     if(visited[i])
                     {
                             edge *temp=g[i];
                             while(temp!=NULL)
                             {
                                     if(!visited[temp->n2] && (dist[i]+temp->weight)<wt)
                                     {
                                             n2=temp->n2;
                                             wt=(dist[i]+temp->weight);
                                     }
                                     temp=temp->next;
                             }
                     }
             }
             visited[n2]=true;
             dist[n2]=wt;
     }
}

int main(int argc, char *argv[])
{
    edge **g=new edge*[SIZE+1];
    long dist[SIZE+1];
    FILE *f=fopen("dijkstraData.txt","r");
    for(int i=1; i<=SIZE; i++)
    {
            g[i]=NULL;
            dist[i]=1000000;
    }
    char *a=new char[400];
    while(fgets(a,400,f))
    {
            int n1=atoi(a);
            while(a[0]!='\t') a++;
            a++;
            while(true)
            {
                    int n2=atoi(a);
                    while(a[0]!=',') a++;
                    a++;
                    int wt=atoi(a);
                    edge *newedge=new edge;
                    newedge->n2=n2;
                    newedge->weight=wt;
                    newedge->next=g[n1];
                    g[n1]=newedge;
                    while(a[0]!='\t' && strlen(a)>=3) a++;
                    if(strlen(a)<3) break;
                    a++;
            }
            a=new char[400];
    }
    fclose(f);
    dijkstra(g,dist,1);
    cout<<"Shortest Path Distances to the vertices 7,37,59,82,99,115,133,165,188,197:\n";
    cout<<dist[7]<<","<<dist[37]<<","<<dist[59]<<","<<dist[82]<<","<<dist[99]<<","<<dist[115]<<","<<dist[133]<<","<<dist[165]<<","<<dist[188]<<","<<dist[197]<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
