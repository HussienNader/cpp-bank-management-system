#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsUser.h"
#include <iostream>

using namespace std;

class clsDeleUserScreen : protected clsScreen
{

private:

        static void _Print(clsUser User)
        {
            cout << "\nUser Information:\n";
            cout << "---------------------\n";
            cout << "User Name   : " << User.GetUserName() << endl;
            cout << "First Name  : " << User.GetFirstName() << endl;
            cout << "Last Name   : " << User.GetLastName() << endl;
            cout << "Email       : " << User.GetEmail() << endl;
            cout << "Phone       : " << User.GetPhone() << endl;
            cout << "Permissions : " << User.GetPermissions() << endl;
        }


public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete Screen ");



        string UserName = "";
        cout  <<"Please Enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout <<"The User Name Is Not exist, Plese Try Another One: ";
            UserName =clsInputValidate:: ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _Print(User);

        cout <<"\nAre Youe Sure You want to Delete this User ? y/n : ";
        char Answer;
        cin >> Answer;
        if(toupper(Answer)== 'Y')
        {
            if(User.DeleteUser())
            {
                cout <<" The User Was Deleted Successfuly :)";
                _Print(User);
            }

            else
                cout <<"The is Not Deleted \n";
        }
        
    }
};