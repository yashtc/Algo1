/*
Question 1:
Download the text file here. (Right click and save link as)

The file contains the adjacency list representation of a simple undirected graph. There are 200 vertices labeled 1 to 200.
The first column in the file represents the vertex label, and the particular row (other entries except the first column) tells all the vertices that the vertex is adjacent to.
So for example, the 6th row looks like : "6 155 56 52 120 ......".
This just means that the vertex with label 6 is adjacent to (i.e., shares an edge with) the vertices with labels 155,56,52,120,......,etc

Your task is to code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph to compute the min cut.
(HINT: Note that you'll have to figure out an implementation of edge contractions.
Initially, you might want to do this naively, creating a new graph from the old every time there's an edge contraction.
But you should also think about more efficient implementations.)
(WARNING: As per the video lectures, please make sure to run the algorithm many times with different random seeds, and remember the smallest cut that you ever find.)
Write your numeric answer in the space provided. So e.g., if your answer is 5, just type 5 in the space provided.
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>
#define SIZE 200

using namespace std;

struct edge
{
       std::string n2;
       edge *next;
};

struct node
{
       std::string n1;
       node* down;
       edge* first;
}*head;

void getCompEdge(int m, std::string *n1, std::string *n2)
{
     int r=rand()%m;
     if(r==0) r=1;
     node *th=head;
     edge *te=th->first;
     while(th!=NULL && r>1)
     {
               while(r>1 && te!=NULL)
               {
                         r--;
                         te=te->next;
               }
               if(te==NULL) {th=th->down; te=th->first;}
     }
	*n1=th->n1; *n2=te->n2; 
}

int kargers(int m)
{
	for(int l=1; l<=SIZE-2; l++)
    {
            std::string comp_node1, comp_node2;
            getCompEdge(m, &comp_node1, &comp_node2);
	        node *newnode=new node;
            newnode->down=head;
            newnode->first=NULL;
            newnode->n1=comp_node1+","+comp_node2;
            head=newnode;
            /*remove first node*/
            node *b4first=head, *fnode=head;
            while(fnode->n1!=comp_node1) {b4first=fnode; fnode=fnode->down;}
            b4first->down=fnode->down;
            /*remove second node*/
            node *b4second=head, *snode=head;
            while(snode->n1!=comp_node2) {b4second=snode; snode=snode->down;}
            b4second->down=snode->down;
            /*merge edges of the two nodes*/
            edge *tedge=fnode->first;
            while(tedge!=NULL)
            {
                 if(tedge->n2==comp_node2) { m--; tedge=tedge->next;}
                 else
                 {
                      edge *newedge=new edge;
                 newedge->n2=tedge->n2;
                 newedge->next=newnode->first;
                 newnode->first=newedge;
                 node *tnode=head;
                 while(tnode->n1!=tedge->n2) tnode=tnode->down;
                 edge *ttedge1=tnode->first;
                 while(ttedge1->n2!=comp_node1) ttedge1=ttedge1->next;
                 ttedge1->n2=newnode->n1;
                 tedge=tedge->next;
                 }
            }
            tedge=snode->first;
            while(tedge!=NULL)
            {
                 if(tedge->n2==comp_node1) { m--; tedge=tedge->next; }
                 else
                 {
                      edge *newedge=new edge;
                 newedge->n2=tedge->n2;
                 newedge->next=newnode->first;
                 newnode->first=newedge;
                 node *tnode=head;
                 while(tnode->n1!=tedge->n2) tnode=tnode->down;
                 edge *ttedge1=tnode->first;
                 while(ttedge1->n2!=comp_node2) ttedge1=ttedge1->next;
                 ttedge1->n2=newnode->n1;
                 tedge=tedge->next;
                 }
            }
    }
    int min_cut=0;
    edge *hd=head->first;
    while(hd!=NULL)
    {
                            min_cut++;
                            hd=hd->next;
    }
    return min_cut;
}

int main(int argc, char *argv[])
{
    int min=200;
	for(long h=1; h<=280000; h++)
    {
    srand(h);
    FILE *f=fopen("kargerMinCut.txt","r");
    int m=0;
	for(int i=1; i<=SIZE; i++)
    {
            char *a=new char[200];
            fgets(a,200,f);
            node *newnode=new node;
            std::stringstream sout;
            sout << i;
            newnode->n1=sout.str();
            newnode->down=NULL;
            newnode->first=NULL;
            if(head==NULL) head=newnode;
            else
            {
                node *temp=head;
                while(temp->down!=NULL) temp=temp->down;
                temp->down=newnode;
            }
            while(*a!='\t') a++;
            a++;
            while(true)
            {
                    int tn=atoi(a);
                    if(tn<1) break;
                    m++;
                    std::stringstream sout;
                    sout << tn;
                    edge *newedge=new edge;
                    newedge->n2=sout.str();
                    edge *temp=newnode->first;
                    newnode->first=newedge;
                    newedge->next=temp;
                    for(; (a[0]!='\t' && a[0]!='\n'); a=a+1);
                    a=a+1;
            }
    }
    fclose(f);
    int thistime=kargers(m);
    if(thistime<min)
    {
        min=thistime;
        cout<<"\nMin-Cut: "<<thistime<<endl;
    }
    head=NULL;
    }
    cout<<"\n\nFinal min: "<<min;
    system("PAUSE");
    return EXIT_SUCCESS;
}
