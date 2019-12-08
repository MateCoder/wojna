#include <iostream>
#include <cstdlib>
#include<ctime>
#define WIELKOSC_TALII 52
#define LICZBA_KOLOROW 4
#define LICZBA_KART_W_KOLORZE 13
#define KARTA_POCZATKOWA 0   //wybierajac talie od 2 wybierz 0, {3->1, 4->2, 5->3, 6->4, 7->5, 8->6, 9->7, 10->8, J->9 ...}
#define A 0
#define B 1
using namespace std;

struct karta {
	int kolor;
	int waga;
};

struct talia_gracza {
	talia_gracza* nastepny;
	talia_gracza* poprzedni;
	talia_gracza* pierwszy;
	talia_gracza* ostatni;
	karta konkretna_karta;
	int licznik;
};

void stworz_talie(karta cala_talia[]) {
	int pomocnicza_wagi;
	pomocnicza_wagi = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = KARTA_POCZATKOWA; i < LICZBA_KART_W_KOLORZE; i++) {
		for (j = KARTA_POCZATKOWA; j < LICZBA_KART_W_KOLORZE; j++) {
			cala_talia[pomocnicza_wagi].kolor = i;
			cala_talia[pomocnicza_wagi].waga = j;
			pomocnicza_wagi++;
		}
	}
}
void potasuj(karta cala_talia[]) {
	srand(time(NULL));

	int j;
	struct karta pomocnicza;
	for (int i = 0; i < WIELKOSC_TALII; i++) {//ten for tasuje talie
		j = rand() % WIELKOSC_TALII;//MUSZE ZAMIENIC TO ZIARNO ZEBY BYLO ROZNE
		pomocnicza = cala_talia[i];
		cala_talia[i] = cala_talia[j];
		cala_talia[j] = pomocnicza;
	}
}

void rozdaj_karty(karta cala_talia[], talia_gracza talia_gracza1[], talia_gracza talia_gracza2[], int& wielkosc_talii1, int& wielkosc_talii2) {
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < WIELKOSC_TALII; i++) {
		if (i % 2 == 0) {//wykorzystuje parzystosc i nieparzystosc indeksu aby rozdawac karty graczom naprzemiennie
			talia_gracza1[j].nastepny = talia_gracza1[j + 1].nastepny;
			talia_gracza1[j].poprzedni = talia_gracza1[j - 1].poprzedni;
			talia_gracza1[j].pierwszy = talia_gracza1[0].pierwszy;
			talia_gracza1[j].ostatni = talia_gracza1[wielkosc_talii1].ostatni;
			talia_gracza1[j].konkretna_karta = cala_talia[i];
			j++;

		}
		else {
			talia_gracza2[k].nastepny = talia_gracza2[k + 1].nastepny;
			talia_gracza2[k].poprzedni = talia_gracza2[k - 1].poprzedni;
			talia_gracza2[k].pierwszy = talia_gracza2[0].pierwszy;
			talia_gracza2[k].ostatni = talia_gracza2[wielkosc_talii2].ostatni;
			talia_gracza2[k].konkretna_karta = cala_talia[i];
			k++;
		}
	}
}

//Funkcja przepisz_talie powoduje to ze usuwa karty z wierzchu talli przez przypisanie im wartosci spoza dziedziny talii, a nastepnie poprawnie nadaje indeksy dla pozostalych kart
void przepisz_talie(talia_gracza talia_do_przepisania[], int liczba_kart_do_usuniecia) {
	int i = 0;
	while (talia_do_przepisania[i].konkretna_karta.waga == 80)//80 poniewaz jest to liczba poza zakresem talii, ktora przypisuje kartom ktore chce usunac
		i++;
	for (int j = 0; j < liczba_kart_do_usuniecia; j++)
		talia_do_przepisania[j] = talia_do_przepisania[j + i];
	//cout << endl << "przepisuje" << endl;
}

//Funkcja ta przepisuje 1 karte wygranego na nowe przedostanie miejsce, przegranego na ostatnie, a 1 miejsce wygranego zapisuje jako 80 aby usunac ta karte z pocztku
void dodaj_karte(talia_gracza talia_wygranego[], talia_gracza talia_przegranego[], int& licznik_kart) {
	licznik_kart++;// powiekszam o 1 a nie 2 bo pierwszy element po prostu jest przeniesiony na koniec
	talia_wygranego[licznik_kart - 1] = talia_wygranego[0];
	talia_wygranego[0].konkretna_karta.waga = 80;
	talia_wygranego[licznik_kart] = talia_przegranego[0];
	przepisz_talie(talia_wygranego, licznik_kart);//usuwam 1 karte z pocztku talii
}

