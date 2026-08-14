#pragma once
#include "../clsScreen.h"
#include "../clsBankClient.h"
#include "../clsInputValidate.h"
#include <iostream>

using namespace std;

class clsTrnasferScreen :  protected clsScreen
{
    
private:
    static void _PrintCLientTrasferInfo(clsBankClient Client)
    {
        cout <<"\nClient Card: \n";
        cout <<"_________________\n";
        cout <<"Full Name   : "<< Client.FullName()<<endl;
        cout <<"Acc.Number  : "<< Client.AccountNumber()<<endl;
        cout <<"Balance     : "<< Client.GetAccountBalance()<<endl;
        cout <<"__________________\n";
    }

    static string _ReadAccountNumber(string position)
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer "<<position <<" : ";
        AccountNumber = clsInputValidate::ReadString();
       
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }



   static float _ReadAmount(clsBankClient SourceClient)
   {
       float Amount;

       cout << "\nEnter Transfer Amount? ";

       Amount = clsInputValidate::ReadFloatNumber();

       while (Amount > SourceClient.GetAccountBalance() || Amount <=0)
       {
            if(Amount <= 0)
            {
                cout <<"You Can't transfer Amount Less Than or Equal to Zero ,Enter Another Amount: ";
            }
            else
                cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
           
            Amount = clsInputValidate::ReadDblNumber();
       }
       return Amount;
   }

public:
    static void ShowTransferScreen()
    {

            _DrawScreenHeader("\t Transfer Screen");

            string AccountNumber1 , AccountNumber2;
        
      
            AccountNumber1 = _ReadAccountNumber("From");
            clsBankClient ClientSource = clsBankClient::Find(AccountNumber1);
            _PrintCLientTrasferInfo(ClientSource);
            
            
            AccountNumber2 = _ReadAccountNumber("To");
            while (AccountNumber2 == AccountNumber1)
            {
                cout <<"You Can't Transfer Money Through The Same Account, try Another Distination: ";
                AccountNumber2 = _ReadAccountNumber("To");
            }
            
            clsBankClient ClientDistination = clsBankClient::Find(AccountNumber2);
            _PrintCLientTrasferInfo(ClientDistination);
            

            float Amount = _ReadAmount(ClientSource);
            

           cout <<"Are You Sure You Want To Perform This Operation ? y/n : ";
           char Answer;
           cin >> Answer;

           if(toupper(Answer) == 'Y')
           {
                if(ClientSource.Transfer(Amount,ClientDistination))
                {
                    cout <<"\nThe Transfer Done successfully :)\n\n";

                      
                    _PrintCLientTrasferInfo(ClientSource);
                    _PrintCLientTrasferInfo(ClientDistination);
                }

                else
                     cout <<"The Transfer Couldn't Be Compeleted";
           }

           else
                    cout <<"The Operation Was Canceled ";   
        
    } 

};