// Banks include different accounts that have their unique identifiers

#ifndef BANK_H
#define BANK_H

#include "account.h"
#include <map>
#include <vector>
#include <string>
#include "account.h"


class Bank
{
public:
    Bank();
    void readFileData();
    std::vector<string> splitLines(const std::string &line, const char delimiter);
    void loadAccounts(std::map<std::string, std::vector<std::string>>& accountData);
    void openAccount();
    void getAccountBalance();
    void depositToAccount();
    void doAccountWithDrawal();
    void showAllAccounts();
private:
    std::map<long int, Account> accounts_;
};

#endif // BANK_H
