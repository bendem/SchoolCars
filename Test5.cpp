#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Employee.hpp"
#include "exceptions/InvalidFunctionException.hpp"
#include "exceptions/InvalidPasswordException.hpp"

using namespace std;

int  Menu();
void Essai1();
void Essai2();
void Essai3();

int main()
{
    int choix;
    bool fini = false;
    srand((unsigned) time(NULL));

    while(!fini)
    {
        choix = Menu();
        switch(choix)
        {
            case 1 : Essai1(); break;
            case 2 : Essai2(); break;
            case 3 : Essai3(); break;
            default : fini = true ; break;
        }
    }

    exit(0);
}

int Menu()
{
    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "--- JEU DE TEST 5 ---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << " 1. Test des methodes susceptibles de lancer une InvalidFonctionException" << endl;
    cout << " 2. Test des methodes susceptibles de lancer une InvalidPasswordException" << endl;
    cout << " 3. Gestion de plusieurs exceptions simultanement" << endl;
    cout << " 4. Quitter" << endl << endl;

    int ch;
    cout << "  Choix : ";
    cin >> ch; // Faites pas le biess !
    cin.ignore();
    return ch;
}

/**********************************************************************************************/
// ATTENTION !!!!
// Les methodes de vos classes NE doivent PAS contenir de TRY{...} CATCH{...} mais
// uniquement des THROW !!! Donc, votre classe lance une exception (une erreur) mais
// ce n'est pas elle qui la traite. C'est l'application qui utilise votre classe
// qui doit traiter les exceptions. C'est donc uniquement dans le main (ou les fonctions appelees)
// que l'on trouve des try...catch 
/**********************************************************************************************/
void Essai1()
{
    cout << "----- 1. Test des methodes susceptibles de lancer une exception InvalidFonctionException --------" << endl;
    // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
    // en particulier : afficher le message de l'exception lancee

    // ...
    {
        cout << "--> Creation d'un objet de la classe Employe <--" << endl;
        Employee e1("Dupont", "Michel", 2, "dupomich", Employee::ADMINISTRATIVE);  // !!!
        cout << e1 << endl << endl;
        cout << "Nouvelle fonction : ";
        char txt[80];
        cin.getline(txt,80,'\n');
        try {
            e1.setFunction(txt);  // !!!
        } catch(InvalidFunctionException e) {
            e.display();
        }
        cout << endl << e1 << endl << endl;

        cout << "--> Creation d'un second objet de la classe Employe <--" << endl;
        Employee e2;
        cout << "Encodez les donnees d'un nouvel employe :" << endl;
        try {
            cin >> e2;  // !!!
        } catch(InvalidFunctionException e) {
            e.display();
        }
        cout << endl << "Voici l'employe que vous avez encode :" << endl;
        cout << e2 << endl;
    }
    // ...

    cout << endl;
}

/**********************************************************************************************/
void Essai2()
{
    cout << "----- 2. Test des methodes susceptibles de lancer une exception InvalidPasswordException --------" << endl;
    // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
    // en particulier : Tester le code de l'erreur et affiche la cause exacte de l'erreur.

    // ...
    {
        Employee e1("Dupont","Michel",2,"dupomich",Employee::ADMINISTRATIVE);
        cout << e1 << endl << endl;
        cout << "Encodez son mot de passe : ";
        char txt[80];
        cin.getline(txt, 80, '\n');
        try {
            e1.setPassword(txt);  // !!!
        } catch (InvalidPasswordException e) {
            e.display();
        }
        cout << endl << "Le mot de passe encode est : " << e1.getPassword() << endl;
    }
    // ...

    cout << endl;
}

/**********************************************************************************************/
void Essai3()
{
    cout << "----- 3. Gestion de plusieurs exceptions simultanement ---" << endl;
    // A COMPLETER : Traitez TOUTES les exceptions susceptible d'etre lancee par le bloc de code suivant (try...catch)

    // ...
    {
        Employee e;
        cout << "Encodez un nouvel employe :" << endl;
        cin >> e;
        cout << "Saisissez son mot de passe : ";
        char txt[80];
        cin.getline(txt,80,'\n');
        try {
            e.setPassword(txt);
        } catch(InvalidPasswordException ex) {
            e.display();
        }
        cout << endl << "Voici l'employe encode :" << endl;
        cout << e << endl;
        cout << "et son mot de passe : " << e.getPassword() << endl << endl;
        cout << "Nouvelle fonction : ";
        cin.getline(txt,80,'\n');
        try {
            e.setFunction(txt);
        } catch(InvalidFunctionException ex) {
            e.display();
        }
        cout << "Voici la nouvelle fonction encodee : " << e.getFunction() << endl;
    }
    // ...

    cout << endl;
}

