#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>

#include "auth/Authenticator.hpp"
#include "Car.hpp"
#include "Client.hpp"
#include "Contract.hpp"
#include "Employee.hpp"
#include "Model.hpp"
#include "Option.hpp"
#include "collections/List.hpp"
#include "collections/SortedList.hpp"
#include "exceptions/IOException.hpp"
#include "formatters/CarFormatter.hpp"
#include "formatters/ContractFormatter.hpp"
#include "formatters/EmployeeFormatter.hpp"
#include "menu/Menu.hpp"
#include "menu/MenuEntry.hpp"
#include "predicates/ClientIdPredicate.hpp"
#include "predicates/CodePredicate.hpp"
#include "predicates/FirstnamePredicate.hpp"
#include "predicates/IdPredicate.hpp"
#include "table/Table.hpp"
#include "utils/Logging.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Application {

private:

    static const String DATA_FOLDER;
    static const String USER_FILE;
    static const String CLIENT_FILE;
    static const String OPTION_FILE;
    static const String MODEL_FILE;
    static const String CONTRACT_FILE;

    SortedList<Employee> users;
    SortedList<Client> clients;
    List<Option> options;
    List<Model> models;
    Table optionTable;
    Table modelTable;
    SortedList<Contract> contracts;
    Car* currentCar;
    Authenticator authenticator;
    bool carDirty;
    bool quitFlag;
    bool loaded;
    unsigned int userId;
    unsigned int clientId;
    unsigned int contractId;

    void loadUsers();
    void defaultUsers();
    void saveUsers() const;
    void loadClients();
    void saveClients() const;
    void loadContracts();
    void saveContracts() const;
    void loadModels();
    void loadOptions();

public:
    Application();
    ~Application();

    void load();
    void save();

    bool login(const String&, const String&);
    Employee& getCurrentUser();
    bool shouldQuit() const;

    // common menu actions
    void changePassword();
    void quit();

    // Admin menu actions
    void displayUsers();
    void displayUser();
    void createUser();
    void resetPassword();
    void displayContracts();
    void displayContract(); // Duplicated in seller menu?
    void displaySellerContracts();

    // Seller menu actions
    void createClient();
    void removeClient();
    void displayClients();
    void displayModels();
    void displayOptions();
    void createCar();
    void loadCar();
    void displayCurrentCar();
    void addOptionToCurrentCar();
    void removeOptionFromCurrentCar();
    void applyDiscountToCurrentCar();
    void saveCurrentCar();
    void newContract();
    void displayContractsForCurrentUser();
    void modifyContract();

};

#endif
