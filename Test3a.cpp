#include <iostream>

#include "Model.hpp"
#include "Option.hpp"
#include "Car.hpp"

using namespace std;

void Pause()
{
    char buffer[20];
    cout << endl << "--> RETURN <--";
    cin.getline(buffer,20);
}

int main()
{
    cout << "**********************************************************************" << endl;
    cout << "(1) ***** Test de l'opérateur d'affectation de Voiture ***************" << endl;
    cout << "**********************************************************************" << endl;
    Car v1("Projet_208_MrDugenou", Model("208 Acces 3P 1.4 HDi",68,true,14600.0f));
    v1.addOption(Option("0MM0","Peinture metallisee",450.0f));
    v1.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
    cout << "---- v1 (avant affectation) --------------------" << endl;
    v1.display();
    {
        Car v2;
        cout << ">>>>> v2 = v1;" << endl;
        v2 = v1;
        cout << "---- v2 ----------------------------" << endl;
        v2.display();
        // Destruction de v2
    }
    cout << "---- v1 (apres affectation) -------------------------" << endl;
    v1.display();
    Pause();

    cout << endl << "***************************************************************" << endl;
    cout         << "(2) ***** Test de l'operateur + de Voiture ********************" << endl;
    cout         << "***************************************************************" << endl;
    Car v("Projet_208_MrDugenou",Model("208 Acces 3P 1.4 HDi",68,true,14600.0f)),v2;
    cout << "---- v (avant) --------------------------" << endl;
    v.display();
    {
        Option op("VD09","Vitres laterales arriere surteintees",150.0f);
        cout << ">>>>> v2 = v + op;" << endl;
        v2 = v + op;
        cout << ">>>>> v2 = v2 + Option(...Pack Cuir...);" << endl;
        v2 = v2 + Option("0P3U","Pack Cuir ambiance Mistral",1100.0f);
    }
    cout << "---- v (apres) --------------------------" << endl; // v ne doit pas etre modifie !!!!
    v.display();
    cout << "---- v2 (v + 2 options) ------------------------" << endl;
    v2.display();
    Pause();

    cout << endl << "*****************************************************************" << endl;
    cout <<         "(3) ***** Test des operateurs - de Voiture **********************" << endl;
    cout <<         "*****************************************************************" << endl;
    Car v3("Projet_3008_MrLegrand",Model("3008 Acces 1.6",120,false,21030.0f));
    v3 = v3 + Option("ZV02","Vision tete haute",350.0f);
    v3 = v3 + Option("OK01","Toit panoramique vitre",500.0f);
    v3 = v3 + Option("0MM0","Peinture metallisee",570.0f);
    cout << "----- v3 (avant) -----------------" << endl;
    v3.display();
    cout << "burp" << endl;
    v3 = v3 - Option("ZV02","Vision tete haute",350.0f);
    cout << "burp2" << endl;
    v3 = v3 - "0MM0";
    cout << "burp3" << endl;
    cout << "----- v3 (apres) ------------------" << endl;
    v3.display();

    return 0;
}