//Wiedzac ile jest kart usunietych zapisuje tyle miejsc jako 80 aby je usunac w funkcji przepisz
void usun_karte(talia_gracza talia_przegranego[], int& licznik_kart) {
	licznik_kart--;//traci 1 karte
	talia_przegranego[0].konkretna_karta.waga = 80;//nadpisuje stracona karte na 80 zeby ja usunac
	przepisz_talie(talia_przegranego, licznik_kart);
}

void dodaj_karty_z_wojnyA(talia_gracza talia_wygranego[], talia_gracza talia_przegranego[], int& liczba_kart_w_talii, int odjete_karty) {
	for (int i = 0; i < odjete_karty; i++)
	{
		talia_wygranego[liczba_kart_w_talii] = talia_wygranego[i];
		talia_wygranego[0].konkretna_karta.waga = 80;
	}
	przepisz_talie(talia_wygranego, odjete_karty);//usuwam 1 karte
	for (int i = 0; i < odjete_karty; i++)
	{
		liczba_kart_w_talii++;
		talia_wygranego[liczba_kart_w_talii] = talia_przegranego[i];
	}
	//przepisz_talie(talia_wygranego, odjete_karty);//!!!!!!!!!!!!!mozliwa ze bez 1      usuwam te 80 z przodu i przepisuje talie
}
void odejmij_karty_z_wojny(talia_gracza tablica_przegranego[], int liczba_odjetych_kart, int& liczba_kart_w_talii) {
	for (int i = 0; i < liczba_odjetych_kart; i++) {
		tablica_przegranego[i].konkretna_karta.waga = 80;//przygotowuje karty przegranego do usuniecia
	}
	liczba_kart_w_talii -= liczba_odjetych_kart;
	przepisz_talie(tablica_przegranego, liczba_odjetych_kart);//usuwam
}
void dodaj_karty_z_wojnyB(talia_gracza talia_wygranego[], talia_gracza talia_przegranego[], int& liczba_kart_w_talii, int odjete_karty) {
	if (odjete_karty % 4 == 0) {//sprawdzam czy jest to wariant gdzie ten co daje karty przeciwnikowi od razu dawal mu po 2 czy na poczatku 1
		talia_wygranego[odjete_karty] = talia_wygranego[0];
		for (int i = 0; i < odjete_karty; i++) {
			talia_wygranego[i] = talia_przegranego[i];
			liczba_kart_w_talii++;
		}
	}
	else {
		talia_wygranego[odjete_karty] = talia_wygranego[0];
		talia_wygranego[odjete_karty + 1] = talia_wygranego[1];
		for (int i = 0; i < odjete_karty; i++) {
			talia_wygranego[i] = talia_przegranego[i];
			liczba_kart_w_talii++;
		}
	}
}
void wojnaA(talia_gracza talia_gracza1[], talia_gracza talia_gracza2[], int karty_do_przepisania, int& wielkosc_talii_1, int& wielkosc_talii_2, int& liczba_ruchow) {
	if (wielkosc_talii_1 <= 2) {
		cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 2   !!!!!" << endl << "poniewaz gracz 1 ma za malo kart aby rozpoczac wojne" << endl;
		exit(0);
	}

	else if (wielkosc_talii_2 <= 2) {
		cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 1   !!!!!" << endl << "poniewaz gracz 2 ma za malo kart aby rozpoczac wojne" << endl;
		exit(0);
	}
	liczba_ruchow++;
	cout << "waga 1:" << talia_gracza1[karty_do_przepisania + 2].konkretna_karta.waga << ", waga 2:" << talia_gracza2[karty_do_przepisania + 2].konkretna_karta.waga << endl;
	karty_do_przepisania = karty_do_przepisania + 2;
	if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga > talia_gracza2[karty_do_przepisania].konkretna_karta.waga) {
		cout << "wojne wygral 1" << endl;
		dodaj_karty_z_wojnyA(talia_gracza1, talia_gracza2, wielkosc_talii_1, karty_do_przepisania + 1);
		odejmij_karty_z_wojny(talia_gracza2, karty_do_przepisania + 1, wielkosc_talii_2);

	}
	else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga < talia_gracza2[karty_do_przepisania].konkretna_karta.waga) {
		cout << "wojne wygral 2" << endl;
		dodaj_karty_z_wojnyA(talia_gracza2, talia_gracza1, wielkosc_talii_2, karty_do_przepisania + 1);
		odejmij_karty_z_wojny(talia_gracza1, karty_do_przepisania + 1, wielkosc_talii_1);

	}

	else {
		cout << "znowu wojna" << endl;
		cout << "waga 1:" << talia_gracza1[karty_do_przepisania].konkretna_karta.waga << ", waga 2:" << talia_gracza2[karty_do_przepisania].konkretna_karta.waga << endl;
		wojnaA(talia_gracza1, talia_gracza2, karty_do_przepisania, wielkosc_talii_1, wielkosc_talii_2, liczba_ruchow);
	}
}

