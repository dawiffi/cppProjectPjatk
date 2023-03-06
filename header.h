#include <iostream>
#include <windows.h>     // biblioteka umozliwiajaca operacje na oknie windowsowym

using std::fstream;
using std::string;
using std::cout;                
using std::exit;            // deklaracje pozwalajace na uzycie funkcji m.in. z biblioteki std, bez uzycia przedrostka std::
using std::endl;
using std::cin;
using std::ios;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // 

void rozmiar_figury(int&);
void wybor_znaku(char&);  
void HideCursor();
void gotoxy(int x,int y);                        // deklaracje funkcji, ktore pozniej sa uzywane w programie
void wybor_koloru(int&);
void menu(int&);
void rysowanie(char, int, int, int);
void ruszanie(int&, int&, int&, char, unsigned char);

void rozmiar_figury(int& rozmiar){ // wybor poczatkowego rozmiaru figury rysowanej przez nasz program
    cout << endl;
    cout << "__________________________" << endl;
    cout << "|                        |" << endl;
    cout << "|     WYBIERZ ROZMIAR    |" << endl;
    cout << "|         FIGURY         |" << endl;
    cout << "|   (zakres od 5 do 10)  |" << endl;
    cout << "|________________________|" << endl;
    cout << endl;
    cout << "Podaj rozmiar figury: " << endl; 
    cin >> rozmiar;                                        // pobranie rozmiaru od uzytkownika
    if (rozmiar >= 5 && rozmiar <=10) {                     // jesli wprowadzona przez uzytkownika wartosc jest wieksza/rowna 5 oraz mniejsza/rowna 10, jest ona poprawna
        cout << "Poprawnie wybrano rozmiar." << endl;
    } else {
        cout << "Wybrany rozmiar nie jest akceptowany. Zastosowano domyslne ustawienie [6]." << endl;         // w przeciwnym razie, wyswietla sie blad
        system("pause");                                                // "zapauzowanie" programu, wyswietla komunikat "Press any key to continue...", po nacisnieciu program zaczyna dalsza prace
        rozmiar = 6;                                                                                       // i rozmiar figury przybiera domyslna wartosc [6]
    }   

    system("cls");  // wyczyszczenie ekranu
}

void wybor_znaku(char& znak){ // wybor znaku ascii do rysowania naszej figury
    cout << endl;
    cout << "__________________________" << endl;
    cout << "|                        |" << endl;
    cout << "|     WPROWADZ ZNAK      |" << endl;
    cout << "|         ASCII          |" << endl;
    cout << "|    (domyslnie: * )     |" << endl;
    cout << "|________________________|" << endl;
    cout << endl;
    cin >> znak;                                        // pobranie znaku od uzytkownika
    if (znak >= 33 && znak <= 126) {                        // jesli wprowadzony znak znajduje sie w tablicy kodow ascii miedzy pozycja 33 (!) a pozycja 126 (~), wybrano poprawnie [33-126 to symbole, litery i liczby]
        cout << "Poprawnie wybrano znak." << endl;
    } else {
        cout << "Wybrany znak nie jest akceptowany. Zastosowano domyslne ustawienie [*]." << endl;   // w przeciwnym razie, wyswietla sie blad
        system("pause");
        znak = '*';                                                                                    // i znak przybiera domyslna wartosc (*)
    }   
    system("cls");  // wyczyszczenie ekranu
}

void gotoxy(int x,int y)    // przeniesienie kursora w określone miejsce na oknie konsoli windows
{
	COORD c;
	c.X=x;                      // wspolrzedna x kursora
	c.Y=y;                      // wspolrzedna y kursora
	SetConsoleCursorPosition(h,c);
}

void HideCursor()           // ukrycie kursora w oknie konsoli windows
{
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo( h, &hCCI );
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo( h, &hCCI );
}

int wherex()             // zwrocenie aktualnej wspolrzednej x kursora z okna konsoli windows
{   
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

int wherey()            // zwrocenie aktualnej wspolrzednej y kursora z okna konsoli windows
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

int maxsizex()      // zwrocenie maksymalnej 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwMaximumWindowSize.X;
}

