#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "TREE.H"
#include "EVAL.h"

#define MAXI 10005
#define NROPERATORI 17 // ( ) + - * / ^ #(diferit) = < > cos sin logaritm exponential modul radical

#define INFINIT 2147483640 //apx cel mai mare int posibil
#define EPSILON 0.0001

using namespace std;

//STIVA VARIABILE: Opvar , varf: top1
//STIVA OPERATORI: Op  , varf: top2

int top1=-1, top2=-1,indice, nrVar=0;
char *p;

//Burghelea
struct variabile // ex: x 10
{
    char nume[MAXI];
    double valoare;
} var[MAXI], stiva_Opvar[MAXI];

struct operatorii // ( ) + - * / ^ # = < > cos sin ln exp abs sqrt
{
    char nume[10];
    int prioritate;
} operatori[20], stiva_Op[MAXI];


int caz_paranteze=0,i_paranteze; // pt afisare pe ecran

void initializare_operatori() //priority
{
    strcpy(operatori[0].nume,"(");
    operatori[0].prioritate=0;
    strcpy(operatori[1].nume,")");
    operatori[1].prioritate=0;
    strcpy(operatori[2].nume,"+");
    operatori[2].prioritate=1;
    strcpy(operatori[3].nume,"-");
    operatori[3].prioritate=1;
    strcpy(operatori[4].nume,"*");
    operatori[4].prioritate=2;
    strcpy(operatori[5].nume,"/");
    operatori[5].prioritate=2;
    strcpy(operatori[6].nume,"^");
    operatori[6].prioritate=3;
    strcpy(operatori[7].nume,"#");
    operatori[7].prioritate=4;
    strcpy(operatori[8].nume,"=");
    operatori[8].prioritate=4;
    strcpy(operatori[9].nume,"<");
    operatori[9].prioritate=4;
    strcpy(operatori[10].nume,">");
    operatori[10].prioritate=4;
    strcpy(operatori[11].nume,"cos");
    operatori[11].prioritate=5;
    strcpy(operatori[12].nume,"sin");
    operatori[12].prioritate=5;
    strcpy(operatori[13].nume,"ln");
    operatori[13].prioritate=5;
    strcpy(operatori[14].nume,"exp");
    operatori[14].prioritate=5;
    strcpy(operatori[15].nume,"abs");
    operatori[15].prioritate=5;
    strcpy(operatori[16].nume,"sqrt");
    operatori[16].prioritate=5;
}

int verif_paranteze(char expresie[]) //greselile in functie de inchiderea parantezelor
{
    int i=0, nr=0, lg;
    lg=strlen(expresie);
    for(i=0; i<=lg; i++)
    {
        if(nr<0) // paranteze inchisa e in fata uneia deschise deci fals
        {
            caz_paranteze=1;i_paranteze=i-1;
            cout<<"paranteza deschisa la pozitia"<<' '<<i-1<<' ';
            return 0;
        }
        if(expresie[i]=='(')
        {
            if(expresie[i+1]==')') //nu am element intre paranteze deci fals
            {
                cout<<"Nu exista termen intre parantezele de pe pozitiile"<<' '<<i<<" si "<<i+1<<", ";
                caz_paranteze=2;i_paranteze=i;
                return 0;
            }
            nr++;
        }
        else if(expresie[i]==')')
        {
            if(expresie[i+1]=='(') // nu am operator intre paranteze deci fals
            {
                cout<<"Nu exista operator intre parantezele de pe pozitiile"<<' '<<i<<" si "<<i+1<<", ";
                caz_paranteze=3;i_paranteze=i;
                return 0;
            }
            nr--;
        }
    }
    if (nr==0)
    {
        return 1;
    }
    else
    {
        cout<<"trebuie paranteza inchisa"<<' '<<i-1<<' ';
        caz_paranteze=4;i_paranteze=i-1;
        return 0;
    }
}

void resetare(char x[], int lg)
{
    for(int i=0; i<=lg-1; i++)
        x[i]=0;
}

