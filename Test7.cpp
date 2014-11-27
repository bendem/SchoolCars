#include <iostream>
#include <fstream>

#include "Model.hpp"
#include "Option.hpp"
#include "Car.hpp"

using namespace std;

int  Menu();
void Essai1();
void Essai2();
void Essai3();

int main() {
    int choix;
    bool fini = false;

    while(!fini) {
        choix = Menu();
        switch(choix) {
            case 1 : Essai1(); break;
            case 2 : Essai2(); break;
            case 3 : Essai3(); break;
            default : fini = true ; break;
        }
    }

    return 0;
}

int Menu()
{
    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "--- JEU DE TEST 7 ---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << " 1. Test des methodes Save et Load de la classe Modele" << endl;
    cout << " 2. Test des mathodes Save et Load de la classe Option" << endl;
    cout << " 3. Test des methodes Save et Load de la classe Voiture" << endl;
    cout << " 4. Quitter" << endl << endl;

    int ch;
    cout << "  Choix : ";
    cin >> ch; // Faites pas le biess !
    cin.ignore();
    return ch;
}

/*********************************************************************************************/
void Essai1()  // Attention : utilisez les flux bytes (read et write) !!!!
{
    cout << "----- 1. Test des methodes Save et Load de la classe Modele ------" << endl;

    Model m("RCZ 2.0 HDi",163,true,30150.0f);
    m.display();
    cout << endl;

    cout << "----- Sauvegarde du modele dans le fichier RCZ.dat -----" << endl;
    ofstream fichier1("RCZ.dat",ios::out);
    m.save(fichier1);
    fichier1.close();

    cout << "----- Chargement du modele situe dans le fichier RCZ.dat -----" << endl;
    ifstream fichier2("RCZ.dat",ios::in);
    Model m2;
    m2.load(fichier2);
    fichier2.close();
    m2.display();
    cout << endl;
}

/*********************************************************************************************/
void Essai2()  // Attention : utilisez les flux bytes (read et write) !!!!
{
    cout << "----- 2. Test des methodes Save et Load de la classe Option ------" << endl;

    Option option("ZH75","Jantes alliage leger 15 pouces",450.0f);
    option.display();
    cout << endl;

    cout << "----- Sauvegarde de l'option dans le fichier JantesAlliage.dat -----" << endl;
    ofstream fichier1("JantesAlliage.dat",ios::out);
    option.save(fichier1);
    fichier1.close();

    cout << "----- Chargement de l'option situee dans le fichier JantesAlliage.dat -----" << endl;
    ifstream fichier2("JantesAlliage.dat",ios::in);
    Option o2;
    o2.load(fichier2);
    fichier2.close();
    o2.display();
    cout << endl;
}

/*********************************************************************************************/
void Essai3()  // Attention : utilisez les flux bytes (read et write) !!!!
{
    cout << "----- 3. Test des methodes Save et Load de la classe Voiture ------" << endl;

    Car voiture("Projet_208_MrLagalere",Model("208 Access 1.0",68,false,12500.0f));
    voiture.addOption(Option("0MM0","Peinture metallisee",450.0f));
    voiture.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
    voiture.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
    voiture.display();
    cout << "Prix du projet : " << voiture.getPrice() << " euros" << endl << endl;

    cout << "----- Sauvegarde du projet de Voiture -----" << endl;
    voiture.save();
    cout << endl;

    cout << "----- Chargement du projet de Voiture du fichier Projet_208_MrLagalere.car -----" << endl;
    Car voiture2;
    voiture2.load("Projet_208_MrLagalere.car");
    voiture2.display();
    cout << "Prix du projet : " << voiture2.getPrice() << " euros" << endl << endl;

    cout << endl;
}