int maxsizey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwMaximumWindowSize.Y;
}

void menu(int& wybor){                  // menu programu, sluzace do wyboru miedzy narysowaniem znaku a "dokumentacja"
    cout << endl;
    cout << "____________________________________________________________" << endl;
    cout << "|                                                          |" << endl;
    cout << "|                      WYBIERZ OPCJE:                      |" << endl;
    cout << "|           1.                                 2.          |" << endl;
    cout << "|                                                          |" << endl;
    cout << "|       RYSOWANIE                         DOKUMENTACJA     |" << endl;
    cout << "|     ZNAKIEM ASCII                                        |" << endl;
    cout << "|                                                   s29608 |" << endl;
    cout << "|__________________________________________________________|" << endl;
    cout << endl;
    cout << "---------->", cin >> wybor;   // podanie przez uzytkownika wybranej opcji
    if (wybor == 1){                // jesli podano opcje 1, wypisz informacje o tym
        cout << endl;
        cout << "Wybrano opcje 1: RYSOWANIE ZNAKIEM ASCII" << endl;
    }
    else if (wybor == 2){       // jesli podano opcje 2, wypisz informacje o "dokumentacji"
        cout << endl;
        cout << "Designed, programmed, compiled by DF 2023." << endl;   // informacje od tworcy ;)
        system("pause");
        exit(0);              // zakonczenie dzialania programu
    }
    else{
        cout << endl;
        cout << "____________________________________________________________" << endl;
        cout << "|                                                          |" << endl;
        cout << "|                                                          |" << endl;
        cout << "|               WYBRANO NIEWLASCIWA OPCJE!                 |" << endl;
        cout << "|                                                          |" << endl;
        cout << "|                URUCHOM PROGRAM PONOWNIE.                 |" << endl;
        cout << "|                                                          |" << endl;
        cout << "|                                                          |" << endl;
        cout << "|__________________________________________________________|" << endl;
        cout << endl;
        system("pause");
        exit(0);            // zakonczenie dzialania programu
    }
}

void wybor_koloru(int& kolor){              // wybor koloru dla rysowanego ksztaltu
    cout << endl;
    cout << "__________________________" << endl;
    cout << "|                        |" << endl;
    cout << "|      WYBIERZ KOLOR     |" << endl;
    cout << "|        KSZTALTU        |" << endl;
    cout << "|  (domyslnie: czerwony) |" << endl;
    cout << "|________________________|" << endl;
    cout << endl;
    cout << "1 = granatowy <----------" << endl;
    cout << "2 = zielony <------------" << endl;
    cout << "3 = niebieski <----------" << endl;
    cout << "4 = czerwony <-----------" << endl;    // wypisanie mozliwych opcji
    cout << "5 = fioletowy <----------" << endl;
    cout << "6 = zolty <--------------" << endl;
    cout << "7 = bialy <--------------" << endl;
    cin >> kolor;
    if (kolor == 1){
        SetConsoleTextAttribute(h, 1); // kolor granatowy
    }
    else if(kolor == 2){
        SetConsoleTextAttribute(h, 2); // kolor zielony
    }
    else if(kolor == 3){
        SetConsoleTextAttribute(h, 3); // kolor niebieski
    }
    else if(kolor == 4){
        SetConsoleTextAttribute(h, 4); // kolor czerwony
    }
    else if(kolor == 5){
        SetConsoleTextAttribute(h, 5); // kolor fioletowy
    }
    else if(kolor == 6){
        SetConsoleTextAttribute(h, 6); // kolor zolty
    }
    else if(kolor == 7){
        SetConsoleTextAttribute(h, 7); // kolor bialy
    }
    else{
        cout << "Wybrany numer koloru nie jest poprawny. Zastosowano domyslne ustawienie [czerwony]." << endl;   // w przeciwnym razie, wyswietla sie blad
        SetConsoleTextAttribute(h, 4); // kolor czerwony        przy wyborze liczby innej niz z zakresu 1-7, zostanie ustawiony domyslny kolor [czerwony]
        system("pause");
    }
}

