#include <iostream>
#include "bank.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>


using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


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
    ofstream outputFile ("accounts.txt", std::ios_base::app);

    string line;

    if (outputFile.is_open()) {
        string id = std::to_string(a.getAccountID());
        string lastName = a.getLastName();
        string firstName = a.getFirstName();
        string balance = std::to_string(a.getAccountBalance());

        outputFile << id << ';'
                   << lastName << ';'
                   << firstName << ';'
                   << balance << "\n";

        outputFile.close();
    }
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

    long int largestID = accounts_.rbegin()->first;
    accountIdCounter_ = ++largestID;
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

    saveToFile(a);

    std::cout << "\nCongratulations, New Account is Now Created!\n" 
              << std::endl;

    printAccountInfo(a);
}


void Bank::closeAnAccount()
{
    long int accountid;
    std::cout << "Enter Account ID That You Want to Close: ";
    std::cin >> accountid;

    bool validDestination = checkIfAccountExists(accountid);

    if (!validDestination) {
        return;
    } else {
        std::map<long int, Account>::iterator it;
        it = accounts_.find(accountid);

        accounts_.erase(it->first);
        std::cout << "Account is now removed." << std::endl;
    }
}


void Bank::checkAccountBalance()
{
    long int accountid;
    std::cout << "Enter Your Account ID: ";
    std::cin >> accountid;
    std::cout << "" << std::endl;

    bool validDestination = checkIfAccountExists(accountid);

    if (!validDestination) {
        return;
    } else {
        std::map<long int, Account>::iterator it;
        it = accounts_.find(accountid);

        std::cout << "Account " << accountid << "\n"
                  << "Total Balance: "
                  << accounts_.find(accountid)->second.getAccountBalance()
                  << std::endl;
    }
}


void Bank::doAccountTransfer()
{
    long int sourceAccount, destinationAccount;
    long double transferredSum;

    std::cout << "Enter the Account ID Where to Deposit From: ";
    std::cin >> sourceAccount;
    bool validSource = checkIfAccountExists(sourceAccount);
    if (!validSource) return;

    std::cout << "Enter the Account ID Where to Deposit: ";
    std::cin >> destinationAccount;
    bool validDestination = checkIfAccountExists(destinationAccount);
    if (!validDestination) return;

    std::cout << "Enter the Amount to Transfer: ";
    std::cin >> transferredSum;

    std::cout << "" << std::endl;

    Account& source = accounts_.find(sourceAccount)->second;
    Account& destination = accounts_.find(destinationAccount)->second;

    long double sourceBalance = source.getAccountBalance();

    if (sourceBalance < transferredSum) {
        std::cout << "Source Account Balance Not High Enough to Make the Transfer."
                  << std::endl;
    } else {
        source.transferFromAccount(transferredSum);
        destination.transferToAccount(transferredSum);
    }
}


void Bank::doAccountDeposit()
{
    long int accountid;
    long double amount;

    std::cout << "Enter the Account ID Where to Deposit: ";
    std::cin >> accountid;

    bool validDestination = checkIfAccountExists(accountid);

    if (!validDestination) {
        return;
    } else {
        std::cout << "Enter the Deposited Amount: ";
        std::cin >> amount;

        Account& account = accounts_.find(accountid)->second;
        account.transferToAccount(amount);

        std::cout << amount << " Has Been Deposited to Your Account." << std::endl;
        std::cout << "Total Balance After Deposit: " <<
                     account.getAccountBalance() << std::endl;
    }
}


void Bank::doAccountWithDrawal()
{
    long int accountid;
    long double amount;

    std::cout << "Enter the Account ID Where to Withdraw: ";
    std::cin >> accountid;

    bool validDestination = checkIfAccountExists(accountid);

    if (!validDestination) {
        return;
    } else {
        std::cout << "Enter the Withdrawn Amount: ";
        std::cin >> amount;

        Account& account = accounts_.find(accountid)->second;
        long double balance = account.getAccountBalance();

        if (balance >= amount) {
            account.transferFromAccount(amount);

            std::cout << amount << " Has Been Withdrawn from Your Account." << std::endl;
            std::cout << "Total Balance After Withdraw: " <<
                         account.getAccountBalance() << std::endl;
        } else {
            std::cout << "\nBalance Not High Enough to Make Suggested Withdrawal."
                      << std::endl;
        }
    }
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
