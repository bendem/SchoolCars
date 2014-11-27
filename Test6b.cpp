#include <iostream>
#include <cstdlib>
#include <ctime>

#include "collections/Stack.hpp"
#include "Option.hpp"

using namespace std;

int  Menu();
void Essai1();
void Essai2();

int main()
{
    int choix;
    bool fini = false;
    srand((unsigned)time(NULL));

    while(!fini)
    {
        choix = Menu();
        switch(choix)
        {
            case 1 : Essai1(); break;
            case 2 : Essai2(); break;
            default : fini = true ; break;
        }
    }

    return 0;
}

int Menu()
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "--- JEU DE TEST 6 (classe Pile) ------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << " 1. Test du template Pile avec des entiers" << endl;
    cout << " 2. Test du template Pile avec des objets de la classe Option" << endl;
    cout << " 3. Quitter" << endl << endl;

    int ch;
    cout << "  Choix : ";
    cin >> ch; // Faites pas le biess !
    cin.ignore();
    return ch;
}

/*******************************************************************************************************/
void Essai1()
{
    cout << "----- 1. Test du template Pile avec des entiers ------------------------" << endl;
    cout << "Creation  d'une Pile..." << endl;
    Stack<int> pile;
    pile.display();                                       // --> ()
    cout << endl;

    cout << "On empile 3..." << endl;
    pile.add(3);
    pile.display();                                       // --> (3)

    cout << "On empile 8..." << endl;
    pile.add(8);
    pile.display();                                       // --> (8 3)

    cout << "On empile 5.." << endl;
    pile.add(5);
    pile.display();                                       // --> (5 8 3)

    cout << "On depile..." << endl;
    int valeurDepilee = pile.pop();
    cout << "Valeur depilee = " << valeurDepilee << endl;
    pile.display();                                       // --> (8 3)

    cout << "On empile 12.." << endl;
    pile.add(12);
    pile.display();                                       // --> (12 8 3)

    cout << endl;
}

/*********************************************************************************************/
void Essai2()
{
    cout << "----- 2. Test du template Pile avec des Options ------------------------" << endl;
    cout << "Creation  d'une Pile..." << endl;
    Stack<Option> pile;
    pile.display();
    cout << endl;

    cout << "On empile l'option 0MM0..." << endl;
    pile.add(Option("0MM0","Peinture metallisee",450.0f));
    pile.display();

    cout << "On empile l'option ZH75..." << endl;
    Option op("ZH75","Jante alliage leger 15 pouces",450.0f);
    pile.add(op);
    pile.display();

    cout << "On empile l'option 0P3U..." << endl;
    Option *ptr = new Option("0P3U","Pack Cuir ambiance Mistral",1100.0f);
    pile.add(*ptr);
    delete ptr;
    pile.display();

    cout << "On depile..." << endl;
    Option valeurDepilee = pile.pop();
    cout << "Valeur depilee = " << valeurDepilee << endl;
    pile.display();

    cout << "On empile l'option VD09.." << endl;
    pile.add(Option("VD09","Vitres laterales arriere surteintees",150.0f));
    pile.display();

    cout << endl;
}
