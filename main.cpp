#include <exception>
#include <fstream>
#include <iostream>

#include "Application.hpp"
#include "utils/FileUtils.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

#define USERFILE "data/userlist.dat"
#define APPLCATIONLOGS "application.log"

int main() {
    fstream x(APPLCATIONLOGS, ios::out | ios::trunc);
    streambuf* old = cerr.rdbuf(x.rdbuf());
    cerr << time << "Output redirected to " << APPLCATIONLOGS << endl;

    Application app;

    cerr << time << "Creating admin menu" << endl;
    // Preparing menus
    Menu<Application> adminMenu("Menu Admin");
    adminMenu
        .addEntry("0", "Changer de mot de passe", &Application::changePassword)
        .addEntry("-", "Gestion des utilisateurs", NULL)
        .addEntry("1", "Afficher la liste des utilisateurs", &Application::displayUserSummary)
        .addEntry("2", "Afficher les infos d'un utilisateur", &Application::displayUser)
        .addEntry("3", "Creer un nouvel utilisateur", &Application::createUser)
        .addEntry("4", "Reinitialiser le mot de passe d'un utilisateur", &Application::resetPassword)
        .addEntry("-", "Gestion des contrats", NULL)
        .addEntry("5", "Afficher tous les contrats", &Application::dummy)
        .addEntry("6", "Afficher les details d'un contrat", &Application::dummy)
        .addEntry("7", "Afficher les contrats et le chiffre d'affaire d'un vendeur", &Application::dummy)
        .addEntry("Q", "Quitter l'application", &Application::quit);

    cerr << time << "Creating seller menu" << endl;
    Menu<Application> sellerMenu("Menu Vendeur");
    sellerMenu
        .addEntry("0",  "Changer de mot de passe", &Application::changePassword)
        .addEntry("-",  "Gerer les clients", NULL)
        .addEntry("1",  "Ajouter un nouveau client", &Application::dummy)
        .addEntry("2",  "Supprimer un client", &Application::dummy)
        .addEntry("3",  "Afficher la liste des clients", &Application::dummy)
        .addEntry("-",  "Gerer les projets de voiture", NULL)
        .addEntry("4",  "Afficher la liste des modeles", &Application::dummy)
        .addEntry("5",  "Afficher la liste des options", &Application::dummy)
        .addEntry("6",  "Nouvelle Voiture", &Application::dummy)
        .addEntry("7",  "Charger une voiture", &Application::dummy)
        .addEntry("8",  "Afficher la voiture en cours", &Application::dummy)
        .addEntry("9",  "Ajouter une option à la voiture en cours", &Application::dummy)
        .addEntry("10", "Retirer une option à la voiture en cours", &Application::dummy)
        .addEntry("11", "Appliquer une ristourne à une option de la voiture en cours", &Application::dummy)
        .addEntry("12", "Enregistrer la voiture en cours", &Application::dummy)
        .addEntry("-",  "Gerer les projets de voiture", NULL)
        .addEntry("13", "Nouveau contrat", &Application::dummy)
        .addEntry("14", "Afficher tous mes contrats", &Application::dummy)
        .addEntry("15", "Afficher un contrat et le prix de vente definitif", &Application::dummy)
        .addEntry("16", "Modifier un contrat", &Application::dummy)
        .addEntry("Q",  "Quitter l'application", &Application::quit);

    cerr << time << "Application starting" << endl;
    if(FileUtils::exists(USERFILE)) {
        cerr << time << "Loading existing users" << endl;
        app.loadUsers(USERFILE);
    } else {
        cerr << time << "Creating default users" << endl;
        app.defaultUsers();
    }

    /* =================================================
     *            THE APPLICATION STARTS HERE
     * ================================================= */
    cerr << time << "Application loaded, starting user interaction" << endl;
    while(!app.login()) {
        cout << endl << "> Bad login, try again..." << endl << endl;
    }
    cout << endl << endl << "> Welcome " << app.getCurrentUser().getFirstname() << "!" << endl;

    while(!app.shouldQuit()) {
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        if(app.getCurrentUser().getFunction() == Employee::ADMINISTRATIVE) {
            adminMenu.display();
            adminMenu.choose(app);
        } else {
            sellerMenu.display();
            sellerMenu.choose(app);
        }
        cout << endl << "> Press a <ENTER> to continue";
        cin.get();
        cin.ignore();
    }
    /* =================================================
     *            THE APPLICATION ENDS HERE
     * ================================================= */

    cerr << time << "Application closing, saving users" << endl;
    app.saveUsers(USERFILE);

    cerr << time << "Restoring cerr output" << endl;
    cerr.rdbuf(old);

    return 0;
}
