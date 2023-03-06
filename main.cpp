#include <iostream>
#include <windows.h>
#include <conio.h>
#include "header.h"

using std::fstream;
using std::string;
using std::cout;
using std::exit;
using std::endl;
using std::cin;
using std::ios;


int main() {
    int rozmiar = 0;
    int wybor = 0;
    int kolor = 0;
    char znak;
    int x = 0;
    int y = 0;
    unsigned char strzalka;
    
    menu(wybor);
    rozmiar_figury(rozmiar);
    wybor_koloru(kolor);
    wybor_znaku(znak);
	HideCursor();
    rysowanie(znak,x,y,rozmiar);

    do 
	{
		strzalka = _getch();
		ruszanie(x, y, rozmiar, znak, strzalka);
	} while (strzalka != 27); // kod ascii klawisza ESCAPE 

	_getch();
    return 0;
}
