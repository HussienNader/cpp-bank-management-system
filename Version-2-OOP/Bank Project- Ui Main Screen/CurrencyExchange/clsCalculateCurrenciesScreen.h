#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsCurrency.h"
#include <iostream>

using namespace std;

class clsCalculateCurrenciesScreen : protected clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        // cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.CountryName();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }


    static string _ReadCurrencyCode(string position)
    {
        string CurrencyCode = "";

        cout <<"Please Enter CurrencyCode of Currency "<< position<<" ";
        CurrencyCode = clsInputValidate::ReadString();
        
        while (!clsCurrency::IsCurrencyExistByCurrencyCode(CurrencyCode))
        {
            cout <<"The Currency is Not Exist ,try another one : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return CurrencyCode;
    }


   static float _ReadAmount()
   {
       float Amount;

       cout << "\nEnter Ex-Change Amount: ";

       Amount = clsInputValidate::ReadFloatNumber();

       while (Amount <=0)
       {
      
        cout <<"You Ex-Change Amout less than or Equal to zero, try again : ";
        Amount = clsInputValidate::ReadDblNumber();
       }

       return Amount;
   }
    

    static void _PerformCalculatingCurrencies()
    {
        system("cls");
        _DrawScreenHeader("\t CalaculateCurrencies Screen");

        string Currency1, Currency2;


        Currency1 =_ReadCurrencyCode("1");

        Currency2 = _ReadCurrencyCode("2");
        while (Currency2 == Currency1)
        {
            cout <<"You Can't Make An Ex-Change Between The Same currencies, try Again: ";
            Currency2 = _ReadCurrencyCode("2");
        }


        clsCurrency C1 = clsCurrency::FindCurrencyByCurrencyCode(Currency1);
        clsCurrency C2 = clsCurrency::FindCurrencyByCurrencyCode(Currency2);

        
        float ExChangeAmountTODollar = _ReadAmount();


            // one step convert
            if(C2.CurrencyCode() == "USD")
            {
                cout <<"Convert From : \n";
                _PrintCurrency(C1);
                float AfterExchange = ExChangeAmountTODollar / C1.Rate();

                cout <<ExChangeAmountTODollar <<" "<<C1.CurrencyCode() <<" = "<<AfterExchange<<" USD " <<endl;
            }

            else
            {
                cout <<"Convert From : \n";
                _PrintCurrency(C1);
                float AfterExchange = ExChangeAmountTODollar / C1.Rate();

                cout <<ExChangeAmountTODollar <<" "<<C1.CurrencyCode() <<" = "<<AfterExchange<<" USD " <<endl;
                
                cout <<"\nConverting From USD To: \n";
                _PrintCurrency(C2);
                
                AfterExchange = AfterExchange * C2.Rate();
                cout <<ExChangeAmountTODollar <<" "<<C1.CurrencyCode() <<" = "<<AfterExchange<<C2.CurrencyCode() <<endl;

            }

    }

public:

static void ShowCalculateCurrenciesScreen()
    {
        char Answer;
        do
        {
            _PerformCalculatingCurrencies();
            cout <<"\nDoYou Want To Perform This Operation Again? y/n  ";
            cin>> Answer;
        } while (toupper(Answer) == 'Y');
        
    }
};