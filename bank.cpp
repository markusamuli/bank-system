#include <iostream>
#include "bank.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>


using std::string;
using std::vector;
using std::ifstream;


Bank::Bank()
{
    readFileData();
}


vector<string> Bank::splitLines(const string& line, const char delimiter)
{
    vector<string> result;
    string tmp = line;

    while (tmp.find(delimiter) != string::npos) {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if (not new_part.empty()) {
            result.push_back(new_part);
        }
    }

    if (not tmp.empty()) {
        result.push_back(tmp);
    }

    return result;
}


void Bank::readFileData()
{
    std::map<string, vector<string>> data;

    ifstream sourceFile("accounts.txt");

    if ( not sourceFile ) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
    }

    string line;
    while ( getline(sourceFile, line) ) {
        std::vector<string> lineParts = splitLines(line, ';');
        string id = lineParts.at(0);
        string lastName = lineParts.at(1);
        string firstName = lineParts.at(2);
        string balance = lineParts.at(3);

        std::vector<string> vec_vals = {lastName, firstName, balance};
        data.insert(std::make_pair(id, vec_vals));

    }

    loadAccounts(data);
}


void Bank::loadAccounts(std::map<string, vector<string>>& accountData)
{
    for (auto account : accountData) {
        long int id = std::stol(account.first);
        string lastName = account.second.at(0);
        string firstName = account.second.at(1);
        long double balance = std::stold(account.second.at(2));

        Account a(id, lastName, firstName, balance);
        accounts_.insert(std::make_pair(a.getAccountID(), a));
    }
}


void Bank::openAccount()
{

}


void Bank::getAccountBalance()
{

}


void Bank::depositToAccount()
{

}


void Bank::doAccountWithDrawal()
{

}


void Bank::showAllAccounts()
{
    int counter = 1;
    for (auto account : accounts_) {
        std::cout << "Account " << counter << std::endl;
        std::cout << "First Name: " << account.second.getFirstName() << std::endl;
        std::cout << "Last Name: " << account.second.getLastName() << std::endl;
        std::cout << "Account ID: " << account.second.getAccountID() << std::endl;
        std::cout << "Account Balance: " << account.second.getAccountBalance() << std::endl;
        std::cout << "" << std::endl;
        counter++;
    }
}
