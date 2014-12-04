#include <exception>
#include <fstream>
#include <iostream>

#include "Application.hpp"
#include "utils/FileUtils.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

#define USERFILE "data/userlist.dat"
#define CLIENTFILE "data/clients.dat"
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
        .addEntry("1", "Afficher la liste des utilisateurs", &Application::displayUsers)
        .addEntry("2", "Afficher les infos d'un utilisateur", &Application::displayUser)
        .addEntry("3", "Creer un nouvel utilisateur", &Application::createUser)
        .addEntry("4", "Reinitialiser le mot de passe d'un utilisateur", &Application::resetPassword)
        .addEntry("-", "Gestion des contrats", NULL)
        .addEntry("5", "Afficher tous les contrats", &Application::displayContracts)
        .addEntry("6", "Afficher les details d'un contrat", &Application::displayContract)
        .addEntry("7", "Afficher les contrats et le chiffre d'affaire d'un vendeur", &Application::displaySellerContracts)
        .addEntry("Q", "Quitter l'application", &Application::quit);

    cerr << time << "Creating seller menu" << endl;
    Menu<Application> sellerMenu("Menu Vendeur");
    sellerMenu
        .addEntry("0",  "Changer de mot de passe", &Application::changePassword)
        .addEntry("-",  "Gerer les clients", NULL)
        .addEntry("1",  "Ajouter un nouveau client", &Application::createClient)
        .addEntry("2",  "Supprimer un client", &Application::removeClient)
        .addEntry("3",  "Afficher la liste des clients", &Application::displayClients)
        .addEntry("-",  "Gerer les projets de voiture", NULL)
        .addEntry("4",  "Afficher la liste des modeles", &Application::displayModels)
        .addEntry("5",  "Afficher la liste des options", &Application::displayOptions)
        .addEntry("6",  "Nouvelle Voiture", &Application::createCar)
        .addEntry("7",  "Charger une voiture", &Application::loadCar)
        .addEntry("8",  "Afficher la voiture en cours", &Application::displayCurrentCar)
        .addEntry("9",  "Ajouter une option à la voiture en cours", &Application::addOptionToCurrentCar)
        .addEntry("10", "Retirer une option à la voiture en cours", &Application::removeOptionFromCurrentCar)
        .addEntry("11", "Appliquer une ristourne à une option de la voiture en cours", &Application::applyDiscountToCurrentCar)
        .addEntry("12", "Enregistrer la voiture en cours", &Application::saveCurrentCar)
        .addEntry("-",  "Gerer les projets de voiture", NULL)
        .addEntry("13", "Nouveau contrat", &Application::newContract)
        .addEntry("14", "Afficher tous mes contrats", &Application::displayContractsForCurrentUser)
        .addEntry("15", "Afficher un contrat et le prix de vente definitif", &Application::displayContract)
        .addEntry("16", "Modifier un contrat", &Application::modifyContract)
        .addEntry("Q",  "Quitter l'application", &Application::quit);

    cerr << time << "Application starting" << endl;
    if(FileUtils::exists(USERFILE)) {
        cerr << time << "Loading existing users" << endl;
        app.loadUsers(USERFILE);
    } else {
        cerr << time << "Creating default users" << endl;
        app.defaultUsers();
    }

    if(FileUtils::exists(CLIENTFILE)) {
        cerr << time << "Loading client file" << endl;
        app.loadClients(CLIENTFILE);
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

    cerr << time << "Application closing" << endl;
    cerr << time << "Saving users" << endl;
    app.saveUsers(USERFILE);

    cerr << time << "Saving clients" << endl;
    app.saveClients(CLIENTFILE);

    cerr << time << "Restoring cerr output" << endl;
    cerr.rdbuf(old);

    return 0;
}
