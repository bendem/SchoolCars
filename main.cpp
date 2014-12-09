#include <exception>
#include <fstream>
#include <iostream>

#include "Application.hpp"
#include "utils/FileUtils.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

#define USER_FILE "data/userlist.dat"
#define CLIENT_FILE "data/clients.dat"
#define OPTIONS_FILE "data/Options.csv"
#define MODELS_FILE "data/Modeles.csv"
#define CONTRACTS_FILE "data/contracts.dat"
#define APPLCATION_LOGS "application.log"

int main() {
    fstream x(APPLCATION_LOGS, ios::out | ios::trunc);
    streambuf* old = cerr.rdbuf(x.rdbuf());
    cerr << time << "Output redirected to " << APPLCATION_LOGS << endl;

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
    if(FileUtils::exists(USER_FILE)) {
        cerr << time << "Loading existing users" << endl;
        app.loadUsers(USER_FILE);
    } else {
        cerr << time << "Creating default users" << endl;
        app.defaultUsers();
    }

    if(FileUtils::exists(CLIENT_FILE)) {
        cerr << time << "Loading client file" << endl;
        app.loadClients(CLIENT_FILE);
    }

    if(FileUtils::exists(CONTRACTS_FILE)) {
        cerr << time << "Loading contract file" << endl;
        app.loadContracts(CONTRACTS_FILE);
    }

    Sanity::truthness(FileUtils::exists(OPTIONS_FILE), "Option file not found");
    app.loadOptions(OPTIONS_FILE);
    Sanity::truthness(FileUtils::exists(MODELS_FILE), "Model file not found");
    app.loadModels(MODELS_FILE);

    /* =================================================
     *            THE APPLICATION STARTS HERE
     * ================================================= */
    cerr << time << "Application loaded, starting user interaction" << endl;
    while(!app.login()) {
        cout << endl << " > Bad login, try again..." << endl << endl;
    }
    cout << endl << endl << " > Welcome " << app.getCurrentUser().getFirstname() << "!" << endl;

    while(!app.shouldQuit()) {
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        if(app.getCurrentUser().getFunction() == Employee::ADMINISTRATIVE) {
            adminMenu.display();
            adminMenu.choose(app);
        } else {
            sellerMenu.display();
            sellerMenu.choose(app);
        }
        cout << endl << " > Press a <ENTER> to continue";
        cin.get();
        cin.ignore();
    }
    /* =================================================
     *            THE APPLICATION ENDS HERE
     * ================================================= */

    cerr << time << "Application closing" << endl;
    cerr << time << "Saving users" << endl;
    app.saveUsers(USER_FILE);

    cerr << time << "Saving clients" << endl;
    app.saveClients(CLIENT_FILE);

    cerr << time << "Saving contracts" << endl;
    app.saveContracts(CONTRACTS_FILE);

    cerr << time << "Restoring cerr output" << endl;
    cerr.rdbuf(old);

    return 0;
}
