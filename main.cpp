#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include"red_polje.h"
//#include"red_pokazivac.h"
using namespace std;

red *glavni=new red;
red *pom=new red;
red *brzi=new red;
klijent e, Ispis[100];
int i=0, br=0, brojac;

void generiranje(tcetvorke *cetvorke, int n){
    for(int x=0; x<n; x++){
        cetvorke[x].ai=rand()%400+100;
        cetvorke[x].bi=rand()%400+100;
        cetvorke[x].ci=rand()%6+1;
        if(cetvorke[x].ci==6) cetvorke[x].di=rand()%2+3;
        else cetvorke[x].di=rand()%4+1;
    }
}
void ispis(){
    cout<<"Ime i Prezime: "<<e.ime<<" "<<e.pre<<endl;
    cout<<"Godina rodjenja: "<<e.god_rod<<endl;
    cout<<"Stanje tekuci: "<<e.stanje_tekuci<<endl;
    cout<<"Stanje devizni: "<<e.stanje_devizni<<endl;
    cout<<"Prioritet: ";
    switch (e.ce.ci){
        case 1: cout<<"Umirovljenik"<<endl; break;
        case 2: cout<<"Invalid"<<endl; break;
        case 3: cout<<"Ima trudnicu sa sobom"<<endl; break;
        case 4: cout<<"VIP klijent"<<endl; break;
        case 5: cout<<"Korisnik banke"<<endl; break;
        case 6: cout<<"Obicni klijent"<<endl; break;
    }
    cout<<"Transakcija: ";
    switch (e.ce.di){
        case 1: cout<<"Uplata"<<endl; break;
        case 2: cout<<"Isplata"<<endl; break;
        case 3: cout<<"Placanje racuna"<<endl; break;
        case 4: cout<<"Krediti"<<endl; break;
    }
    cout<<"-------------------------------------"<<endl;
}
void unos(tcetvorke *cet, int n){
    short a=0, b=0, c=0, d=0;
    do{
        cout<<"Unesi ime klijenta: ";
        cin.ignore();
        cin.getline(e.ime,20);
        cout<<"Unesi prezime klijenta: ";
        cin.getline(e.pre,30);
        cout<<"Unesi godinu rodjenja: ";
        cin>>e.god_rod;
        cout<<"Unesi stanje na tekucem racunu (kn): ";
        cin>>e.stanje_tekuci;
        cout<<"Unesi stanje na deviznom racunu ($): ";
        cin>>e.stanje_devizni;
        e.ce=cet[i];
        switch (e.ce.di){
            case 1: a++; break;
            case 2: b++; break;
            case 3: c++; break;
            case 4: d++; break;
        }
        EnQueueQ(e,glavni);
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
        cout<<"-----------------------"<<endl;
        sort(glavni, i);
        i++; br++;
     }while((a<1 || b<1 || c<1 || d<1) && i<n);
     cout<<endl<<"Klijenti koji na deviznom raèunu imaju više od 10.000 kuna:"<<endl;
     cout<<"___________________________________________________________"<<endl;
     InitQ(pom);
     while(!IsEmptyQ(glavni)){
        e=FrontQ(glavni);
        EnQueueQ(e,pom);
        if(e.stanje_devizni*5.7>10000) ispis();
        DeQueueQ(glavni);
     }
     InitQ(glavni);
     while(!IsEmptyQ(pom)){
        e=FrontQ(pom);
        EnQueueQ(e,glavni);
        DeQueueQ(pom);
     }
}
void brze_transakcije(){
     InitQ(brzi);
     InitQ(pom);
     while(!IsEmptyQ(glavni)){
        e=FrontQ(glavni);
        if(e.ce.di==3) {
            EnQueueQ(e,brzi);
            br--;
        }
        else EnQueueQ(e,pom);
        DeQueueQ(glavni);
     }
     InitQ(glavni);
     cout<<endl<<"Glavni red u banci nakon brzih transakcija:"<<endl;
     cout<<"____________________________________________"<<endl;
     while(!IsEmptyQ(pom)){
        e=FrontQ(pom);
        ispis();
        EnQueueQ(e,glavni);
        DeQueueQ(pom);
     }
     cout<<endl<<"Brzi red koji rad samo plaèanje raèuna: "<<endl;
     cout<<"____________________________________________"<<endl;
     while(!IsEmptyQ(brzi)){
        e=FrontQ(brzi);
        ispis();
        DeQueueQ(brzi);
     }
}
void brisanje_VIP(){
     InitQ(pom);
     while(!IsEmptyQ(glavni)){
        e=FrontQ(glavni);
        DeQueueQ(glavni);
        if(e.ce.ci==4 && e.ce.di==1 && e.god_rod>1982 && e.stanje_tekuci<100) {br--; continue;}
        if(e.ce.ci==1 && e.ce.di==2 && e.stanje_tekuci>5000) {br--; continue;}
        EnQueueQ(e,pom);
     }
     InitQ(glavni);
     cout<<endl<<"Red u banci nakon brisanje VIP klijenata i umirovljenika:"<<endl;
     cout<<"_________________________________________________________"<<endl;
     while(!IsEmptyQ(pom)){
        e=FrontQ(pom);
        ispis();
        EnQueueQ(e,glavni);
        DeQueueQ(pom);
     }
}
void novi_salter(){
    if(brojac--){
        e=FrontQ(glavni);
        ispis();
        DeQueueQ(glavni);
        novi_salter();
    }
}
int main(){
    int N;
    short izbor;
    bool zas=true;
    tcetvorke *cetvorke;
    srand(time(NULL));
    cout<<"Unesi broj N za generiranje N cetvorki: ";
    cin>>N;
    cetvorke=new tcetvorke[N];
    generiranje(cetvorke, N);
    do{
        cout<<"************************IZBORNIK************************"<<endl;
        cout<<"1. Dodavanje zapisa klijenata banke u red"<<endl;
        cout<<"2. Simulirati red brzih transakcija"<<endl;
        cout<<"3. Brisanje VIP klijenata mladjih od 30g i umirovljenika"<<endl;
        cout<<"4. Simulacija otvaranja novog saltera"<<endl;
        cout<<"0. IZLAZ iz programa"<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"Unesi svoj izbor: ";
        cin>>izbor;
        system("cls");
        switch (izbor){
            case 1:
                if(zas) InitQ(glavni);
                unos(cetvorke, N);
                zas=false;
                break;
            case 2:
                brze_transakcije();
                break;
            case 3:
                brisanje_VIP();
                break;
            case 4:
                brojac=br*0.7;
                cout<<endl<<"Glavni red u banci nakon otvaranja novog saltera:"<<endl;
                cout<<"_________________________________________________________"<<endl;
                novi_salter();
                int y=0;
                while(!IsEmptyQ(glavni)){
                    e=FrontQ(glavni);
                    Ispis[y++]=e;
                    DeQueueQ(glavni);
                 }
                 cout<<endl<<"Red na novom salteru:"<<endl;
                 cout<<"___________________________"<<endl;
                 for(int x=y-1; x>=0; x--){
                    e=Ispis[x];
                    ispis();
                 }
                 break;
        }
    }while(izbor);
    cout<<"Program je gotov sa radom!"<<endl;
    system("pause");
    return 0;
}