void wojnaB(talia_gracza talia_gracza1[], talia_gracza talia_gracza2[], int karty_do_przepisania, int& wielkosc_talii1, int& wielkosc_talii2, int& liczba_ruchow) {
	if (wielkosc_talii2 < 2) {
		if (wielkosc_talii2 == 1) {
			if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga < talia_gracza1[karty_do_przepisania + 2].konkretna_karta.waga || wielkosc_talii1 < 4) {
				cout << "!!!  Gre wygral gracz 1  !!!" << endl;
				exit(0);
			}
			else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga > talia_gracza1[karty_do_przepisania + 2].konkretna_karta.waga) {
				if (wielkosc_talii1 < 4) {
					cout << "!!!  Gre wygral gracz 1  !!!" << endl;
					exit(0);
				}
				else {
					cout << "bitwe wygral 2, po pomocy 1" << endl;
					dodaj_karty_z_wojnyB(talia_gracza2, talia_gracza1, wielkosc_talii2, karty_do_przepisania);
					odejmij_karty_z_wojny(talia_gracza1, karty_do_przepisania, wielkosc_talii1);
				}
			}
			else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga == talia_gracza1[karty_do_przepisania + 2].konkretna_karta.waga) {
				if (wielkosc_talii1 < 4) {
					cout << "!!!  Gre wygral gracz 1  !!!" << endl;
					exit(0);
				}
				else {
					karty_do_przepisania = wielkosc_talii2 + 3;
					wielkosc_talii2--;
					wojnaB(talia_gracza1, talia_gracza2, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2,liczba_ruchow);
				}
			}
			else if (wielkosc_talii2 == 0) {
				if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga < talia_gracza1[karty_do_przepisania + 3].konkretna_karta.waga || wielkosc_talii1 < 4) {
					cout << "!!!  Gre wygral gracz 1  !!!" << endl;
					exit(0);
				}
				else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga > talia_gracza1[karty_do_przepisania + 3].konkretna_karta.waga) {
					if (wielkosc_talii1 < 4) {
						cout << "!!!  Gre wygral gracz 1  !!!" << endl;
						exit(0);
					}
					else {
						cout << "bitwe wygral 2, po pomocy 1" << endl;
						dodaj_karty_z_wojnyB(talia_gracza2, talia_gracza1, wielkosc_talii2, karty_do_przepisania);
						odejmij_karty_z_wojny(talia_gracza1, karty_do_przepisania, wielkosc_talii1);
					}
				}
				else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga == talia_gracza1[karty_do_przepisania + 3].konkretna_karta.waga) {
					if (wielkosc_talii1 < 4) {
						cout << "!!!  Gre wygral gracz 1  !!!" << endl;
						exit(0);
					}
					else {
						karty_do_przepisania = wielkosc_talii2 + 4;//wylozyl po 2 karty dla siebie i przeciwnika
						wojnaB(talia_gracza1, talia_gracza2, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2, liczba_ruchow);
					}
				}
			}
		}

	}
	else if (wielkosc_talii1 < 2) {
		if (wielkosc_talii2 == 1) {
			if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga < talia_gracza2[karty_do_przepisania + 2].konkretna_karta.waga || wielkosc_talii2 < 4) {
				cout << "!!!  Gre wygral gracz 2  !!!" << endl;
				exit(0);
			}
			else if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga > talia_gracza2[karty_do_przepisania + 2].konkretna_karta.waga) {
				if (wielkosc_talii2 < 4) {
					cout << "!!!  Gre wygral gracz 2  !!!" << endl;
					exit(0);
				}
				else {
					cout << "bitwe wygral 1, po pomocy 2" << endl;
					dodaj_karty_z_wojnyB(talia_gracza1, talia_gracza2, wielkosc_talii1, karty_do_przepisania);
					odejmij_karty_z_wojny(talia_gracza2, karty_do_przepisania, wielkosc_talii2);
				}
			}
			else if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga == talia_gracza2[karty_do_przepisania + 2].konkretna_karta.waga) {
				if (wielkosc_talii2 < 4) {
					cout << "!!!  Gre wygral gracz 2  !!!" << endl;
					exit(0);
				}
				else {
					karty_do_przepisania = wielkosc_talii1 + 3;
					wielkosc_talii1--;
					wojnaB(talia_gracza2, talia_gracza1, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2, liczba_ruchow);
				}
			}
			else if (wielkosc_talii1 == 0) {
				if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga < talia_gracza2[karty_do_przepisania + 3].konkretna_karta.waga || wielkosc_talii2 < 4) {
					cout << "!!!  Gre wygral gracz 2  !!!" << endl;
					exit(0);
				}
				else if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga > talia_gracza2[karty_do_przepisania + 3].konkretna_karta.waga) {
					if (wielkosc_talii2 < 4) {
						cout << "!!!  Gre wygral gracz 2  !!!" << endl;
						exit(0);
					}
					else {
						cout << "bitwe wygral 1, po pomocy 2" << endl;
						dodaj_karty_z_wojnyB(talia_gracza1, talia_gracza2, wielkosc_talii1, karty_do_przepisania);
						odejmij_karty_z_wojny(talia_gracza2, karty_do_przepisania, wielkosc_talii2);
					}
				}
				else if (talia_gracza2[karty_do_przepisania].konkretna_karta.waga == talia_gracza2[karty_do_przepisania + 3].konkretna_karta.waga) {
					if (wielkosc_talii2 < 4) {
						cout << "!!!  Gre wygral gracz 1  !!!" << endl;
						exit(0);
					}
					else {
						karty_do_przepisania = wielkosc_talii1 + 4;//wylozyl po 2 karty dla siebie i przeciwnika
						wojnaB(talia_gracza2, talia_gracza1, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2, liczba_ruchow);
					}
				}
			}
			else {
				cout << "waga 1:" << talia_gracza1[karty_do_przepisania + 2].konkretna_karta.waga << ", waga 2:" << talia_gracza2[karty_do_przepisania + 2].konkretna_karta.waga << endl;
				karty_do_przepisania = karty_do_przepisania + 2;
				if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga > talia_gracza2[karty_do_przepisania].konkretna_karta.waga) {
					cout << "wojne wygral 1" << endl;
					dodaj_karty_z_wojnyA(talia_gracza1, talia_gracza2, wielkosc_talii1, karty_do_przepisania + 1);
					odejmij_karty_z_wojny(talia_gracza2, karty_do_przepisania + 1, wielkosc_talii2);

				}
				else if (talia_gracza1[karty_do_przepisania].konkretna_karta.waga < talia_gracza2[karty_do_przepisania].konkretna_karta.waga) {
					cout << "wojne wygral 2" << endl;
					dodaj_karty_z_wojnyA(talia_gracza2, talia_gracza1, wielkosc_talii2, karty_do_przepisania + 1);
					odejmij_karty_z_wojny(talia_gracza1, karty_do_przepisania + 1, wielkosc_talii1);

				}

				else {
					cout << "znowu wojna" << endl;
					cout << "waga 1:" << talia_gracza1[karty_do_przepisania].konkretna_karta.waga << ", waga 2:" << talia_gracza2[karty_do_przepisania].konkretna_karta.waga << endl;
					wojnaB(talia_gracza1, talia_gracza2, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2, liczba_ruchow);
				}
			}
		}
	}
	else
		wojnaA(talia_gracza1, talia_gracza2, karty_do_przepisania, wielkosc_talii1, wielkosc_talii2, liczba_ruchow);
}




