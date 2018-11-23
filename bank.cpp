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

    if (not sourceFile) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
    }

    string line;
    while (getline(sourceFile, line)) {
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


void Bank::saveToFile(Account& a)
{

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


bool Bank::checkIfAccountExists(long int& accountid)
{
    std::map<long int, Account>::iterator it;
    it = accounts_.find(accountid);

    bool accountExists = (it != accounts_.end());

    if (!accountExists) {
        std::cout << "Accout " << accountid << " Was Not Found." << std::endl;
        return false;
    } else {
        return true;
    }
}


void Bank::openAccount()
{
    string firstname, lastname;
    long double deposit;

    std::cout << "Give First Name: ";
    std::cin >> firstname;
    std::cout << "Give Last Name: ";
    std::cin >> lastname;
    std::cout << "Give Initial Deposit: ";
    std::cin >> deposit;
    std::cout << "" << std::endl;

    long int accountid = accountIdCounter_;
    ++accountIdCounter_;

    Account a(accountid, lastname, firstname, deposit);
    accounts_.insert(std::make_pair(a.getAccountID(), a));

    std::cout << "\nCongratulations, New Account is Now Created!\n" 
              << std::endl;

    printAccountInfo(a);

    // TODO
    //saveToFile(a);
}


void Bank::closeAnAccount()
{

}


void Bank::getAccountBalance()
{
    long int userInput;
    std::cout << "Enter Your Account ID: ";
    std::cin >> userInput;
    std::cout << "" << std::endl;

    std::map<long int, Account>::iterator it;
    it = accounts_.find(userInput);

    if (it != accounts_.end()) {
        std::cout << "Account " << userInput << "\n" 
                  << "Total Balance: "
                  << accounts_.find(userInput)->second.getAccountBalance() 
                  << std::endl;
    } else {
        std::cout << "No Account Found With Suggested ID.\n";
    }
}


void Bank::depositToAccount()
{
    long int sourceAccount;
    std::cout << "Enter the Account ID Where to Deposit From: ";
    std::cin >> sourceAccount;
    bool validSource = checkIfAccountExists(sourceAccount);
    if (!validSource) return;

    long int destinationAccount;
    std::cout << "Enter the Account ID Where to Deposit: ";
    std::cin >> destinationAccount;
    bool validDestination = checkIfAccountExists(destinationAccount);
    if (!validDestination) return;

    long double transferredSum;
    std::cout << "Enter the Amount to Transfer: ";
    std::cin >> transferredSum;

    std::cout << "" << std::endl;

    Account source = accounts_.find(sourceAccount)->second;
    Account destination = accounts_.find(destinationAccount)->second;

    long double sourceBalance = source.getAccountBalance();

    if (sourceBalance < transferredSum) {
        std::cout << "Source Account Balance Not High Enough to Make the Transfer."
                  << std::endl;
    } else {
        source.transferFromAccount(transferredSum);
        destination.transferToAccount(transferredSum);
    }

}


void Bank::doAccountWithDrawal()
{

}


void Bank::printAccountInfo(Account& account)
{
    std::cout << "First Name: " << account.getFirstName() << std::endl;
    std::cout << "Last Name: " << account.getLastName() << std::endl;
    std::cout << "Account ID: " << account.getAccountID() << std::endl;
    std::cout << "Account Balance: " << account.getAccountBalance() << std::endl;
    std::cout << "" << std::endl;
}


void Bank::showAllAccounts()
{
    int counter = 1;
    for (auto account : accounts_) {
        std::cout << "Account " << counter << std::endl;
        printAccountInfo(account.second);
        counter++;
    }
}
