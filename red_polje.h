#include<iostream>
#include<cstdlib>
using namespace std;

struct tcetvorke{
    short ai,bi,ci,di;
};

struct klijent{
    char ime[20], pre[30];
    int god_rod;
    float stanje_tekuci, stanje_devizni;
    tcetvorke ce;
};

struct red{
    klijent el[100];
    int front, rear;
};

void InitQ(red *Q){
    Q->front=0; Q->rear=99;
}

klijent FrontQ(red *Q){
    return Q->el[Q->front];
}

void EnQueueQ(klijent e, red *Q){
    if(Q->rear==99) {
        Q->rear=0;
        Q->el[Q->rear]=e;
    }
    else{
        Q->rear++;
        Q->el[Q->rear]=e;
    }
}

void DeQueueQ(red *Q){
    if(Q->front==99) Q->front=0;
    else Q->front++;
}

bool IsEmptyQ(red *Q){
    if(Q->rear+1==Q->front || (Q->rear==99 && Q->front==0)) return true;
    else return false;
}

void sort(red *Q, int i){
    klijent p;
    for(int x=i; x>0; x--) if(Q->el[x].ce.ci < Q->el[x-1].ce.ci) {
                p=Q->el[x];
                Q->el[x]=Q->el[x-1];
                Q->el[x-1]=p;
        }
}
