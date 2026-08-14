#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{

private:
    // Print Client
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
    static void ShowFindClientScreen()
    {

         if(!CheckAccesRghts(clsUser::enPermissions::pFindclients))
         {
            return;
         }



        _DrawScreenHeader("Find Client Screen");


        
        string AccountNumber = "";
        cout <<"Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"\n The Account Number is Not Exist, Try Another One: ";
            AccountNumber = clsInputValidate:: ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if(!Client.IsEmpty())
            cout <<"\n Client Found Successfuly -)";
       
        else
            cout <<"\n Client Did Not Found ";

        
        _PrintClient(Client);    
        
    }

};