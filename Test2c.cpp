#include <iostream>

#include "Car.hpp"
#include "Model.hpp"
#include "Option.hpp"

using namespace std;

// Tests de la classe Voiture (avec options)

int main()
{
    cout << "(1) ***** on cree un objet Voiture *****" << endl;
    Car voiture("Projet_208_MrLagalere",Model("208 Access 1.0",68,false,12500.0f));
    voiture.display(); // Affiche doit a present tenir comptes des options

    cout << "(2) ***** on ajoute 3 options *****" << endl;
    voiture.addOption(Option("0MM0","Peinture metallisee",450.0f));
    voiture.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
    voiture.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
    voiture.display();

    cout << "(3) ***** on calcule le prix du projet *****" << endl;
    cout << "Prix du projet : " << voiture.getPrice() << " euros" << endl << endl;

    cout << "(4) ***** on retire l'option ZH75 *****" << endl;
    voiture.removeOption("ZH75");
    voiture.display();
    cout << "Prix du projet : " << voiture.getPrice() << " euros" << endl << endl;

    cout << "(5) ***** on ajoute une derniere option *****" << endl;
    voiture.addOption(Option("FE10","Pack LED",350.0f));
    voiture.display();
    cout << "Prix du projet : " << voiture.getPrice() << " euros" << endl << endl;

    cout << "(6) ***** Test du constructeur de copie et du destructeur de Voiture *****" << endl;
    {
        Car voiture2(voiture);
        voiture2.removeOption("0MM0");
        cout << "Copie modifiee du projet de depart :" << endl;
        voiture2.display();
        // on regarde comment se comporte le destructeur de Voiture :)
        // et surtout si celui de Option est appele un nombre de fois suffisant !
    }

    cout << "(7) ***** on regarde si le projet de depart n'a pas ete modifie *****" << endl;
    voiture.display();

    return 0;
}


