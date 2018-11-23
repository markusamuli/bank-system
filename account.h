// Each account contains information about the owner and the deposited money

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using std::string;

class Account
{
public:
    Account(long int id, string lastname, string firstname, long double balance);
    long int getAccountID();
    std::string getFirstName();
    std::string getLastName();
    long double getAccountBalance();
    void transferFromAccount(long double& amount);
    void transferToAccount(long double& amount);
private:
    long int accountID_;
    string accountHolderFirstName_;
    string accountHolderLastName_;
    long double accountBalance_;
};

#endif // ACCOUNT_H
