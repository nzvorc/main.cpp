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

struct element{
    klijent el;
    element *sljedeci;
};

struct red{
element *front,*rear;
};

void InitQ(red *Q ){
    Q->front=new element;
    Q->rear=Q->front;
    Q->front->sljedeci=NULL;
}

klijent FrontQ(red *Q){
return Q->front->sljedeci->el;
}

void EnQueueQ(klijent e, red *Q){
    element *novi=new element;
    novi->el=e;
    novi->sljedeci=NULL;
    Q->rear->sljedeci=novi;
    Q->rear=novi;
}

void DeQueueQ(red *Q){
    element *brisi=Q->front;
    Q->front=Q->front->sljedeci;
    delete brisi;
}

bool IsEmptyQ(red *Q){
    return Q->front==Q->rear;
}

void sort(red *Q, int i){

};
