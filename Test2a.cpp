#include <iostream>
#include "Model.hpp"
#include "Car.hpp"
using namespace std;

// Tests de base de la classe Voiture (sans les options)

int main()
{
    cout << "(1) ***** Test du constructeur par defaut de Voiture *****" << endl;
    {
        Car voiture;
        voiture.display();
    }

    cout << endl << "(2) **** Test des setters/getters *****" << endl;
    {
        Car voiture;
        voiture.setName("Projet_2008_MrDugenou");
        voiture.setModel(Model("5008 Active 2.0 HDi 5P",136,true,28080.0f));
        voiture.display();
        cout << "Nom du projet : " << voiture.getName() << endl;
        cout << "Modele du projet : " << endl;
        voiture.getModel().display();
    }

    cout << endl << "(3) ***** Test du constructeur d'initialisation de Voiture *****" << endl;
    {
        Car voiture("Projet_508SW_MmeLoreille", Model("508SW Style 1.6 HDi",115,true,28500.0f));
        voiture.display();
        cout << "Nom du projet : " << voiture.getName() << endl;
        cout << "Modele du projet : " << endl;
        voiture.getModel().display();
    }

    cout << endl << "(4) ***** Test du constructeur de copie de Voiture *****" << endl;
    {
        Car voiture1("Projet_208GTi_MrLepresse", Model("208 GTi 1.6",200,false,23100.0f));
        cout << "voiture1 (AVANT) :" << endl;
        voiture1.display();
        {
            Car voiture2(voiture1);
            cout << "voiture2 :" << endl;
            voiture2.display();
            voiture2.setName("Projet_208GTi_MrLepresse_bis");
            voiture2.display();
        }
        cout << "voiture1 (APRES) :" << endl;
        voiture1.display();
    }

    return 0;
}


