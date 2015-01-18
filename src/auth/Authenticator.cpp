#include <utils/TermUtils.hpp>
#include "auth/Authenticator.hpp"

Authenticator::Authenticator() {
    this->currentUser = NULL;
}

bool Authenticator::quickLogin(const String& providedLogin, const String& providedPassword, List<Employee>& users) {
    // Quick arg login (useful for debug)
    if(providedLogin.length() != 0 && providedPassword.length() != 0) {
        Optional<Employee> opt = users.getFirstMatching(LoginPredicate(providedLogin));
        if(opt.hasValue() && opt.get().getPassword() == providedPassword) {
            this->currentUser = &opt.get();
            return true;
        }
    }
    return false;
}

bool Authenticator::login(List<Employee>& users) {
    String username, password;

    cout << "    ========================" << endl;
    cout << "    =        Login         =" << endl;
    cout << "    ========================" << endl << endl;
    cout << "    Entrez votre nom d'utilisateur: ";
    cin >> username;
    cout << endl;

    Optional<Employee> optEmployee = users.getFirstMatching(LoginPredicate(username));
    if(!optEmployee.hasValue()) {
        cout << " > User not found" << endl;
        return false;
    }

    // Password not set
    if(optEmployee.get().getPassword().length() == 0) {
        cerr << time("Authenticator::login") << "Found user without password, logging in and asking password" << endl;
        this->currentUser = &optEmployee.get();
        String newPassword;
        String confirmation;
        while(true) {
            cout << endl << "    404 password not found, enter a new one: ";
            TermUtils::setEchoInput(false);
            cin >> newPassword;
            cout << "    Confirm your password: ";
            cin >> confirmation;
            TermUtils::setEchoInput(true);
            if(newPassword != confirmation) {
                cout << " > Passwords don't match, try again" << endl;
                continue;
            }
            try {
                this->currentUser->setPassword(newPassword);
            } catch(InvalidPasswordException e) {
                cout << " > " << e.what() << ", try again" << endl;
                continue;
            }
            break;
        }
        return true;
    }

    cout << "    Entrez votre mot de passe: ";
    TermUtils::setEchoInput(false);
    cin >> password;
    cout << endl;
    TermUtils::setEchoInput(true);

    // Correct password
    if(optEmployee.get().getPassword() == password) {
        cerr << time("Authenticator::login") << "Found correct user, logging in" << endl;
        this->currentUser = &optEmployee.get();
        return true;
    }

    cerr << time("Authenticator::login") << "Found user (" << optEmployee.get().getLogin() << ") with wrong password" << endl;
    return false;
}

void Authenticator::changePassword() {
    String current, newPassword, confirmation;

    cout << "    Type your current password: ";
    TermUtils::setEchoInput(false);
    cin >> current;
    cout << endl;
    TermUtils::setEchoInput(true);
    if(this->currentUser->getPassword() != current) {
        cout << " > Incorrect password" << endl;
        return;
    }

    TermUtils::setEchoInput(false);
    cout << "    Type your new password: ";
    cin >> newPassword;
    cout << endl;
    cout << "    Confirm your password: ";
    cin >> confirmation;
    cout << endl;
    TermUtils::setEchoInput(true);

    if(newPassword != confirmation) {
        cout << " > Passwords do not match!" << endl;
        return;
    }

    try {
        this->currentUser->setPassword(newPassword);
    } catch(InvalidPasswordException e) {
        cout << e.what() << endl;
        return;
    }
    cout << " > Password changed" << endl;
}

void Authenticator::resetPassword(List<Employee>& users) {
    String username;
    cout << "    Enter the login of the user you want to reset the pwd for: ";
    cin >> username;
    if(username.length() == 0) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = users.getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        opt.get().resetPassword();
        cout << " > " << username << "'s password has been reset" << endl;
    } else {
        cout << " > User not found :(" << endl;
    }
}

Employee& Authenticator::getCurrentUser() {
    Sanity::nullness(this->currentUser, "No user logged in");

    return *this->currentUser;
}