int eroare=0,i_eroare;
char err[100];
int verif_expresie(char expresie[], char *p, int nrVar)
{
    char st[MAXI],curent[MAXI],dr[MAXI];
    bool ST_var=0, DR_var=0, curentSemn,ST_semn=0, DR_semn=0, ok=0;
    int indice, ST_i=-1, DR_i=-1, poz=0, i;
    resetare(st,MAXI);
    resetare(curent, MAXI);
    resetare(dr,MAXI);
    p=strtok(expresie," "); // copiem pana la spatiu, spatiile separa operatorii
    while(p!=NULL)
    {
        strcpy(curent,p);
        p=strtok(NULL," "); // se copiaza operatorul din dreapta
        poz+=strlen(curent);
        if(p==NULL) break; // daca nu mai exista operator in dreapta, se iese din while
        strcpy(dr,p);
        if((strcmp(curent,"sin")==0 || strcmp(curent,"cos")==0  || strcmp(curent,"sqrt")==0  || strcmp(curent,"exp")==0  || strcmp(curent,"abs")==0 || strcmp(curent,"ln")==0 )&& strcmp(dr,"(")!=0 )
        { // daca se calculeaza sin,cos,sqrt,ln,exp si nu se deschid parantezele
            eroare=1;i_eroare=poz;strcpy(err,curent);
            cout<<"Nu exista paranteza deschisa dupa "<<curent<<" pe pozitia "<<poz<<", ";
            return 0;
        }
        curentSemn=0;
        indice=-1;
        for(int i=0; i<NROPERATORI && indice==-1; i++)
        {
            if(strcmp(curent,operatori[i].nume)==0 && operatori[i].prioritate>=1 && operatori[i].prioritate<=4)
                indice=i; // daca are prioritate 1-4 : + - * / ^  = < > pastram indicile
            if(strcmp(curent,operatori[i].nume)==0)
                curentSemn=1;
        }
        if(indice!=-1) //daca termenul curent este de prioritate 1,2,3 sau 4
        {
            ST_var=0; // initializam cu 0, verificam daca exista variabile in stanga si dreapta operatorului
            DR_var=0;
            ST_semn=0;
            DR_semn=0;

            for(i=1; i<=nrVar && !ST_var; i++) // numarul variabilelor se citeste de la tastatura
                if(strcmp(st,var[i].nume)==0) ST_var=1;

            for(i=0; i<NROPERATORI && !ST_var && !ST_semn; i++)
                if(strcmp(st,operatori[i].nume)==0) // daca in stanga este operator
                    {
                        ST_semn=1;
                        ST_i=i;
                    }
            if(ST_semn==0) ST_var=1; // daca in stanga nu este semn, inseamna ca este variabila
            for(i=1; i<=nrVar && !DR_var; i++)
                if(strcmp(dr,var[i].nume)==0)
                    DR_var=1;
            for(i=0; i<NROPERATORI && !DR_var && !DR_semn; i++)
                if(strcmp(dr,operatori[i].nume)==0) // daca in dreapta este operator
                    {
                        DR_semn=1;
                        DR_i=i;
                    }
            if (DR_semn==0) DR_var=1;// daca in dreapta nu este semn, inseamna ca este variabila
            if (!((ST_var && DR_var) || (ST_var && DR_i==0) || (ST_i==1 && DR_var) || (ST_i==1 && DR_i==0) || (ST_var && DR_i>=11) || (ST_i==1 && DR_i>=11) ))
            {
                eroare=2;
                cout<<"Nu exista un termen sau o functie de prioritate 5 in stanga si in dreapta unui operator"<<'\n';
                cout<<"pe pozitia "<<poz-1<<", ";
                return 0;
            }
        }
        else if(curentSemn==0) // daca in curent este salvata o variabila
        {
            if(ok==0)  ST_i=0;
            else ST_i=-1;
            DR_i=-1;
            for(i=0; i<NROPERATORI && ST_i==-1; i++)
                if(strcmp(st,operatori[i].nume)==0)
                    ST_i=i;
            for(i=0; i<NROPERATORI && DR_i==-1; i++)
                if(strcmp(dr,operatori[i].nume)==0)
                    DR_i=i;
            if(!((ST_i<11 && ST_i!=1 && ST_i>=0)&& (DR_i<11 && DR_i !=0 && DR_i>=0)))
            {
                eroare=3;
                cout<<"Nu exista un operator cu prioritatea de la 1 la 4 intre doi termeni sau intre un termen si o paranteza deschisa"<<'\n';
                if(st[strlen(st)-1]==')'){
                  cout<<"intre caracterele de pe pozitiile "<<poz-2<<" si "<<poz-1<<", ";
                  }
                else{
                  cout<<"intre caracterele de pe pozitiile "<<poz-1<<" si "<<poz<<", ";
                }

                return 0;
            }
        }
        ok=1;
        strcpy(st,curent);
    }
    return 1;
}

