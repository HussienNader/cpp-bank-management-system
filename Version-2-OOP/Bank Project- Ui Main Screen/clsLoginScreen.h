#pragma once 
// #include "Global.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include <iostream>

using namespace std;

class clsloginScreen : protected clsScreen
{

private:
    static bool _Login()
    {
        _DrawScreenHeader("\t  Login Screen");
        
       

        bool LoginFailed = false;

        string UserName, Password;
        short TrailCounter = 3;

        do
        {
            if(LoginFailed && TrailCounter)
            {
                cout <<"\nInvalid UserName Or Password \n";
                TrailCounter--;
                cout << "You have "<< TrailCounter << " to login\n";
            }

            if(TrailCounter == 0)
            {
                cout <<"You are Locked after 3 Failed trails\n";
               
                return false;
            }          

            cout <<"Please Enter User Name: ";
            cin >> UserName;
            
            cout <<"Please Enter Password: ";
            cin >> Password;


            CurrentUser = clsUser::Find(UserName,Password);
            LoginFailed = CurrentUser.IsEmpty();
            
        } while (LoginFailed);

        CurrentUser.RegisterLogin();

        clsMainScreen::ShowMainMenue();

        return true;
    }

public:
    
    static bool ShowLoginScreen()
    {
        system("Cls");
        return _Login();
    }
};


