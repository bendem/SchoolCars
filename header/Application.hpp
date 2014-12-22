#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>

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
#include "predicates/IdPredicate.hpp"
#include "predicates/LoginPredicate.hpp"
#include "table/Table.hpp"
#include "utils/Logging.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Application {

private:
    SortedList<Employee> users;
    SortedList<Client> clients;
    List<Option> options;
    List<Model> models;
    Table optionTable;
    Table modelTable;
    SortedList<Contract> contracts;
    Employee* currentUser;
    Car* currentCar;
    bool carDirty;
    bool quitFlag;
    unsigned int userId;
    unsigned int clientId;
    unsigned int contractId;

public:
    Application();
    ~Application();

    void loadUsers(const String&);
    void defaultUsers();
    void saveUsers(const String&) const;
    void loadClients(const String&);
    void saveClients(const String&) const;
    void loadContracts(const String&);
    void saveContracts(const String&) const;
    void loadModels(const String&);
    void loadOptions(const String&);
    bool login(const String&, const String&);
    Employee& getCurrentUser() const;
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
