#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "../clsString.h"
#include "clsCurrency.h"
#include <iostream>

using namespace  std;

class clsUpdateCurrencyScreen : private clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.CountryName();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }


public:

    static void ShowUpdateCurrenncyScreen()
    {
        _DrawScreenHeader("\t Update Currency screen");

        string CurrencyCode;

        cout <<"Enter Currency Code : ";
        CurrencyCode = clsInputValidate::ReadString();
        
        while (!clsCurrency::IsCurrencyExistByCurrencyCode(CurrencyCode))
        {
            cout <<"Currency Is Not Exist ,Try Another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindCurrencyByCurrencyCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout <<"Are You Sure You Want To Update This Currency Rate y/n ";
        char Answer;
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            cout <<"\n____Updating Rate_________\n";
            float Rate;
            cout << "Enter Amount : ";
            cin >> Rate;
            Currency.UpdateRate(Rate);

            cout <<"\nUpdate Done Succesfuly\n";
            _PrintCurrency(Currency);

        }

        else
            cout <<" Operation Canceled ";

    }
};