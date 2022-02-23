#ifndef MENIU_PRINCIPAL_H_INCLUDED
#define MENIU_PRINCIPAL_H_INCLUDED

//Cocheor
void loadMENIU_PRINC()
{
    readimagefile("menu_limbi.jpg", 0, 0, 1000, 620);
}

int MenuClickP(int x, int y)
{
     if (x>0 && x<500) return 1;
    if (x>700 && x<1000) return 2;
    return 0;
}

int menu_principal()
{
    int Page=0;
    initwindow(1000, 620, "APP", 100, 100, true, true);
    setactivepage(1);
    loadMENIU_PRINC();
    setactivepage(1);
    setvisualpage(1);
     while(true){

        if (ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            if(Page==0 && MenuClickP(mousex(), mousey())==1){
                Page=1;
                setactivepage(2);
                menu_start("RO");
                setvisualpage(2);
                return 0;
            }
            else if(Page==0 && MenuClickP(mousex(), mousey())==2){
                Page=1;
                setactivepage(3);
                menu_start("EN");
                setvisualpage(3);
                return 1;
            }

        }
        if(Page==0){
         if(MenuClickP(mousex(), mousey())==1)
                 readimagefile("ales_rom.jpg", 0, 0, 1000, 620);
         if(MenuClickP(mousex(), mousey())==2)
                 readimagefile("ales_eng.jpg", 0, 0, 1000, 620);
         if(!MenuClickP(mousex(), mousey()))
         readimagefile("menu_limbi.jpg", 0, 0, 1000, 620);
        }
     }
}


#endif
