#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

#include "Person.hpp"
#include "utils/Comparable.hpp"
#include "utils/String.hpp"

using namespace std;

class Client : public Person, public Comparable<Client> {
private:
    int id;
    String address;

public:
    Client(String surname = "", String firstname = "", int id = 0, String address = "") :
        Person(surname, firstname), id(id), address(address) {}
    Client(const Client&);

    int getId() const;
    void setId(int id);

    const String& getAddress() const;
    void setAddress(const String&);

    String toString() const;

    int compareTo(const Client&) const;

    Client& operator=(const Client&);

    void load(istream&);
    void save(ostream&) const;

    friend istream& operator>>(istream&, Client&);
    friend ostream& operator<<(ostream&, const Client&);

};

#endif