void insereaza0(char sir[]) // pt nr negative
{
    int lg, i, j;
    lg=strlen(sir);
    for(i=0; i<=lg-1; i++)
        if(sir[i]=='-')
         if(sir[i-1]=='(' || i==0)
    {
     for(j=lg-1;j>=i;j--)
             sir[j+1]=sir[j];
     sir[i]='0';
    }
}

//fabs = modul

bool DifInf(float x)
{
    if(x>=2147483640) return 0;
    return 1;
}

float Logaritm(float x)
{
    if (x>EPSILON && DifInf(x))
        return log(x);
    else
        return INFINIT;
}

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return INFINIT;
}

float Inmultit(float x, float y)
{
    if ((fabs(x) < EPSILON) || (fabs(y) < EPSILON)) return 0;
        else if (DifInf(x) && DifInf(y)) return x*y;
            else return INFINIT;
}

float Putere(float x, float y)
{
    if (x==0) return 0;
    else if (y==0) return 1;
    else if (x==INFINIT || y==INFINIT) return INFINIT;
    else
        return pow(x,y);
}

float Egal(float x, float y)
{
    if (x==y) return 1;
    return 0;
}

float Diferit(float x, float y)
{
    if(x!=y) return 1;
    return 0;
}

float MaiMic(float x, float y)
{
    if (x<y) return 1;
    return 0;
}

bool MaiMare(float x, float y)
{
    if(x>y) return 1;
    return 0;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return (x+y);
    else return INFINIT;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return (x-y);
    else return INFINIT;
}

float Impartit(float x, float y)
{
    if (fabs(y)>EPSILON) return (x/y);
    else return INFINIT;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return INFINIT;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return INFINIT;
}

float Modul(float x)
{
    if (DifInf(x)) return fabs(x);
    else return INFINIT;
}

