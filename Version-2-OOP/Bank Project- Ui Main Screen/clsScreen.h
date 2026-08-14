#pragma once
#include <iostream>
#include "BankProject-Ui Manage Users Screen/clsUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{

protected:
    static void _DrawScreenHeader(string Title,string SubTitle ="")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout <<"\t\t\t\t\t    "<<CurrentUser.GetUserName() << endl;
        cout <<"\t\t\t\t\t    "<<clsDate::DateToString(clsDate())<< endl;;
    }


    static bool CheckAccesRghts(clsUser::enPermissions Permssions)
    {
        if(!CurrentUser.CheckAccessPermossions(Permssions))
        {
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                return false;
        }
        else 
            return true;
    }


   
    

};