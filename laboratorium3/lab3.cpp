#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class matrix {

    private:
    
    double **tab;
    int a, b;
    void macierz() {
         tab = new double*[a];
         for(int i = 0; i < a; i++) {
             tab[i] = (double*)calloc(b, sizeof(double));
         }
    }

    public:

    matrix(int n, int m) {
        a = n;
        b = m;
        macierz();
    }

    matrix(int n) {
        a = n;
        b = n;
        macierz();
    }

    void set(int x, int y, double val) {

        if (x > 0 && x <= a && y > 0 && y <= b) {
            tab[x-1][y-1] = val;
        } else {
            cout << "Podales zle argumenty!" << endl;
        }
    }

    int get(int x, int y) {

        if (x > 0 && x <= a && y > 0 && y <= b) {
             return tab[x-1][y-1];
        } else {
            cout << "Podales zle argumenty!" << endl;
            return 1;
        }
    }

    matrix add(matrix tablica3) {

        if (a != tablica3.rows() || b != tablica3.cols()) {
            cout << "Nie mozna dodac macierze" << endl;
            return 1;
        }

        matrix dodanemacierze(a,b);
            for(int i = 0; i < a; i++) {
                for(int j = 0; j < b; j++){
                    dodanemacierze.tab[i][j] = tab[i][j] + tablica3.tab[i][j];
                }
            }
        return dodanemacierze;
    }

    matrix substract(matrix tablica3) {

        if (a != tablica3.rows() || b != tablica3.cols()) {
            cout << "Nie mozna odjac macierze" << endl;
            return 1;
        }

        matrix odjetemacierze(a,b);
            for(int i = 0; i < a; i++) {
                for(int j = 0; j < b; j++){
                    odjetemacierze.tab[i][j] = tab[i][j] - tablica3.tab[i][j];
                }
            }
        return odjetemacierze;
    }

    matrix multiply(matrix tablica4) {

        if (a != tablica4.rows()) {
            cout << "Nie mozna pomnozyc" << endl;
            return 1;
        }

        matrix mnozonemacierze(a,b);
        for(int i = 0; i < a; i++) {
            for(int j = 0; j < b; j++) {
                mnozonemacierze.tab[i][j] = 0;
                for(int k = 0; k < b; k++) {
                    mnozonemacierze.tab[i][j] += tab[i][k] * tablica4.tab[k][j];
                }
                return mnozonemacierze;
            }
        }
    }


    int rows() {
        //cout << "Liczba wierszy: " << a << endl;
        return a;
    }

    int cols() {
        //cout << "Liczba kolumn: " << b << endl;
        return b;
    }

    void print() {
        for(int i = 0; i < a; i++) {
            for(int j = 0; j < b; j++) {
                cout << tab[i][j] << "\t";
            }
            cout << endl;
        }
    }

    matrix store(std::string filename, std::string path) {

        std::ofstream  plik;
		path += "\\" + filename;
		plik.open(path, std::ios_base::out);
		if (!plik.good())
		{
			std::cout << "Nie otwarto pliku." << endl;
			exit(0);
		}

		plik << a << "\t" << b << endl;
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
				plik << tab[i][j] << "\t";
			plik << endl;
		}

		plik.close();
	 }

     matrix Matrix(std::string path) {
		std::ifstream plik;
		plik.open(path);
		if (plik.good() != 0) {
			std::cout << "Nie otwarto pliku" << std::endl;
			exit(1);
		}

		plik >> a;
		plik >> b;

		for (int i = 0; i < a; i++) {

			for (int j = 0; j < b; j++) {

				plik >> tab[i][j];
			}
		}
		plik.close();
	}
};

int main() {

    cout << "Tablica (niekwadratowa) zainicjowana zerami:" << endl;
    matrix tablica1(4,5);
    tablica1.print();

    cout << "Tablica (kwadratowa) zainicjowana zerami:" << endl;
    matrix tablica2(4);
    tablica2.print();

    cout << "Funkcja set dla tablicy niekwadratowa:" << endl;
    tablica1.set(2,1,768);
    tablica1.print();

    cout << "Element, ktory pobrales testujac funkcje get to: ";
    cout << tablica1.get(2,1) << endl;

    cout << "Suma macierzy tablica1 oraz tablica3:" << endl;
    matrix tablica3(4,5);
    tablica3.set(2,1,100);
    tablica1.print();
    cout << "+" << endl;
    tablica3.print();
    matrix dodanemacierze = tablica1.add(tablica3);
    cout << "=" << endl;
    dodanemacierze.print();
    cout << "Liczba wierszy: " << dodanemacierze.rows() << endl;
    cout << "Liczba kolumn: " <<dodanemacierze.cols() << endl;

    cout << "Odejmowanie tablicy1 i tablicy3:" << endl;
    tablica1.print();
    cout << "-" << endl;
    tablica3.print();
    matrix odjetemacierze = tablica1.substract(tablica3);
    cout << "=" << endl;
    odjetemacierze.print();
    cout << "Liczba wiersz: " << odjetemacierze.rows() << endl;
    cout << "Liczba kolumn: " << odjetemacierze.cols() << endl;

    cout << "Mnozenie macierzy tablica5 i tablica4" << endl;
    matrix tablica5(4,4);
    tablica5.set(1,1,2);
    tablica5.set(1,2,2);
    tablica5.set(1,3,2);
    tablica5.set(1,4,2);
    matrix tablica4(4,4);
    tablica4.set(1,1,2);
    tablica4.set(2,1,2);
    tablica4.set(3,1,2);
    tablica4.set(4,1,2);
    tablica5.print();
    cout << "*" << endl;
    tablica4.print();
    matrix mnozonemacierze = tablica5.multiply(tablica4);
    cout << "=" << endl;
    mnozonemacierze.print();
    cout << "Liczba wierszy: " << mnozonemacierze.rows() << endl;
    cout << "Liczba kolumn: " << mnozonemacierze.cols() << endl;

    cout << "Zapisywanie macierzy do pliku" << endl;
    string nazwa;
    string sciezka;

    cout << "Podaj nazwe pliku, w ktorym chcesz zapisac macierz: ";
    cin >> nazwa;
    cout << "Podaj sciezke do tego pliku: ";
    cin >> sciezka;
    mnozonemacierze.store(nazwa,sciezka);


    return 0;

}