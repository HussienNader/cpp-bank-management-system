#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        _DrawScreenHeader("\t  Find User Screen ");

       

        string UserName = "";
        cout <<"Please Enter The User Name: ";
        UserName = clsInputValidate::ReadString();
        
        while (!clsUser::IsUserExist(UserName))
        {
            cout <<"This User Is Not Exist, try Another one..: ";
            UserName = clsInputValidate::ReadString();
        }
        

        clsUser User = clsUser::Find(UserName);

        if(!User.IsEmpty())
        {
            _Print(User);
        }

        else
            cout <<"The user is Empty ";
    }
};