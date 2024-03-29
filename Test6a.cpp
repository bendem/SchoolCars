#include <cstdlib>
#include <ctime>
#include <iostream>

#include "collections/List.hpp"
#include "Option.hpp"

using namespace std;

int  Menu();
void Essai1();
void Essai2();

int main() {
    int choix;
    bool fini = false;
    srand((unsigned) time(NULL));

    while(!fini) {
        choix = Menu();
        switch(choix) {
            case 1:
                Essai1();
                break;
            case 2:
                Essai2();
                break;
            default:
                fini = true;
        }
    }

    return 0;
}

int Menu() {
    cout << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "--- JEU DE TEST 6 (classe Liste) -----------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << " 1. Test du template Liste avec des entiers" << endl;
    cout << " 2. Test du template Liste avec des objets de la classe Option" << endl;
    cout << " 3. Quitter" << endl << endl;

    int ch;
    cout << "  Choix : ";
    cin >> ch; // Faites pas le biess !
    cin.ignore();
    return ch;
}

/*******************************************************************************************************/
void Essai1() {
    cout << "----- 1. Test du template Liste avec des entiers ------------------------" << endl;
    cout << "Creation  d'une Liste..." << endl;
    List<int> liste;
    liste.display();                                       // --> ()
    cout << endl;

    cout << "On insere 3,-2,5,-1 et 0..." << endl;
    liste.add(3);
    liste.add(-2);
    liste.add(5);
    liste.add(-1);
    liste.add(0);
    liste.display();                                       // --> (3 -2 5 -1 0)
    cout << "La liste contient " << liste.size() << " elements." << endl;
    cout << endl;
}

/*********************************************************************************************/
void Essai2() {
    cout << "----- 2. Test du template Liste avec des Options ------------------------" << endl;
    cout << "Creation  d'une Liste..." << endl;
    List<Option> liste;
    liste.display();
    cout << endl;

    cout << "On insere l'option 0MM0..." << endl;
    liste.add(Option("0MM0","Peinture metallisee",450.0f));
    liste.display();

    cout << "On insere l'option ZH75..." << endl;
    Option op("ZH75","Jante alliage leger 15 pouces",450.0f);
    liste.add(op);
    liste.display();

    cout << "On insere l'option 0P3U..." << endl;
    Option *ptr = new Option("0P3U","Pack Cuir ambiance Mistral",1100.0f);
    liste.add(*ptr);
    delete ptr;
    liste.display();
    cout << "La liste contient " << liste.size() << " elements." << endl;

    cout << endl;
}

