#include <iostream>

#include "Option.hpp"

using namespace std;

// Tests de la classe Option seule

int main()
{
    cout << "(1) ***** Test du constructeur par defaut de Option *****" << endl;
    {
        Option option;
        option.display();
    }

    cout << endl << "(2) **** Test des setters/getters *****" << endl;
    {
        Option option;
        option.setCode("0MM0");
        option.setName("Peinture metallisee");
        option.setPrice(450.0f);
        option.display();
    }

    cout << endl << "(3) ***** Test du constructeur d'initialisation de Option *****" << endl;
    {
        Option option("ZH75","Jante alliage leger 15 pouces",450.0f);
        option.display();
    }

    cout << endl << "(4) ***** Test du constructeur de copie de Option *****" << endl;
    {
        Option option1("UB01","Detecteur obstacles arriere",250.0f);
        cout << "option1 (AVANT) :" << endl;
        option1.display();
        {
            Option option2(option1);
            cout << "option2 :" << endl;
            option2.display();
            option2.setPrice(300.0f);
            option2.display();
        }
        cout << "option1 (APRES) :" << endl;
        option1.display();
    }

    return 0;
}