void bitwa(talia_gracza talia_gracza1[], talia_gracza talia_gracza2[], char wybor, int& wielkosc_talii_1, int& wielkosc_talii_2, int& liczba_ruchow) {
	liczba_ruchow++;
	cout << "........................" << endl << "waga gracza 1: " << talia_gracza1[0].konkretna_karta.waga << endl;
	cout << "waga gracza 2: " << talia_gracza2[0].konkretna_karta.waga << endl;
	if (talia_gracza1[0].konkretna_karta.waga > talia_gracza2[0].konkretna_karta.waga) {
		cout << "bitwe wygral 1" << endl;
		dodaj_karte(talia_gracza1, talia_gracza2, wielkosc_talii_1);
		usun_karte(talia_gracza2, wielkosc_talii_2);
	}
	else if (talia_gracza1[0].konkretna_karta.waga < talia_gracza2[0].konkretna_karta.waga) {
		cout << "bitwe wygral 2" << endl;
		dodaj_karte(talia_gracza2, talia_gracza1, wielkosc_talii_2);
		usun_karte(talia_gracza1, wielkosc_talii_1);
	}
	else if (talia_gracza1[0].konkretna_karta.waga == talia_gracza2[0].konkretna_karta.waga) {
		cout << "wojna" << endl;
		if (wybor == A)
			wojnaA(talia_gracza1, talia_gracza2, 0, wielkosc_talii_1, wielkosc_talii_2,liczba_ruchow);//stala ma byc 0 poniewaz jest to zmienna w petli for wojny ktora zaczyna sie od 0 i jest powiekszana podczas rekurencji
		else
			wojnaB(talia_gracza1, talia_gracza2, 0, wielkosc_talii_1, wielkosc_talii_2, liczba_ruchow);
	}
	cout << "liczba kart gracza 1: " << wielkosc_talii_1 << endl;
	cout << "liczba kart gracza 2: " << wielkosc_talii_2 << endl;
}



