#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsUpdateClientScreen : protected clsScreen
{

private:
    // ReadClientInfo

    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber()) ;
    }

    // PrintClientInfo
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

    static void ShowUpdateClientScreen()
    {

         if(!CheckAccesRghts(clsUser::enPermissions::pUpdateClient))
         {
            return;
         }


        _DrawScreenHeader("Update Client Screen");

        

        string AccountNumber = "";
        cout <<"Please Enter Account Number: ";
        AccountNumber = clsInputValidate:: ReadString();
        
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout <<"\n The Account Number Is Not Exist, Try Another One: ";
            AccountNumber = clsInputValidate:: ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout <<"\n Are Your Sure You Want to Update This Client ? Y / N: ";
        char Answer;
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
            cout <<"\n____Updating Client Data____\n";
            _ReadClientInfo(Client);

            clsBankClient ::enSaveResults SaveResult;
            SaveResult = Client.Save();

            switch (SaveResult)
            {
                case  clsBankClient::enSaveResults::svSucceeded:
                {
                    cout << "\nAccount Updated Successfully :-)\n";
                    _PrintClient(Client);
                    break;
                }
                case clsBankClient::enSaveResults::svFaildEmptyObject:
                {
                    cout << "\nError account was not saved because it's Empty";
                    break;    
                }            
            }       
        }
    }


};