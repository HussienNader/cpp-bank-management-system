#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen :protected clsScreen
{

private:
    // _PrintClient
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
    static void ShowDeleteClientScreen()
    {

         if(!CheckAccesRghts(clsUser::enPermissions::pDeleteClients))
        {
            return;
        }


        _DrawScreenHeader("Delete Client Screen");



        string AccountNumber = "";
        AccountNumber = clsInputValidate:: ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"\n The Account Number Is not Exsit, Try Another One: ";
            AccountNumber = clsInputValidate:: ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
    
        cout <<"Are  You Sure You Want To Delete this Client? Y / N : ";
        char Answer;
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
            if(Client.Delete())
            {
                cout <<"Client Has Been Deleted Succesfully\n";
                _PrintClient(Client);
            }

            else
                cout <<"Error The Client Couldn't Be Deleted\n";
        }
    }    
};