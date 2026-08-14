#pragma once
#include <iostream>
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "../clsBankClient.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{

private:

    // print Client
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("Deposit Screen");


        string AccountNumber = "";
        cout <<"Please enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();
        
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"The Account Number Is Not exist, Try Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient ::Find(AccountNumber);
        Client.Print();
        
        double Amount;
        cout <<"Please Enter The Amount You Want To Deposite: ";
        cin >> Amount;

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            if(!Client.IsEmpty())
            {
                Client.Deposit(Amount);
                cout <<"The Amount Deposited Successfully :)\n";
                cout <<"The New Balance Is : "<<Client.GetAccountBalance() <<endl;
            }
        }

        else
            cout <<"The operation was canceled\n";
        
    }
};