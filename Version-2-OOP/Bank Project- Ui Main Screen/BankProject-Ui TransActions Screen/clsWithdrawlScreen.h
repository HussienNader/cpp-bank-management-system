#pragma once
#include <iostream>
#include "../clsScreen.h"
#include "../clsBankClient.h"
#include "../clsInputValidate.h"

using namespace std;

class clsWithdrawl : protected clsScreen
{

private:
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
    static void ShowWithdarwlScreen()
    {
        _DrawScreenHeader("Withdrawl Screen");


        string AccountNumber = "";
        cout <<"Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"The Account Number Is Not exist, Try Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        

        clsBankClient Client = clsBankClient:: Find(AccountNumber);
        Client.Print();

        double Amount;
        cout <<"Please Enter The Amount You Want To Withdraw: ";
        cin >> Amount;

        cout <<"Are Youe Sure You want to perform this transaction ? Y/N  ";
        char Answer;
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            if(!Client.IsEmpty())
            {
                if(Client.Withdrawl(Amount))
                {
                    cout <<"The Amount was Withdrwaled successfully :)\n";
                    cout <<"The New Balabce Is : "<< Client.GetAccountBalance() << endl; 
                }

                else
                {
                    cout <<"Can Not Withdaraw InSuffecient balance \n";
                    cout << "Amout To withdraw is : "<< Amount << endl;
                    cout <<"The Actual Balance is : "<< Client.GetAccountBalance() << endl;
                }
            }
        }

        else
            cout <<"The Operation was Canceled\n";
    }
};
