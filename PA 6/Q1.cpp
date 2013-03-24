/*
Question 1
Download the text file here. (Right click and save link as).

The goal of this problem is to implement a variant of the 2-SUM algorithm (covered in the Week 6 lecture on hash table applications).
The file contains 500,000 positive integers (there might be some repetitions!).
This is your array of integers, with the ith row of the file specifying the ith entry of the array.

Your task is to compute the number of target values t in the interval [2500,4000] (inclusive) such that there are distinct numbers x,y in the input file that satisfy x+y=t.
(NOTE: ensuring distinctness requires a one-line addition to the algorithm from lecture.)

Write your numeric answer (an integer between 0 and 1501) in the space provided.


OPTIONAL COMMENT: You might notice that the chosen targets are relatively small numbers. (There is a good reason for this.
Can you guess what would be the problem with a similar interval of larger targets?)
You are welcome to add extra optimizations that take advantage of this fact, though it is not required for the assignment.

OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing your own hash table for it.
For example, you could compare performance under the chaining and open addressing approaches to resolving collisions.

REQUEST FOR COMMENTS: Do you have a favorite hash table application that could serve as a programming assignment for this course?
Post your idea to the discussion form, and maybe it will be used in the next iteration of this course!
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define SIZE 12345

using namespace std;

struct bucket
{
       long n;
       bucket *next;
};

int main(int argc, char *argv[])
{
    char *a=new char[10];
    bucket **hash=new bucket*[SIZE];
    FILE *f=fopen("HashInt.txt","r");
    for(long i=0; i<SIZE; hash[i++]=NULL);
    for(long i=1; i<=500000; i++)
    {
             a=new char[10];
             fgets(a,10,f);
             long no=atol(a);
             long hash_val=no%SIZE;
             if(hash[hash_val]==NULL)
             {
                 hash[hash_val]=new bucket;
                 hash[hash_val]->n=no;
             }
             else
             {
                 bucket *temp=hash[hash_val];
                 while(temp!=NULL && temp->n!=no) temp=temp->next;
                 if(temp==NULL)
                 {
                     bucket *newhd=new bucket;
                     newhd->n=no;
                     newhd->next=hash[hash_val];
                     hash[hash_val]=newhd;
                 }
             }
    }
    cout<<"Reached here";
    fclose(f);
    long ans=0;
    for(int t=2500; t<=4000; t++)
            for(long i=1; i<=SIZE; i++)
            {
                     bucket *temp=hash[i];
                     while(temp!=NULL)
                     {
                             long n1=temp->n;
                             if(n1!=i/2)
                             {
                                        long n2=t-n1;
                                        bucket *temp2=hash[n2%SIZE];
                                        while(temp2!=NULL && temp2->n!=n2) temp2=temp2->next;
                                        if(temp2!=NULL)
                                        {
                                                ans++;
                                                i=SIZE+1;
                                                break;
                                        }
                             }
                     }
            }
    cout<<"Total number of target values: "<<ans;
    system("PAUSE");
    return EXIT_SUCCESS;
}
