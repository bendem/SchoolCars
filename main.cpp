#include <exception>
#include <fstream>
#include <iostream>

#include "Application.hpp"
#include "utils/Logging.hpp"
#include "utils/FileUtils.hpp"

using namespace std;

#define APPLCATION_LOGS "application.log"

int main(int argc, char** argv) {
    fstream x(APPLCATION_LOGS, ios::out | ios::trunc);
    streambuf* old = cerr.rdbuf(x.rdbuf());
    cerr << time("main") << "Output redirected to " << APPLCATION_LOGS << endl;

    cerr << time("main") << "Parsing arguments" << endl;
    String login, password;
    bool useArrowsForMenus = false;
    for (int i = 1; i < argc; ++i) {
        String param(argv[i]);
        if(param == String("-h")) {
            cout
                << endl
                << " Parameters are" << endl
                << " '-u <string:username>' used with '-p <string:password>' to use the autologin feature" << endl
                << " '-m <boolean:use arrows in menus>' to enable the arrow browsable menus" << endl
                << endl;
            return 0;
        } else if(param == String("-u") && i+1 != argc) {
            login = argv[++i];
        } else if(param == String("-p") && i+1 != argc) {
            password = argv[++i];
        } else if(param == String("-m") && i+1 != argc) {
            useArrowsForMenus = String(argv[++i]).toBool();
        }
    }
    cerr << time("main") << "Running application with "
        << "user: '" << login << "', "
        << "password: '" << String('*', password.length()) << "', "
        << "useArrowsForMenus: " << useArrowsForMenus << endl;

    Application app;

    cerr << time("main") << "Creating admin menu" << endl;
    // Preparing menus
    Menu<Application> adminMenu("Menu Admin", useArrowsForMenus);
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

    cerr << time("main") << "Creating seller menu" << endl;
    Menu<Application> sellerMenu("Menu Vendeur", useArrowsForMenus);
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
        .addEntry("9",  "Ajouter une option a la voiture en cours", &Application::addOptionToCurrentCar)
        .addEntry("10", "Retirer une option a la voiture en cours", &Application::removeOptionFromCurrentCar)
        .addEntry("11", "Appliquer une ristourne a une option de la voiture en cours", &Application::applyDiscountToCurrentCar)
        .addEntry("12", "Enregistrer la voiture en cours", &Application::saveCurrentCar)
        .addEntry("-",  "Gerer les projets de voiture", NULL)
        .addEntry("13", "Nouveau contrat", &Application::newContract)
        .addEntry("14", "Afficher tous mes contrats", &Application::displayContractsForCurrentUser)
        .addEntry("15", "Afficher un contrat et le prix de vente definitif", &Application::displayContract)
        .addEntry("16", "Modifier un contrat", &Application::modifyContract)
        .addEntry("Q",  "Quitter l'application", &Application::quit);

    cerr << time("main") << "Application starting" << endl;
    app.load();

    /* =================================================
     *            THE APPLICATION STARTS HERE
     * ================================================= */
    cerr << time("main") << "Application loaded, starting user interaction" << endl;
    while(!app.login(login, password)) {
        cout << " > Bad login, try again..." << endl << endl;
    }
    cout << endl << endl
        << "               _____\n"
        << "      _-_-  _/\\______\\\\__\n"
        << "   _-_-__  / ,-. -|-  ,-.`-.\n"
        << "      _-_- `( o )----( o )-'\n"
        << "             `-'      `-'";
    cout << endl << endl << " > Welcome " << green << app.getCurrentUser().getFirstname() << reset << "!" << endl;
    {
        cout << endl << " > Press <ENTER> to continue";
        String throwItOnTheGround;
        cin >> throwItOnTheGround;
    }

    while(!app.shouldQuit()) {
        if(app.getCurrentUser().getFunction() == Employee::ADMINISTRATIVE) {
            adminMenu.display();
            adminMenu.choose(app);
        } else {
            sellerMenu.display();
            sellerMenu.choose(app);
        }
        cout << endl << " > Press <ENTER> to continue";
        String throwItOnTheGround;
        cin >> throwItOnTheGround;
        cout << endl;
    }
    /* =================================================
     *            THE APPLICATION ENDS HERE
     * ================================================= */

    cerr << time("main") << "Application closing" << endl;
    app.save();

    cerr << time("main") << "Restoring cerr output" << endl;
    cerr.rdbuf(old);

    return 0;
}