void rysowanie(char znak, int x, int y, int rozmiar) {  // rysowanie ksztaltu na podstawie wprowadzonych przez uzytkownika danych dotyczacych jego rozmiaru, znaku uzytego do rysowania, koloru

int wysokosc_figury = rozmiar;  // wysokosc ksztaltu
int szerokosc_figury = rozmiar; // szerokosc ksztaltu

    for (int i = 0; i < wysokosc_figury; i++) {  // petla rysujaca lewe i prawe ramie ksztaltu
        gotoxy(x, y + i);                       // uzycie funkcji gotoxy() do przeniesienia kursora w określone miejsce, uzaleznione od podanego rozmiaru ksztaltu
        cout << znak;

        gotoxy(x + szerokosc_figury - 1, y + i);
        cout << znak;
    }

    for (int i = 1; i < (wysokosc_figury + 1) / 2; i++) {   // petla rysujaca srodkowa czesc ksztaltu
        gotoxy(x + i, y + wysokosc_figury - 1 - i);
        cout << znak;
        
        gotoxy(x + szerokosc_figury - 1 - i, y + wysokosc_figury - 1 - i);
        cout << znak;
    }
}

void ruszanie(int &x, int &y, int &rozmiar, char znak, unsigned char strzalka){ // ruszanie figura po ekranie, oraz dodatkowe funkcje
	if (strzalka == 135){
		strzalka = _getch();
        }
    if (strzalka == 32){ // spacja [kod ascii] - zmiana koloru na losowy, przy naciskaniu spacji
        srand((int)time(NULL));
        int j = 0;
        for (auto i=1; i<100; i++){
        j = rand() % 7 + 1;
		SetConsoleTextAttribute(h, j);
        }
	} 
    if (strzalka == 42){ // gwiazdka [kod ascii] - zmiana rozmiaru na losowy z przedzialu 5-15, przy naciskaniu *
        srand((int)time(NULL));
        int z = 0;
        for (auto k=1; k<100; k++){
        z = rand() % 15 + 5;
		rozmiar = z;
        }
	} 
    if (strzalka == 72){ // strzalka w gore [kod ascii] - ruch figura w gore
	    y -= 1;

		if (y <= -1){ 
            y = 0; 
        } 
    } 
    if (strzalka == 80){ // strzalka w dol [kod ascii] - ruch figura w dol
		y += 1;

		if (y < wherey() - rozmiar){
            y = wherey() - rozmiar; 
            } 
	}  
    if (strzalka == 77){ // strzalka w prawo [kod ascii] - ruch figura w prawo
		x += 1;

		if (x >= maxsizex() - (rozmiar * 2)){ 
            x = maxsizex() - (rozmiar * 2); 
        } 
	}  
    if (strzalka == 75){ // strzalka w lewo [kod ascii] - ruch figura w lewo
		x -= 1;

		if (x <= -1){ 
            x = 0; 
        } 
	}  
    if (strzalka == 45){ // minus [kod ascii] - pomniejszanie figury
		rozmiar -= 1; 
		if (x <= -1) {
            x = 0; 
        }

		if (y <= -1){ 
            y = 0; 
        }
	}  
    if (strzalka == 43){ // plus [kod ascii] - powiekszanie figury
		if (rozmiar <= (maxsizex()/2)){ 
            rozmiar += 1; 
        }

		if (x >= maxsizex() - (rozmiar * 2)){  // powiekszanie do prawej sciany, przy dotknieciu koniec
            rozmiar -= 1; 
        } 

		if (y < wherey() - rozmiar){  // powiekszanie do dolnej sciany, przy dotknieciu koniec
            rozmiar -= 1; 
        } 
	} 
	system("cls"); // wyczyszczenie ekranu
	gotoxy(0, 0);

	rysowanie(znak, x, y, rozmiar);
}