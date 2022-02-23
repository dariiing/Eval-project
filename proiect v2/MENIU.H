#ifndef MENIU_H_INCLUDED
#define MENIU_H_INCLUDED
#include "EVAL.H"

//Cocheor&Burghelea

void loadDefaultMenu(char * lang) // meniul de start
{
    char v[50];strcpy(v,"b_");strcat(v,lang);strcat(v,".jpg");
    readimagefile(v, 0, 0, 1000, 620); // meniu fundal
    readimagefile("start_button.jpg", 402, 300, 600, 400); // start button
    readimagefile("about_buttonRO.jpg", 402, 400, 600, 500); // about button
    strcpy(v,"rules_");strcat(v,lang);strcat(v,".jpg"); // rules button
    readimagefile(v, 402, 500, 600, 600);
}

void loadDefaultAbout(char * lang) // about page
{
    char v[50];
    strcpy(v,"about");strcat(v,lang);strcat(v,".jpg");
    readimagefile(v, 0, 0, 1000, 620); // despre proiect fundal
    strcpy(v,"back_button");strcat(v,lang);strcat(v,".jpg"); // back button
    readimagefile(v,  800, 500, 980, 600);
}
void loadDefaultRules(char * lang) // rules page
{
    char v[50];
    strcpy(v,"reguli_");strcat(v,lang);strcat(v,".jpg");
    readimagefile(v, 0, 0, 1000, 620); // reguli fundal
    strcpy(v,"back_button");strcat(v,lang);strcat(v,".jpg"); // back button
    readimagefile(v,  800, 500, 980, 600);
}

int MenuClick(int x, int y)
{
    if (x>402 && x<600) {
        if (y>300 && y<400) return 1; // start
        if (y>400 && y<500) return 2; // about
        if(y>500 && y<600) return 4; // rules
    }
    else if(x>800&&x<980&&y>500&&y<600)
        return 3; //back
    return 0;
}

void menu_start(char * lang)
{
    char t[50];
    int Page=0;
    setactivepage(1);
    loadDefaultMenu(lang);
    setactivepage(2);
    loadDefaultAbout(lang);
    setactivepage(3);
    loadDefaultRules(lang);
    setactivepage(1);
    setvisualpage(1);
    while(true){
        if (ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            if(Page==0 && MenuClick(mousex(), mousey())==1){ //start
                Page=2;
                setactivepage(5);
                main_program(lang);
                setvisualpage(5);
            }
            if(Page==0 && MenuClick(mousex(), mousey())==2){ //about
                Page=1;
                setactivepage(2);
                setvisualpage(2);
            }
            if(Page==0 && MenuClick(mousex(), mousey())==4){ //rules
                Page=1;
                setactivepage(3);
                setvisualpage(3);
            }
            else if(Page==1 && MenuClick(mousex(), mousey())==3){ //back
                Page=0;
                setactivepage(1);
                setvisualpage(1);
            }

        }
        if(Page==1){
            //t is a temporary string used for selecting a language in text without requireing duplicate functions
            if(MenuClick(mousex(), mousey())==3){
                strcpy(t,"back_click");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 800, 500, 980, 600);}
            else {
                strcpy(t,"back_button");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 800, 500, 980, 600);}
        }
        else if(Page==0){
            if(MenuClick(mousex(), mousey())==1)
                 readimagefile("start_click.jpg", 402, 300, 600, 400);
            else readimagefile("start_button.jpg", 402, 300, 600, 400);
            if(MenuClick(mousex(), mousey())==2){
                strcpy(t,"about_click");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 402, 400, 600, 500);}
            else {
                strcpy(t,"about_button");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 402, 400, 600, 500);}
            if(MenuClick(mousex(), mousey())==4){
                strcpy(t,"rulesclick_");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 402, 500, 600, 600);}
            else {
                strcpy(t,"rules_");strcat(t,lang);strcat(t,".jpg");
                readimagefile(t, 402, 500, 600, 600);}
        }
    }
}

#endif