float Radical(float x)
{
    if (DifInf(x) && (x>EPSILON)) return sqrt(x);
    else return INFINIT;
}
int caz=0;
int calcule(operatorii op[MAXI], variabile var[MAXI], int &imposibil)
{
    double aux;
    // in functie de operator se calculeaza fiecare operatie stabilita mai sus
    /* algoritmul functioneaza astfel:
    - pentru + - * / se iau ultimele 2 valori din stiva si se calculeaza, iar rezultatul final este pus in vf stivei
    - pentru restul operatiilor se ia varful din stiva(ultima valoare), si varful este reactualizat cu noua valoare
    */
    if(op[top2].nume[0]=='+')
    {
        aux=Plus(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='-')
    {
          aux=Minus(var[top1-1].valoare,var[top1].valoare);
          top1--;
          var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='*')
    {
        aux=Inmultit(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='/')
    {
         if(var[top1].valoare==0)
        {
            imposibil=1; caz=1;
            cout<<"Impartirea se face la 0, este caz de nedeterminare"<<'\n';
        }
        else
        {
            aux=Impartit(var[top1-1].valoare,var[top1].valoare);
            top1--;
            var[top1].valoare=aux;
        }
    }
    if(op[top2].nume[0]=='^')
    {
        if(var[top1-1].valoare==0 && var[top1].valoare==0)
        {
            imposibil=1; caz=2;
            cout<<"S-a ajuns la cazul 0 la puterea 0, este caz de nedeterminare"<<'\n';
        }
        else{
            aux=Putere(var[top1-1].valoare,var[top1].valoare);
            top1--;
            var[top1].valoare=aux;
        }
    }
    if(op[top2].nume[0]=='#')
    {
        aux=Diferit(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='=')
    {
        aux=Egal(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='<')
    {
        aux=MaiMic(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(op[top2].nume[0]=='>')
    {
        aux=MaiMare(var[top1-1].valoare,var[top1].valoare);
        top1--;
        var[top1].valoare=aux;
    }
    if(strcmp(op[top2].nume,"cos")==0)
    {
        aux=Cosinus(var[top1].valoare);
        var[top1].valoare=aux;
    }
    if(strcmp(op[top2].nume,"sin")==0)
    {
        aux=Sinus(var[top1].valoare);
        var[top1].valoare=aux;
    }
    if(strcmp(op[top2].nume,"ln")==0)
    {
        if(var[top1].valoare<=0)
        {
            imposibil=1; caz=3;
            cout<<"S-a ajuns la logaritm dintr-un numar negativ sau egal cu 0, este caz de nedeterminare"<<'\n';
        }
        else
           {
               aux=Logaritm(var[top1].valoare);
               var[top1].valoare=aux;
           }
    }
    if(strcmp(op[top2].nume,"exp")==0)
    {
        aux=Exponential(var[top1].valoare);
        var[top1].valoare=aux;
    }
    if(strcmp(op[top2].nume,"abs")==0)
    {
        aux=Modul(var[top1].valoare);
        var[top1].valoare=aux;
    }
    if(strcmp(op[top2].nume,"sqrt")==0)
    {
        if(var[top1].valoare<0)
        {
            imposibil=1; caz=4;
            cout<<"S-a ajuns la radical dintr-un numar negativ, este caz de nedeterminare"<<'\n';
        }
        else
            {
                aux=Radical(var[top1].valoare);
                var[top1].valoare=aux;
            }
    }
    return 0;
}

void rezolva(operatorii op[MAXI], variabile var[MAXI], int i, int &imposibil)
{
    if(strcmp(operatori[i].nume,")")!=0)
    {
        while(op[top2].prioritate>=operatori[i].prioritate && top2>=0)
        {
            calcule(op,var,imposibil);
            if(imposibil) return;
            top2--;
        }
        strcpy(op[++top2].nume,operatori[i].nume);
        op[top2].prioritate=operatori[i].prioritate;
    }
    else
    {
        while(op[top2].nume[0]!='(')
        {
            calcule(op,var,imposibil);
            if(imposibil) return;
            top2--;
        }
        top2--;
    }
}

void citeste_variabile(char eq[200], char lang[2])
{
    settextjustify(0, 2);
    int y=0,i=0;
    char inp[100]="";
    readimagefile("dot.jpg", 10, 10, 100, 400);
    if(strcmp(lang,"EN"))
        outtextxy(10, 10, "Nr variabile:");
    else
        outtextxy(10, 10, "Variable count:");
    //Numarul de variabile
    while(inp[strlen(inp)-1]!=13){
        inp[strlen(inp)]=getch();
        if(inp[strlen(inp)-1]==8){
            inp[strlen(inp)-1]=0;
            inp[strlen(inp)-1]=0;
        }else if(inp[strlen(inp)-1]==27){inp[strlen(inp)-1]=0; return;}
        readimagefile("dot.jpg", 10, 10, 300, 400);
        outtextxy(10, 10, inp);
    }inp[strlen(inp)-1]=0;
    nrVar=atoi(inp);
    int j=1;
    for(i=0;i<nrVar;i++){
        while(strlen(inp))inp[strlen(inp)-1]=0;
        readimagefile("dot.jpg", 10, 30*i+40, 300, 40*i+70);
        if(strcmp(lang,"RO"))
            outtextxy(10, 30*i+40, "variable=value");
        else
            outtextxy(10, 30*i+40, "variabila=valoare");
        while(inp[strlen(inp)-1]!=13){
            inp[strlen(inp)]=getch();
            if(inp[strlen(inp)-1]==8){
                inp[strlen(inp)-1]=0;
                inp[strlen(inp)-1]=0;
            }else if(inp[strlen(inp)-1]==27){inp[strlen(inp)-1]=0; return;}
            readimagefile("dot.jpg", 10, 30*i+40, 300, 40*i+70);
            outtextxy(10, 30*i+40, inp);
        }inp[strlen(inp)-1]=0;
        if(strchr(inp,'=')!=NULL){
            *strchr(inp,'=')=0;
            strcpy(var[j].nume,inp);var[j].valoare=myatof(inp+strlen(inp)+1);
            cout<<var[j].nume<<"->"<<var[j].valoare<<"\n";j+=1;
            }
        else i-=1;
        //cout<<eq<<"\n";
    }

    settextjustify(1, 2);

    /*
    int i;
    cout<<"Numarul de variabile: ";
        cin>>nrVar;
        if(nrVar!=0) // daca exista variabile se vor citi valorile pentru fiecare de la tastatura
            {
                cout<<'\n'<<"Scrie valoarea fiecarei variabile, ca in exemplul dat"<<'\n';
                cout<<"EXEMPLU: var 10 ( variabila 'SPATIU' valoarea variabilei)"<<'\n';
            }
        for(i=1; i<=nrVar; i++)
            {
                cin>>var[i].nume>>var[i].valoare;
            }
            */
}
void spatiu(char expresie[],int &lg) // se adauga spatii
{
    int i, j, contor=0, k=0, kvar=0;
    char aux[MAXI];
    expresie[lg++]=')'; // expresiei i se va adăuga încă o paranteză )
        for(i=0; i<=lg-1; i++)
        {
            //verific daca este operator
            if(expresie[i]!=' ' && !(expresie[i]>='0' && expresie[i]<='9'))
                aux[contor++]=expresie[i];
            else if((expresie[i]>='0' && expresie[i]<='9') && contor!=0)
                aux[contor++]=expresie[i];
            for(j=0; j<NROPERATORI && k==0; j++)
                if(strcmp(aux,operatori[j].nume)==0) k=1;
            if(k!=0) // se adauga spatii intre operatori
            {
                if(i-contor>=0 && expresie[i-contor]!=' ')
                {
                    for(j=lg-1; j>=i-contor+1; j--)
                        expresie[j+1]=expresie[j];
                    expresie[i-contor+1]=' ';
                    lg++;
                }
                for(j=lg-1; j>=i+1; j--)
                    expresie[j+1]=expresie[j];
                expresie[i+1]=' ';
                lg++;
                resetare(aux,MAXI);
                contor=0;
                k=0;
            }
            else
            {
                kvar=0;
                for(j=1; j<=nrVar; j++)
                    {
                    if(strcmp(aux,var[j].nume)==0) // daca este variabila
                        k=1;
                    else
                      {
                        aux[contor++]=expresie[i+1];
                        if(strstr(var[j].nume,aux)!=NULL && strcmp(strstr(var[j].nume,aux),var[j].nume)==0)
                         kvar=1;
                        aux[contor-1]=0; contor--;
                      }
                    }
                if(k!=0 && kvar==0)
                {
                    k=0;
                    if(i-contor>=0 && expresie[i-contor]!=' ')
                    {
                        for(j=lg-1; j>=i-contor+1; j--)
                            expresie[j+1]=expresie[j];
                        expresie[i-contor+1]=' ';
                        lg++;
                    }
                    for(j=lg-1; j>=i+1; j--)
                        expresie[j+1]=expresie[j];
                    expresie[i+1]=' ';
                    lg++;
                    resetare(aux,MAXI);
                    contor=0;
                }
                k=0;
            }
        }
}

void creare_stive(char expresie[], operatorii stiva_Op[MAXI], variabile stiva_Opvar[MAXI],int &imposibil)
{
    int k=0, kvar=0, i, lg_numar, numar;
    strcpy(stiva_Op[++top2].nume,"("); // se adauga '(' in stiva de operatori
    stiva_Op[top2].prioritate=0;
    p=strtok(expresie," "); // se considera  primul element
     while(p)
       {
            k=0;
            for(i=0; i<NROPERATORI && k==0; i++)
                if(strcmp(operatori[i].nume,p)==0)
                          {
                             k=1; // daca este operator
                             indice=i;
                          }
            if(k!=0)
                {
                    if(strcmp(p,"(")==0)
                    {
                        strcpy(stiva_Op[++top2].nume,p);
                        stiva_Op[top2].prioritate=0;
                    }
                    else if(operatori[indice].prioritate>stiva_Op[top2].prioritate && strcmp(operatori[indice].nume,")")!=0)
                    { /*se pun în stiva operatorilor, pe rând, operatorii intâlniţi,
                        doar dacă în vârful stivei Opnu este un operator de prioritate mai mare sau egală*/
                        strcpy(stiva_Op[++top2].nume,operatori[indice].nume);
                        stiva_Op[top2].prioritate=operatori[indice].prioritate;
                    }
                    else if(operatori[indice].prioritate<=stiva_Op[top2].prioritate && strcmp(operatori[indice].nume,")")!=0)
                        /*în caz contrar, se scot operatorul din vârful stivei şi cei doi operanzi din vârful stivei operanzilor,
                         punându-se în stiva operanzilor rezultatul obţinut prin aplicarea operatorului asupra celor doi operanzi*/
                        rezolva(stiva_Op,stiva_Opvar,indice,imposibil);
                    else if(strcmp(operatori[indice].nume,")")==0)
                        rezolva(stiva_Op,stiva_Opvar,indice,imposibil);
                    if(imposibil) break; // daca este caz imposibil, calculul nu continua
                }
                else
                {
                    kvar=0;
                    for(i=1; i<=nrVar && kvar==0; i++)
                        if(strcmp(var[i].nume,p)==0)
                            {
                                kvar=1;
                                indice=i;
                            }
                    if(kvar!=0) stiva_Opvar[++top1].valoare=var[indice].valoare;
                    else
                    { // se face transformarea din char in int a numerelor din expresie
                        lg_numar=strlen(p);
                        numar=0;
                        for(i=0; i<=lg_numar-1; i++)
                            numar=numar*10+p[i]-'0';
                        stiva_Opvar[++top1].valoare=numar;
                    }
                }
                p=strtok(NULL," ");
            }
}


int VALID_ECRAN=1,imposibil=0;

float calc(char equation[200], char lang[2])
{
    char expresie[200]="",aux[MAXI]="", expresie2[MAXI]="";

    int paranteze=0, valid=0, lg, i=0, j=0, ok=1;
    top1=-1; top2=-1; indice=0;
    for(int i=0;i<200;i++) expresie[i]=equation[i];//metoda aceasta simpla evita erori de copiere si sterge orice reziduu al $expresie
    format(expresie);
    initializare_operatori();
    insereaza0(expresie);
    lg=strlen(expresie);
    paranteze=verif_paranteze(expresie); //se verifica daca parantezarea este corect facuta
    if(paranteze == 0){
             //daca nu este corecta, verificarea se opreste aici
             }
    else {
        cout<<'\n'<<" Expresia a fost parantezata corect!"<<'\n'<<'\n';
        spatiu(expresie,lg);
        strcpy(expresie2,expresie);
        valid=verif_expresie(expresie2,p,nrVar);
        if(valid==0)
            {
                cout<<"!Expresia nu este scrisa corect!"<<'\n'; // APARE PE ECRAN
                VALID_ECRAN=0;
            }
        else
        {
            cout<<"Expresia este scrisa corect!"<<'\n';
            cout<<"Se calculeaza expresia..."<<'\n'<<'\n';
            creare_stive(expresie,stiva_Op,stiva_Opvar,imposibil);
            if(imposibil==0)
                {
                    cout<<"Valoarea expresiei este: "<<stiva_Opvar[0].valoare;
                    return stiva_Opvar[0].valoare;
                }
            else
                {
                    cout<<"Nu se poate calcula"; // varianta imposibila
                    /*if (strcmp(lang,"RO")) outtextxy(500, 60, "NU SE POATE CALCULA");
                    else outtextxy(500, 60, "CANNOT COMPUTE");*/
                }
        }
    return 0;
}}



#endif // CALC_H_INCLUDED
