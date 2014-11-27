#include <stdlib.h>
#include <iostream>
#include "Model.hpp"

using namespace std;

// Quelques conseils avant de commencer...
// * N'oubliez pas de tracer (cout << ...) tous les constructeurs et le destructeur !!! Ca, c'est pas un conseil,
//   c'est obligatoire :-)
// * N'essayez pas de compiler ce programme entierement immediatement. Mettez tout en commentaires
//   sauf le point (1) et creez votre classe (dans ce fichier pour commencer) afin de compiler et tester
//   le point (1). Une fois que cela fonctionne, decommentez le point (2) et modifier votre classe en
//   consequence. Vous developpez, compilez et testez donc etape par etape. N'attendez pas d'avoir encode
//   300 lignes pour compiler...
// * Une fois que tout le programme compile et fonctionne correctement, creez le .h contenant la declaration
//   de la classe, le .cxx contenant la definition des methodes, et ensuite le makefile permettant de compiler
//   le tout grace a la commande make

int main() {
    cout << endl << "(1) ***** Test constructeur par defaut + Affiche *****" << endl;
    {
        Model modele;
        modele.display();
    } // La presence des accolades assure que le destructeur de Modele sera appele --> a tracer !

    cout << endl << "(2) ***** Test des setters et getters *****" << endl;
    {
        Model modele;
        modele.setName("208 Active 1.4HDi 3P");
        modele.setPower(68);
        modele.setDiesel(true);
        modele.setBaseCost(16450.0f);
        modele.display();
        cout << "Nom          = " << modele.getName() << endl;
        cout << "Puissance    = " << modele.getPower() << " Ch" << endl;
        cout << "Carburant    = ";
        if (modele.isDiesel())
            cout << "diesel" << endl;
        else
            cout << "essence" << endl;
        cout << "Prix de base = " << modele.getBaseCost() << " euros" << endl;
    }

    cout << endl << "(3) ***** Test du constructeur d'initialisation *****" << endl;
    {
        Model modele("208 Allure 1.6 5P", 120, false, 17600.0f);
        modele.display();
    }

    cout << endl << "(4) ***** Test du constructeur de copie *****" << endl;
    {
        Model modele1("RCZ 2.0 HDi", 163, true, 30150.0f);
        cout << "modele1 (AVANT) :" << endl;
        modele1.display();
        {
            Model modele2(modele1);
            cout << "modele2 :" << endl;
            modele2.display();
            modele2.setName("RCZ 2.0 HDi FAP");
            modele2.display();
        } // de nouveau, les {} assurent que modele2 sera detruit avant la suite
        cout << "modele1 (APRES) :" << endl;
        modele1.display();
    }

    cout << endl << "(5) ***** Test d'allocation dynamique (constructeur par defaut) *****" << endl;
    {
        Model *p = new Model();
        p->setName("3008 Active 1.6 5P");
        p->setPower(120);
        p->setDiesel(false);
        p->setBaseCost(22720.0f);
        p->display();
        cout << "Le prix de base de ce modele est : " << p->getBaseCost() << " euros" << endl;
        delete p;
    }

    cout << endl << "(6) ***** Test d'allocation dynamique (constructeur de copie) *****" << endl;
    {
        Model modele1("308CC Sport Pack 1.6 2P", 120, false, 27725.0f);
        cout << "modele1 (AVANT) :" << endl;
        modele1.display();
        Model* p = new Model(modele1);
        cout << "La copie :" << endl;
        p->display();
        cout << "Destruction de la copie..." << endl;
        delete p;
        cout << "modele1 (APRES) :" << endl;
        modele1.display();
    }

    return 0;
}

