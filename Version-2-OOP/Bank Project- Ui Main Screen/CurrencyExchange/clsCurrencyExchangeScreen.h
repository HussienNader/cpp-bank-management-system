#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdatecurrencyScreen.h"
#include "clsCalculateCurrenciesScreen.h"
#include <iostream>
#include <iomanip>


class clsCurrencyExchangescreen : protected clsScreen
{

private:

    enum enCurrencyOperations {cListCurrency =1,eFindCurrency =2,eUpdateCurrency =3,eCalculateCurrency =4,
                                MainMenue =5};

    static short _ReadCurrencyMenueOptions()
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,10,"Enter Number between 1 to 5 ? ");
        return Choice;
    }
    

    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << setw(37) << left << ""<<"\n\tPress any key to go back to Currency Menue...\n";
        
        system("pause>0");
        ShowCurrencyExchangeScreen();
    }


    
    static void  _ShowListCurrenciesScreen()
    {
        // cout <<"List Currencies Screen Will Be Here  ...";
          clsListCurrenciesScreen::ShowListCurrenciesScreen();
    }

    static void  _ShowFindCurrenciesScreen()
    {
        // cout <<"Find Currencies Screen Will Be Here  ...";
            clsFindCurrency::ShowFindCurrencyScreen();
    }


    static void  _ShowUpdateCurrenciesScreen()
    {
        // cout <<"Update Currencies Screen Will Be Here  ...";
            clsUpdateCurrencyScreen::ShowUpdateCurrenncyScreen();
    }


    static void  _ShowLCalculateCurrenciesScreen()
    {
        // cout <<"Calculate Currencies Screen Will Be Here  ...";
            clsCalculateCurrenciesScreen::ShowCalculateCurrenciesScreen();
    }


    static void  _ShowGotoMainMenueScreen()
    {
        cout <<"got to Main Menue Screen Screen Will Be Here  ...";
    }


    static void _PerformCurrencyExchangeMenueOptions(enCurrencyOperations Operation)
    {
        switch (Operation)
        {
        case enCurrencyOperations::cListCurrency:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        
        case enCurrencyOperations::eFindCurrency:
            system("cls");
            _ShowFindCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
                
        case enCurrencyOperations::eUpdateCurrency:
            system("cls");
            _ShowUpdateCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyOperations::eCalculateCurrency:
            system("cls");
            _ShowLCalculateCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyOperations::MainMenue:
            
            break;
        
        }
    }


public:
    
    static void ShowCurrencyExchangeScreen()
    {
         system("cls");
            _DrawScreenHeader("\tCurrency Exchange Screen");

            

            cout << setw(37) << left <<""<< "===========================================\n";
            cout << setw(37) << left << "" << "\t\tCurrency Exchange Main Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
            cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Claculator.\n";
            cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            
            _PerformCurrencyExchangeMenueOptions((enCurrencyOperations) _ReadCurrencyMenueOptions());
    }

};