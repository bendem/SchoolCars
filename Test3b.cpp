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
  cout << "***** Test des op�rateurs < > == de Voiture **************************" << endl;
  cout << "**********************************************************************" << endl;

  Car v1("Projet1_208_MrDugenou",Model("208 Acces 3P 1.4 HDi",68,true,14600.0f));
  v1.addOption(Option("0MM0","Peinture metallisee",450.0f));
  cout << "---- Projet 1 --------------------" << endl;
  v1.display();
  cout << "Prix du projet 1 = " << v1.getPrice() << " euros" << endl << endl;

  Car v2("Projet2_208_MrDugenou",Model("208 Acces 5P 1.2",82,false,13500.0f));
  v2 = v2 + Option("0MM0","Peinture metallisee",450.0f);
  v2 = v2 + Option("ZH75","Jante alliage leger 15 pouces",450.0f);
  cout << "---- Projet 2 --------------------" << endl;
  v2.display();
  cout << "Prix du projet 2 = " << v2.getPrice() << " euros" << endl << endl;

  cout << "---- Comparaison des projets -------------------" << endl;
  if (v1 < v2) cout << "Le projet 1 est moins cher" << endl;
  if (v1 > v2) cout << "Le projet 1 est plus cher" << endl;
  if (v1 == v2) cout << "Les deux projets ont le meme prix" << endl;

  return 0;
}


