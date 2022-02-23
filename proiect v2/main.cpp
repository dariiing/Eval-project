#include <iostream>
#include <math.h>
#include <graphics.h>
#include <string.h>
#include <fstream>

#define INFINIT 2147483640 //apx cel mai mare int posibil
#define EPSILON 0.0001

#include "MENIU.H"
#include "EVAL.H"
#include "meniu_principal.h"

using namespace std;

int main()
{
    int lang;
    lang=menu_principal();//Atribuirea executa programul care returneaza 1 pentru a reprezenta limba romana si 0 pentru limba enleza
    if(lang)
        main_program("RO");
    else
        main_program("EN");
    //getch();
    closegraph();
    return 0;
}