int main() {
	srand(time(NULL));

	struct karta* cala_talia = new karta[WIELKOSC_TALII];
	struct talia_gracza* talia_gracza1 = new talia_gracza[WIELKOSC_TALII];
	struct talia_gracza* talia_gracza2 = new talia_gracza[WIELKOSC_TALII];
	char wybor;
	int liczba_kart_gracza1 = WIELKOSC_TALII / 2;//od razu przydzielam liczbe kart graczom 1 i 2 po 26 kart jako poczatkowa
	int liczba_kart_gracza2 = WIELKOSC_TALII / 2;
	int liczba_ruchow=0;
	stworz_talie(cala_talia);
	potasuj(cala_talia);

	rozdaj_karty(cala_talia, talia_gracza1, talia_gracza2, liczba_kart_gracza1, liczba_kart_gracza2);


	/*for (int j = 0; j < liczba_kart_gracza1; j++) {
		cout << "numer: " << j << endl;
		cout << "wartosc" << talia_gracza1[j].konkretna_karta.waga;
		cout << " kolor" << talia_gracza1[j].konkretna_karta.kolor;
		cout << endl << "---------------------" << endl;
	}
	cout << endl << "2 talia" << endl;
	for (int j = 0; j < liczba_kart_gracza2; j++) {
		cout << "numer: " << j << endl;
		cout << "wartosc" << talia_gracza2[j].konkretna_karta.waga;
		cout << " kolor" << talia_gracza2[j].konkretna_karta.kolor;
		cout << endl << "---------------------" << endl;
	}*/

	cout << "------------------------------" << endl << "      WITAJ W GRZE WOJNA      " << endl << "------------------------------" << endl;
	cout << endl << "ABY ZAGRAC MUSISZ WYBRAC WARIANT: " << endl << endl;
	cout << "a)jezeli graczowi skoncza sie wszystkie karty podczas gry - natychmiast przegrywa" << endl;
	cout << "b) pomoc przeciwnika podczas wojny" << endl << endl;
	cout << "podaj wariant 'a' lub 'b' : ";
	cin >> wybor;
	if (wybor == 'a') {
		wybor = A;
	}
	else if (wybor == 'b') {
		wybor = B;
	}
	else {
		cout << "podales bledne dane" << endl;
		return 0;
	}
	while (liczba_kart_gracza1 > 0 && liczba_kart_gracza2 > 0)
	{

		bitwa(talia_gracza1, talia_gracza2, wybor, liczba_kart_gracza1, liczba_kart_gracza2, liczba_ruchow);
	}
	if (liczba_kart_gracza1 <= 0)
	{
		cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 2   !!!!!" << endl;
	}
	else
	{
		cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 1   !!!!!" << endl;
	}
	return 0;
}
