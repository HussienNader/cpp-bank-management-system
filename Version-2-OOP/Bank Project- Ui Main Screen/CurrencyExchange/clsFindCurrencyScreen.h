#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsCurrency.h"
#include <iostream>

using namespace std;

class clsFindCurrency : protected clsScreen
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

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t Find Currency Screen");

        cout <<"Find By [1] Code or [2] Country ";
        short choice = clsInputValidate::ReadShortNumberBetween(1,2);

        if(choice == 1)
        {
            cout <<"Enter Currency Code : ";
            string CurrencyCode = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExistByCurrencyCode(CurrencyCode))
            {
                cout <<"The Currency Code is not Exist ,Try again: ";
                CurrencyCode = clsInputValidate::ReadString();
            }
            
            clsCurrency Currency = clsCurrency::FindCurrencyByCurrencyCode(CurrencyCode);

            if(!Currency.IsEmpty())
            {
                cout <<"Currency  found :)\n";
                _PrintCurrency(Currency);
            }
            else 
                cout <<"Couldin't Find The Currency\n";
        }

        else
        {
            cout <<"Enter Country Name : ";
            string CountryName = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExistByCountryName(CountryName))
            {
                cout <<"The Currency  is not Exist ,Try again: ";
                CountryName = clsInputValidate::ReadString();
            }
            
            clsCurrency Currency = clsCurrency::FindCurrencyByCountryName(CountryName);

            if(!Currency.IsEmpty())
            {
                cout <<"Currency  found :)\n";
                _PrintCurrency(Currency);
            }
            else 
                cout <<"Couldin't Find The Currency\n";
        }
    }
};




