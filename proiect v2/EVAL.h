#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "TREE.H"
#include "CALC.H"

//Cocheor&Burghelea

int interbutton(int x, int y){
    if (y<400) return -1;
    if (y>400){
             if(x<250)return 1;
        else if(x<500)return 2;
        else if(x<750)return 3;
        else{if(y<500)return 4;
                 else return 5;}
    }
    return 0;
}

int color=7;
void main_program(char lang[2])
{
    char inp[200]="",rez[200]="";
    float val;
    bool inputMode=true;
    setactivepage(0);
    if(lang[0]=='E')
        readimagefile("appEN.jpg", 0, 0, 1000, 620);
    else
        readimagefile("appRO.jpg", 0, 0, 1000, 620);
    setvisualpage(0);
    setbkcolor(15); //BG color

    setcolor(0);

    settextstyle(8, HORIZ_DIR, 3);
    settextjustify(1, 2);
    if(lang[0]=='R')outtextxy(500, 10, "MOD TASTATURA");
    if(lang[0]=='E')outtextxy(500, 10, "KEYBOARD MODE");
    while(true){
        if(inputMode){
            inp[strlen(inp)]=getch();
        }
        else{
            if (ismouseclick(WM_LBUTTONDOWN)){ //PT MOUSE MODE
            clearmouseclick(WM_LBUTTONDOWN);
            if(interbutton(mousex(), mousey())==1){
                outtextxy(500, 30, inp);
                char expresie[200];strcpy(expresie,inp);
                val = calc(expresie,lang);

                int paranteze=verif_paranteze(expresie);
                int valid=verif_expresie(expresie,p,nrVar);

                if(paranteze==0){
                    cout<<"expresia nu a fost parantezata corect!"<<'\n';
                    settextjustify(1, 2);
                    if (strcmp(lang,"EN")) {
                            outtextxy(500, 60, "EROARE");
                            outtextxy(500,100, "Expresia nu a fost parantezata corect!");
                            char ic[3];char v[100];//pt pastrarea pozitiei
                            myitoa(i_paranteze,ic);
                            if(caz_paranteze==1)
                            {
                                strcpy(v,"Paranteza este inchisa la pozitia ");
                                strcat(v,ic);
                                outtextxy(500,200, v);
                                strcpy(v," inainte sa apara paranteza deschisa");
                                outtextxy(500,250, v);
                            }
                            else if(caz_paranteze==2)
                            {
                                strcpy(v,"Nu exista termen intre parantezele de pe pozitiile ");
                                strcat(v,ic);strcat(v," si ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==3)
                            {
                                strcpy(v,"Nu exista operator intre parantezele de pe pozitiile ");
                                strcat(v,ic);strcat(v," si ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==4)
                            {
                                strcpy(v,"Paranteza trebuie inchisa pe pozitia ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                    }
                    else {
                            outtextxy(500, 60, "ERROR");
                            outtextxy(500,100, "The expression has incorrect parantheses");
                            char ic[3];char v[100];//pt pastrarea pozitiei
                            myitoa(i_paranteze,ic);
                            if(caz_paranteze==1)
                            {
                                strcpy(v,"The mistake is at this position: ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==2)
                            {
                                strcpy(v,"There is no variable between paranthesis from position ");
                                strcat(v,ic);strcat(v," and ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==3)
                            {
                                strcpy(v,"There is not operator between paranthesis from position ");
                                strcat(v,ic);strcat(v," and ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==4)
                            {
                                strcpy(v,"There is a missing paranthesis at position ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                    }
            }
            else  { val = calc(expresie,lang);}
            valid=VALID_ECRAN;
            if(valid==0){
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "EROARE");
                        outtextxy(500, 100, "Expresia data este scrisa gresit");
                        char ic[3];char v[100],w[100];//pt pastrarea pozitiei
                        myitoa(i_eroare,ic);
                        if(eroare==1) {
                            strcpy(v,"Nu exista paranteza deschisa dupa ");
                            strcat(v,err); //sin cos etc
                            strcat(v, " pe pozitia ");strcat(v,ic);
                            outtextxy(500, 200, v);
                            outtextxy(500,270,"Prioritate 1:          + -            ");
                            outtextxy(500,300,"Prioritate 2:          * /            ");
                            outtextxy(500,330,"Prioritate 3:           ^             ");
                            outtextxy(500,360,"Prioritate 4:        # = < >          ");
                            outtextxy(500,390,"Prioritate 5: cos sin ln exp abs sqrt ");

                        }
                        if(eroare==2)
                        {
                            strcpy(v,"Nu exista un termen sau o functie de prioritate 5 in stanga");
                            outtextxy(500, 200, v);
                            strcpy(w,"si in dreapta unui operator ");//strcat(w,ic);
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Prioritate 1:          + -            ");
                            outtextxy(500,300,"Prioritate 2:          * /            ");
                            outtextxy(500,330,"Prioritate 3:           ^             ");
                            outtextxy(500,360,"Prioritate 4:        # = < >          ");
                            outtextxy(500,390,"Prioritate 5: cos sin ln exp abs sqrt ");
                        }
                        if(eroare==3)
                        {
                            strcpy(v,"Nu exista un operator cu prioritatea de la 1 la 4");
                            outtextxy(500, 200, v);
                            strcpy(w,"intre doi termeni sau intre un termen si o paranteza deschisa");
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Prioritate 1:          + -            ");
                            outtextxy(500,300,"Prioritate 2:          * /            ");
                            outtextxy(500,330,"Prioritate 3:           ^             ");
                            outtextxy(500,360,"Prioritate 4:        # = < >          ");
                            outtextxy(500,390,"Prioritate 5: cos sin ln exp abs sqrt ");
                        }
                      }
                else {
                    outtextxy(500, 60, "ERROR");
                    outtextxy(500, 100, "The given expression is invalid");
                    char ic[3];char v[100],w[100];//pt pastrarea pozitiei
                        myitoa(i_eroare,ic);
                        if(eroare==1) {
                            strcpy(v,"There is no open paranthesis after ");
                            strcat(v,err); //sin cos etc
                            strcat(v, " on position ");strcat(v,ic);
                            outtextxy(500, 200, v);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");

                        }
                        if(eroare==2)
                        {
                            strcpy(v,"There is no term or function with priority 5 to the left");
                            outtextxy(500, 200, v);
                            strcpy(w,"and right of an operator ");//strcat(w,ic);
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");
                        }
                        if(eroare==3)
                        {
                            strcpy(v,"There is no 1 to 4 priority operator between");
                            outtextxy(500, 200, v);
                            strcpy(w,"two terms or between a term and an open parenthesis");
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");
                        }
                }
            }
            if(val<=INFINIT && paranteze==1 && valid==1 && imposibil==0){
                DrawTree(inp,lang,color);
                myitoa(val,rez);
                outtextxy(500, 60, rez);
                }
            else if(imposibil==1 && paranteze==1 && valid==1)
            {
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "NU SE POATE CALCULA");
                        outtextxy(500, 100, "Expresia data contine un caz de nedeterminare");
                        if(caz==1) outtextxy(500, 200, "Impartirea se face la 0, nu se poate calcula");
                        else if(caz==2) outtextxy(500,200, "Exista cazul 0 la puterea 0 ( 0^0 ), nu se poate calcula");
                             else if(caz==3) outtextxy(500,200, "Exista logaritm dintr-un numar negativ sau egal cu 0");
                                else if(caz==4) outtextxy(500,200, "Exista un radical dintr-un numar negativ, nu se poate calcula");
                      }
                else {
                    outtextxy(500, 60, "CAN'T COMPUTE");
                    outtextxy(500, 100, "The given expression has an undetermined case");
                    if(caz==1) outtextxy(500, 200, "A number can't be divided by 0");
                        else if(caz==2) outtextxy(500,200, "Cannot compute 0^0");
                             else if(caz==3) outtextxy(500,200, "Cannot compute a logarithm from a number less than 0");
                                else if(caz==4) outtextxy(500,200, "Cannot compute square root from a negative number");
                }
            }
            else if(val>=INFINIT && paranteze==1 && valid==1 && imposibil==0)
            {
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "REZULTAT NEDEFINIT");
                        outtextxy(500, 100, "INFINIT");
                      }
                else {
                    outtextxy(500, 60, "INDEFINITE RESULT");
                    outtextxy(500, 100, "INFINITY");
                }
            }
            }
            if(interbutton(mousex(), mousey())==2)
                {
                    ifstream fin("read_formula.in");
                    fin>>inp;color=5;
                }
            if(interbutton(mousex(), mousey())==3)
                {
                    DrawTree(inp,lang,color);
                }
            if(interbutton(mousex(), mousey())==4)
                {
                    color-=1;
                    while(color<0)color+=16;
                    setbkcolor(color);
                    if(color<2)
                        setcolor(15);
                    else
                        setcolor(0);
                    //DrawTree(inp,lang,color);
                }
            if(interbutton(mousex(), mousey())==5)
                {
                    color+=1;
                    while(color>15)color-=16;
                    setbkcolor(color);
                    if(color<2)
                        setcolor(15);
                    else
                        setcolor(0);
                    //DrawTree(inp,lang,color);
                }
            if(interbutton(mousex(), mousey())==-1) {
                inputMode=!inputMode;
                readimagefile("dot.jpg", 0, 0, 1000, 30);
                if(lang[0]=='R')outtextxy(500, 10, "MOD TASTATURA");
                if(lang[0]=='E')outtextxy(500, 10, "KEYBOARD MODE");
                }
        }
        }

        readimagefile("dot.jpg", 0, 30, 1000, 60);

        if(inp[strlen(inp)-1]==8){
            inp[strlen(inp)-1]=0;
            inp[strlen(inp)-1]=0;
        }else if(inp[strlen(inp)-1]==13){ //cand este apasat ENTER
            inp[strlen(inp)-1]=0;
            outtextxy(500, 30, inp);
            char expresie[200];
            strcpy(expresie,inp);
            int paranteze=verif_paranteze(expresie);

            readimagefile("dot.jpg", 0, 50, 1000, 400);

            citeste_variabile(expresie,lang);

            if(paranteze==0){
                    cout<<"expresia nu a fost parantezata corect!"<<'\n';
                    settextjustify(1, 2);
                    if (strcmp(lang,"EN")) {
                            outtextxy(500, 60, "EROARE");
                            outtextxy(500,100, "Expresia nu a fost parantezata corect!");
                            char ic[3];char v[100];//pt pastrarea pozitiei
                            myitoa(i_paranteze,ic);
                            if(caz_paranteze==1)
                            {
                                strcpy(v,"Paranteza este inchisa la pozitia ");
                                strcat(v,ic);
                                outtextxy(500,200, v);
                                strcpy(v," inainte sa apara paranteza deschisa");
                                outtextxy(500,250, v);
                            }
                            else if(caz_paranteze==2)
                            {
                                strcpy(v,"Nu exista termen intre parantezele de pe pozitiile ");
                                strcat(v,ic);strcat(v," si ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==3)
                            {
                                strcpy(v,"Nu exista operator intre parantezele de pe pozitiile ");
                                strcat(v,ic);strcat(v," si ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==4)
                            {
                                strcpy(v,"Paranteza trebuie inchisa pe pozitia ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                    }
                    else {
                            outtextxy(500, 60, "ERROR");
                            outtextxy(500,100, "The expression has incorrect paranthesis");
                            char ic[3];char v[100];//pt pastrarea pozitiei
                            myitoa(i_paranteze,ic);
                            if(caz_paranteze==1)
                            {
                                strcpy(v,"The mistake is at this position: ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==2)
                            {
                                strcpy(v,"There is no variable between paranthesis from position ");
                                strcat(v,ic);strcat(v," and ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==3)
                            {
                                strcpy(v,"There is no operator between paranthesis from position ");
                                strcat(v,ic);strcat(v," and ");myitoa(i_paranteze+1,ic);strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                            else if(caz_paranteze==4)
                            {
                                strcpy(v,"There is a missing paranthesis at position ");strcat(v,ic);
                                outtextxy(500,200, v);
                            }
                    }
            }
            else  { val = calc(expresie,lang);}
            int valid=VALID_ECRAN;
            if(valid==0){
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "EROARE");
                        outtextxy(500, 100, "Expresia data este scrisa gresit");
                        char ic[3];char v[100],w[100];//pt pastrarea pozitiei
                        myitoa(i_eroare,ic);
                        if(eroare==1) {
                            strcpy(v,"Nu exista paranteza deschisa dupa ");
                            strcat(v,err); //sin cos etc
                            strcat(v, " pe pozitia ");strcat(v,ic);
                            outtextxy(500, 200, v);
                        }
                        if(eroare==2)
                        {
                            strcpy(v,"Nu exista un termen sau o functie de prioritate 5 in stanga");
                            outtextxy(500, 200, v);
                            strcpy(w,"si in dreapta unui operator ");//strcat(w,ic);
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Prioritate 1:          + -            ");
                            outtextxy(500,300,"Prioritate 2:          * /            ");
                            outtextxy(500,330,"Prioritate 3:           ^             ");
                            outtextxy(500,360,"Prioritate 4:        # = < >          ");
                            outtextxy(500,390,"Prioritate 5: cos sin ln exp abs sqrt ");
                        }
                        if(eroare==3)
                        {
                            strcpy(v,"Nu exista un operator cu prioritatea de la 1 la 4");
                            outtextxy(500, 200, v);
                            strcpy(w,"intre doi termeni sau intre un termen si o paranteza deschisa");
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Prioritate 1:          + -            ");
                            outtextxy(500,300,"Prioritate 2:          * /            ");
                            outtextxy(500,330,"Prioritate 3:           ^             ");
                            outtextxy(500,360,"Prioritate 4:        # = < >          ");
                            outtextxy(500,390,"Prioritate 5: cos sin ln exp abs sqrt ");
                        }
                      }
                else {
                    outtextxy(500, 60, "ERROR");
                    outtextxy(500, 100, "The given expression is invalid");
                    char ic[3];char v[100],w[100];//pt pastrarea pozitiei
                        myitoa(i_eroare,ic);
                        if(eroare==1) {
                            strcpy(v,"There is no open paranthesis after ");
                            strcat(v,err); //sin cos etc
                            strcat(v, " on position ");strcat(v,ic);
                            outtextxy(500, 200, v);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");

                        }
                        if(eroare==2)
                        {
                            strcpy(v,"There is no term or function with priority 5 to the left");
                            outtextxy(500, 200, v);
                            strcpy(w,"and right of an operator ");//strcat(w,ic);
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");
                        }
                        if(eroare==3)
                        {
                            strcpy(v,"There is no 1 to 4 priority operator between");
                            outtextxy(500, 200, v);
                            strcpy(w,"two terms or between a term and an open parenthesis");
                            outtextxy(500, 230, w);
                            outtextxy(500,270,"Priority 1:          + -            ");
                            outtextxy(500,300,"Priority 2:          * /            ");
                            outtextxy(500,330,"Priority 3:           ^             ");
                            outtextxy(500,360,"Priority 4:        # = < >          ");
                            outtextxy(500,390,"Priority 5: cos sin ln exp abs sqrt ");
                        }
                }
            }
            if(val<=INFINIT && paranteze==1 && valid==1 && imposibil==0){
                DrawTree(inp,lang,color);
                myitoa(val,rez);
                outtextxy(500, 60, rez);}
            else if(imposibil==1 && paranteze==1 && valid==1)
            {
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "NU SE POATE CALCULA");
                        outtextxy(500, 100, "Expresia data contine un caz de nedeterminare");
                        if(caz==1) outtextxy(500, 200, "Impartirea se face la 0, nu se poate calcula");
                        else if(caz==2) outtextxy(500,200, "Exista cazul 0 la puterea 0 ( 0^0 ), nu se poate calcula");
                             else if(caz==3) outtextxy(500,200, "Exista logaritm dintr-un numar negativ sau egal cu 0");
                                else if(caz==4) outtextxy(500,200, "Exista un radical dintr-un numar negativ, nu se poate calcula");
                      }
                else {
                    outtextxy(500, 60, "CAN'T COMPUTE");
                    outtextxy(500, 100, "The given expression has an undetermined case");
                    if(caz==1) outtextxy(500, 200, "A number can't be divided by 0");
                        else if(caz==2) outtextxy(500,200, "Cannot compute 0^0");
                             else if(caz==3) outtextxy(500,200, "Cannot compute a logarithm from a number less than 0");
                                else if(caz==4) outtextxy(500,200, "Cannot compute square root from a negative number");
                }
            }
            else if(val>=INFINIT && paranteze==1 && valid==1 && imposibil==0)
            {
                settextjustify(1, 2);
                if (strcmp(lang,"EN")) {
                        outtextxy(500, 60, "REZULTAT NEDEFINIT");
                        outtextxy(500, 100, "INFINIT");
                      }
                else {
                    outtextxy(500, 60, "INDEFINITE RESULT");
                    outtextxy(500, 100, "INFINITY");
                }
            }
            settextjustify(1, 2);
        }
        else if(inp[strlen(inp)-1]==27){
            if(inputMode)inputMode=false;
            else return;}
        else if(inp[strlen(inp)-1]==9){
            inp[strlen(inp)-1]=0;
            inputMode=!inputMode;
            readimagefile("dot.jpg", 0, 0, 1000, 30);
            if(lang[0]=='R')outtextxy(500, 10, "  MOD MOUSE  ");
            if(lang[0]=='E')outtextxy(500, 10, "  MOUSE MODE  ");
            }
        outtextxy(500, 30, inp);
    }
}


#endif // EVAL_H_INCLUDED
