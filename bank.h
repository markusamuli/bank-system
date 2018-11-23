// Banks include different accounts that have their unique identifiers

#ifndef BANK_H
#define BANK_H

#include "account.h"
#include <map>
#include <vector>
#include <string>
#include "account.h"

using std::string;
using std::vector;


class Bank
{
public:
    Bank();
    void readFileData();
    void saveToFile(Account& a);
    vector<string> splitLines(const string &line, const char delimiter);
    void loadAccounts(std::map<string, vector<string>>& accountData);
    bool checkIfAccountExists(long int& accountid);
    void openAccount();
    void closeAnAccount();
    void getAccountBalance();
    void depositToAccount();
    void doAccountWithDrawal();
    void printAccountInfo(Account& account);
    void showAllAccounts();
private:
    std::map<long int, Account> accounts_;
    long int accountIdCounter_ = 1000;
};

#endif // BANK_H
