#include <iostream>
#include "Model.hpp"
#include "Option.hpp"
#include "Car.hpp"

using namespace std;

int main()
{
  cout << "**********************************************************************" << endl;
  cout << "(1) ***** Test des op�rateurs << et >> de Modele *********************" << endl;
  cout << "**********************************************************************" << endl;
  Model m;
  cout << "Saisissez un nouveau modele :" << endl;
  cin >> m;
  cout << endl << "Voici le modele que vous avez encode :" << endl;
  cout << m << endl << endl;

  cout << "**********************************************************************" << endl;
  cout << "(2) ***** Test des op�rateurs << et >> de Option *********************" << endl;
  cout << "**********************************************************************" << endl;
  Option o;
  cout << "Saisissez une nouvelle option :" << endl;
  cin >> o;
  cout << endl << "Voici l'option que vous avez encodee :" << endl;
  cout << o << endl << endl;

  cout << "**********************************************************************" << endl;
  cout << "(3) ***** Test des op�rateurs << et >> de Voiture ********************" << endl;
  cout << "**********************************************************************" << endl;
  Car v;
  cout << "Saisissez un nouveau projet de Voiture :" << endl;
  cin >> v;
  cout << endl << "Combien d'options voulez-vous ajouter ? " ;
  int nb;
  cin >> nb;
  cin.ignore();
  for(int i=0 ; i<nb ; i++)
  {
    Option op;
    cout << endl << "Encodez l'option no " << (i+1) << " : " << endl;
    cin >> op;
    v = v + op;
  }
  cout << endl << "Voici le projet de Voiture que vous avez encode :" << endl;
  cout << v << endl;

  return 0;
}


