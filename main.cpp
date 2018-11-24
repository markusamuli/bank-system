#include <iostream>
#include "bank.h"


void printOptions() {
    std::cout << "Select a wanted option:" << std::endl;
    std::cout << "1 Open an Account" << std::endl;
    std::cout << "2 Balance Enquiry" << std::endl;
    std::cout << "3 Do Transfer to Another Account" << std::endl;
    std::cout << "4 Deposit" << std::endl;
    std::cout << "5 Withdrawal" << std::endl;
    std::cout << "6 Close an Account" << std::endl;
    std::cout << "7 Show All Accounts" << std::endl;
    std::cout << "8 Quit" << std::endl;
    std::cout << "" << std::endl;
}


int main()
{

    std::cout << "\n===== Welcome to the Bank =====\n\n" << std::endl;

    Bank bank;
    bool keepWorking = true;

    while (keepWorking)
    {
        printOptions();

        char optionSelection;
        std::cout << "Enter your option: ";
        std::cin >> optionSelection;
        std::cout << "" << std::endl;

        switch (optionSelection)
        {
           case '1':
            bank.openAccount();
            break;
           case '2':
            bank.checkAccountBalance();
            break;
           case '3':
            bank.doAccountTransfer();
            break;
           case '4':
            bank.doAccountDeposit();
            break;
           case '5':
            bank.doAccountWithDrawal();
            break;
           case '6':
            bank.closeAnAccount();
            break;
           case '7':
            bank.showAllAccounts();
            break;
           case '8':
            std::cout << "See You Again!" << std::endl;
            keepWorking = false;
            break;
        }
        std::cout << "" << std::endl;
    }
    return 0;
}
