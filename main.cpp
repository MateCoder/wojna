#include <iostream>
#include <cstdlib>
#include<ctime>
#define WIELKOSC_TALII 52
#define LICZBA_KOLOROW 4
#define LICZBA_KART_W_KOLORZE 13
using namespace std;

struct karta {
	//int pomocnicza_wagi;
	int kolor;
	//char wartosc;
	int waga;
};

struct talia_gracza {
	talia_gracza* nastepny;
	talia_gracza* poprzedni;
	talia_gracza* pierwszy;
	talia_gracza* ostatni;
	karta konkretna_karta;
	//int key;
	int licznik;
};
int liczba_kart_gracza1 = WIELKOSC_TALII / 2;
int liczba_kart_gracza2 = WIELKOSC_TALII / 2;


void stworz_talie(karta cala_talia[]) {
	int pomocnicza_wagi;
	pomocnicza_wagi = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < LICZBA_KART_W_KOLORZE; i++) {
		for (j = 0; j < LICZBA_KART_W_KOLORZE; j++) {
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
	for (int i = 0; i < WIELKOSC_TALII; i++) {
		j = rand() % 52;
		pomocnicza = cala_talia[i];
		cala_talia[i] = cala_talia[j];
		cala_talia[j] = pomocnicza;
	}
}

void rozdaj_karty(karta cala_talia[], talia_gracza talia_gracza1[], talia_gracza talia_gracza2[]) {
	int i;
	int j = 0;
	int k=0;
	for (i = 0; i < WIELKOSC_TALII; i++) {
		if (i % 2 == 0) {
				talia_gracza1[j].nastepny = talia_gracza1[j + 1].nastepny;
				talia_gracza1[j].poprzedni = talia_gracza1[j - 1].poprzedni;
				talia_gracza1[j].pierwszy = talia_gracza1[0].pierwszy;
				talia_gracza1[j].ostatni = talia_gracza1[liczba_kart_gracza1].ostatni;
				talia_gracza1[j].konkretna_karta = cala_talia[i];
				j++;
			
		}
		else{
				talia_gracza2[k].nastepny = talia_gracza2[k + 1].nastepny;
				talia_gracza2[k].poprzedni = talia_gracza2[k - 1].poprzedni;
				talia_gracza2[k].pierwszy = talia_gracza2[0].pierwszy;
				talia_gracza2[k].ostatni = talia_gracza2[liczba_kart_gracza2].ostatni;
				talia_gracza2[k].konkretna_karta = cala_talia[i];
				k++;
			}
	}
}

void przepisz_talie(talia_gracza talia_do_przepisania[], int stala_pomocnicza) {
	struct talia_gracza* talbica_pomocnicza=new talia_gracza[stala_pomocnicza];
	int i = 0;
	int j;
	while (talia_do_przepisania[i].konkretna_karta.waga == 80)//80 poniewaz jest to liczba poza zakresem talii, ktora przypisuje kartom ktore chce usunac
		i++;
	for (j = 0; j < stala_pomocnicza; j++) {
		talbica_pomocnicza[j] = talia_do_przepisania[i];
		i++;
	}
	for (j = 0; j < stala_pomocnicza; j++) {
		talia_do_przepisania[j] = talbica_pomocnicza[j];
	}
}
void dodaj_karte(talia_gracza talia_wygranego[], talia_gracza talia_przegranego[], int licznik_kart) {
	licznik_kart++;
	talia_wygranego[0].konkretna_karta.waga=80;
	talia_wygranego[licznik_kart] = talia_wygranego[0];
	talia_wygranego[licznik_kart + 1] = talia_przegranego[0];
	przepisz_talie(talia_wygranego, licznik_kart);
}

void usun_karte(talia_gracza talia_przegranego[], int licznik_kart) {
	licznik_kart--;
	talia_przegranego[0].konkretna_karta.waga = 80;
	przepisz_talie(talia_przegranego, licznik_kart);
}
//int wojenna_poczatkowa = 0;

void dodaj_karty_z_wojny(talia_gracza talia_zwyciezcy[], talia_gracza tablica_pomocnicza_w[], talia_gracza tablica_pomocnicza_p[], int liczba_kart_w_talii, int odjete_karty) {
	
	for (int i = 0; i < odjete_karty; i++) {
		talia_zwyciezcy[liczba_kart_w_talii + odjete_karty + i] = tablica_pomocnicza_w[i];
		talia_zwyciezcy[i].konkretna_karta.waga = 80;
	}
	for (int i = 0; i < odjete_karty; i++) {
		talia_zwyciezcy[liczba_kart_w_talii + 2 * odjete_karty + i] = tablica_pomocnicza_p[i];
	}
	przepisz_talie(talia_zwyciezcy, liczba_kart_w_talii+2*odjete_karty+1);//!!!!!!!!!!!!!mozliwa ze bez 1
}
void odejmij_karty_z_wojny(talia_gracza tablica_przegranego[], int liczba_odjetych_kart) {
	for (int i = 0; i < liczba_odjetych_kart; i++) {
		tablica_przegranego[i].konkretna_karta.waga = 80;
	}
	przepisz_talie(tablica_przegranego, liczba_odjetych_kart);
}


void wojna(talia_gracza talia_gracza1[], talia_gracza talia_gracza2[], int pomocnicza_wojny) {
	//int i;
	int licznik_odjetych_kart;
	if (liczba_kart_gracza1 < 2) {
			cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 2   !!!!!" << endl << "poniewaz gracz 1 ma za malo kart aby rozpoczac wojne" << endl;
			exit(0);
	}

	else {
			cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 1   !!!!!" << endl << "poniewaz gracz 2 ma za malo kart aby rozpoczac wojne" << endl;
			exit(0);
	}
	struct talia_gracza* talbica_pomocnicza_gracza1 = new talia_gracza[WIELKOSC_TALII];
	struct talia_gracza* talbica_pomocnicza_gracza2 = new talia_gracza[WIELKOSC_TALII];
	for (; pomocnicza_wojny < pomocnicza_wojny+2; pomocnicza_wojny++) {
		licznik_odjetych_kart++;
		talbica_pomocnicza_gracza1[pomocnicza_wojny] = talia_gracza1[pomocnicza_wojny];
		liczba_kart_gracza1--;
		talbica_pomocnicza_gracza2[pomocnicza_wojny] = talia_gracza2[pomocnicza_wojny];
		liczba_kart_gracza2--;
	}
	if (talia_gracza1[pomocnicza_wojny].konkretna_karta.waga > talia_gracza2[pomocnicza_wojny].konkretna_karta.waga) {
		dodaj_karty_z_wojny(talia_gracza1, talbica_pomocnicza_gracza1, talbica_pomocnicza_gracza2,liczba_kart_gracza1,licznik_odjetych_kart);
		odejmij_karty_z_wojny(talia_gracza2, licznik_odjetych_kart);
		talbica_pomocnicza_gracza1 = NULL;
		talbica_pomocnicza_gracza2 = NULL;
	}
	else if (talia_gracza1[pomocnicza_wojny].konkretna_karta.waga < talia_gracza2[pomocnicza_wojny].konkretna_karta.waga) {
		//przypisz talie dla 2
		dodaj_karty_z_wojny(talia_gracza2, talbica_pomocnicza_gracza2, talbica_pomocnicza_gracza1, liczba_kart_gracza2, licznik_odjetych_kart);
		odejmij_karty_z_wojny(talia_gracza1, licznik_odjetych_kart);
		talbica_pomocnicza_gracza1 = NULL;
		talbica_pomocnicza_gracza2 = NULL;
	}
		
	else {
		pomocnicza_wojny = pomocnicza_wojny + 2;
		wojna(talia_gracza1, talia_gracza2, pomocnicza_wojny);
	}
	
	

}
int stala = 0;
void bitwa(talia_gracza talia_gracza1[], talia_gracza talia_gracza2[]) {

	if (talia_gracza1[0].konkretna_karta.waga > talia_gracza2[0].konkretna_karta.waga) {
		dodaj_karte(talia_gracza1, talia_gracza2, liczba_kart_gracza1);
		usun_karte(talia_gracza2, liczba_kart_gracza2);
	}
	else if (talia_gracza1[0].konkretna_karta.waga < talia_gracza2[0].konkretna_karta.waga) {
		dodaj_karte(talia_gracza2, talia_gracza1, liczba_kart_gracza2);
		usun_karte(talia_gracza1, liczba_kart_gracza1);
	}
	else if (talia_gracza1[0].konkretna_karta.waga == talia_gracza2[0].konkretna_karta.waga) {
		
		wojna(talia_gracza1, talia_gracza2, stala);
	}
}
/*
TO BYLO W WOJNIE


if (talia_gracza1[0].konkretna_karta.waga > talia_gracza2[0].konkretna_karta.waga) {
		dodaj_karte(talia_gracza1, talia_gracza2, liczba_kart_gracza1);
		usun_karte(talia_gracza2, liczba_kart_gracza2);
	}
	if (talia_gracza1[0].konkretna_karta.waga < talia_gracza2[0].konkretna_karta.waga) {
		dodaj_karte(talia_gracza2, talia_gracza1, liczba_kart_gracza2);
		usun_karte(talia_gracza1, liczba_kart_gracza1);
	}
*/


int main() {
	srand(time(NULL));

	struct karta* cala_talia = new karta[WIELKOSC_TALII];
	struct talia_gracza* talia_gracza1 = new talia_gracza[WIELKOSC_TALII];
	struct talia_gracza* talia_gracza2 = new talia_gracza[WIELKOSC_TALII];

	//talia_gracza1* poczatek = NULL;
	char wybor;

	stworz_talie(cala_talia);
	potasuj(cala_talia);

	rozdaj_karty(cala_talia, talia_gracza1, talia_gracza2);


	/*for (int j = 0; j < WIELKOSC_TALII / 2; j++) {
		cout << "numer: " << j << endl;
		cout << "wartosc" << talia_gracza1[j].konkretna_karta.waga;
		cout << " kolor" << talia_gracza1[j].konkretna_karta.kolor;
		cout << endl << "---------------------" << endl;
	}
	cout<<endl << "2 talia" << endl;
	for (int j = 0; j < WIELKOSC_TALII / 2; j++) {
		cout << "numer: " << j << endl;
		cout << "wartosc" << talia_gracza2[j].konkretna_karta.waga;
		cout << " kolor" << talia_gracza2[j].konkretna_karta.kolor;
		cout << endl << "---------------------" << endl;
	}*/

	
	cout <<endl<< "------------------------------" << endl << "      WITAJ W GRZE WOJNA      " << endl << "------------------------------" << endl;
	cout <<endl<< "ABY ZAGRAC MUSISZ WYBRAC WARIANT: " << endl<<endl;
	cout<< "a)jezeli graczowi skoncza sie wszystkie karty podczas gry - natychmiast przegrywa" << endl;
	cout << "b) pomoc przeciwnika podczas wojny" << endl<<endl;
	cout << "podaj wariant 'a' lub 'b' : ";
	cin >> wybor;
	if (wybor == 'a') {
		for(int f=0; f<50; f++){
		while (liczba_kart_gracza1>0&&liczba_kart_gracza2>0)
		{
			bitwa(talia_gracza1, talia_gracza2);
		}
		if(liczba_kart_gracza1==0)
			cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 2   !!!!!" << endl;
		else
			cout << endl << endl << "!!!!!   WYGRAL GRACZ NR 1   !!!!!" << endl;
		}
	}
	


	return 0;
}
