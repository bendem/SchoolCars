#include <cstdlib>
#include <ctime>
#include <iostream>

#include "collections/SortedList.hpp"
#include "Person.hpp"

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

  exit(0);
}

int Menu()
{
  cout << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 6 (classe ListeTriee) ------------------------------------------------" << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << " 1. Test du template ListeTriee avec des entiers" << endl;
  cout << " 2. Test du template ListeTriee avec des objets de la classe Personne" << endl;
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
  cout << "----- 1. Test du template ListeTriee avec des entiers ------------------------" << endl;
  cout << "Creation  d'une Liste triee..." << endl;
  SortedList<int> liste;
  liste.display();                                       // --> ()
  cout << endl;

  cout << "On insere 3,-2,5,-1,0 et -8..." << endl;
  liste.add(3);
    liste.display(); cout << endl;
  liste.add(-2);
    liste.display(); cout << endl;
  liste.add(5);
    liste.display(); cout << endl;
  liste.add(-1);
    liste.display(); cout << endl;
  liste.add(0);
    liste.display(); cout << endl;
  liste.add(-8);
  liste.display();                                       // --> (-8 -2 -1 0 3 5)
  cout << "La liste contient " << liste.size() << " elements." << endl;
  cout << endl;
}

/*******************************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test du template ListeTriee avec des Personnes ------------------------" << endl;
  cout << "Creation  d'une Liste triee..." << endl;
  SortedList<Person> liste;
  liste.display();
  cout << endl;

  cout << "On insere quelques personnes..." << endl;
  liste.add(Person("Starzak","Richard"));
  liste.add(Person("Vilvens","Claude"));
  liste.add(Person("Mercenier","Denys"));
  liste.add(Person("Wagner","Jean-Marc"));
  liste.add(Person("Starzak","Luc"));
  liste.add(Person("Charlet","Christophe"));
  liste.add(Person("Moitroux","Cecile"));
  liste.display();
  cout << "La liste contient " << liste.size() << " elements." << endl;
  cout << endl;
}
