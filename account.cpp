#include "account.h"
#include <iostream>


using std::string;


Account::Account(long int id, string lastname, string firstname, long double balance)
{
    accountID_ = id;
    accountHolderLastName_ = lastname;
    accountHolderFirstName_ = firstname;
    accountBalance_ = balance;
}

long int Account::getAccountID()
{
    return accountID_;
}

string Account::getFirstName()
{
    return accountHolderFirstName_;
}

string Account::getLastName()
{
    return accountHolderLastName_;
}

long double Account::getAccountBalance()
{
    return accountBalance_;
}

void Account::transferFromAccount(long double& amount)
{
    accountBalance_ -= amount;
}

void Account::transferToAccount(long double& amount)
{
    accountBalance_ += amount;
}