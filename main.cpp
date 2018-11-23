#include <iostream>
#include "bank.h"


void printOptions() {
    std::cout << "Select a wanted option:" << std::endl;
    std::cout << "1 Open an Account" << std::endl;
    std::cout << "2 Balance Enquiry" << std::endl;
    std::cout << "3 Deposit" << std::endl;
    std::cout << "4 Withdrawal" << std::endl;
    std::cout << "5 Close an Account" << std::endl;
    std::cout << "6 Show All Accounts" << std::endl;
    std::cout << "7 Quit" << std::endl;
    std::cout << "" << std::endl;
}


int main()
{

    std::cout << "===== Welcome to Markus' Bank =====\n\n" << std::endl;

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
            std::cout << "Hello there" << std::endl;
            break;
           case '2':
            break;
           case '3':
            break;
           case '4':
            break;
           case '5':
            break;
           case '6':
            bank.showAllAccounts();
            break;
           case '7':
            std::cout << "See You Again!" << std::endl;
            keepWorking = false;
            break;
        }

        std::cout << "" << std::endl;

    }

    return 0;
}