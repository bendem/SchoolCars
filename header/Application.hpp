#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>

#include "Car.hpp"
#include "Client.hpp"
#include "Employee.hpp"
#include "collections/SortedList.hpp"
#include "menu/Menu.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Application {

private:
    SortedList<Employee>* users;
    SortedList<Client>* clients;
    Employee* currentUser;
    Car* currentCar;
    bool quitFlag;

public:
    Application();
    ~Application();

    void loadUsers(const String&);
    void defaultUsers();
    void saveUsers(const String&) const;
    void loadClients(const String&);
    void saveClients(const String&) const;
    bool login();
    void logout();
    bool isUserLoggedin() const;
    Employee& getCurrentUser() const;
    bool isThereACarAtTheMomemnt() const ;
    Car& getCurrentCar() const;
    bool shouldQuit() const;

    // common menu actions
    void dummy() { cout << "dummy" << endl; };
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
