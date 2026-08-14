#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsUser.h"
#include <iostream>

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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


   static void _ReadUserInfo(clsUser & User)
   {
     
      cout << "Enter First Name: ";
      User.SetFirstName(clsInputValidate::ReadString());
      cout << "Enter Last Name: ";
      User.SetLastName(clsInputValidate::ReadString());
      cout << "Enter Email: ";
      User.SetEmail(clsInputValidate::ReadString());
      cout << "Enter Phone: ";
      User.SetPhone(clsInputValidate::ReadString());
      cout << "Enter Password: ";
      User.SetPassword(clsInputValidate::ReadString());
      cout <<"Enter PerMissions \n\n";
      User.SetPermissions(ReadPermissions());
   }


    static int ReadPermissions()
    {
       return clsUser::ReadUserPermissions();
    }


public:

    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t  Update Screen ");

       
        string UserName = "";
        cout <<"PLease Enter User Name: ";
        UserName = clsInputValidate:: ReadString();
        
        while (!clsUser::IsUserExist(UserName))
        {
            cout <<"The User Name Is Not  exist ,Try Again: ";
            UserName = clsInputValidate:: ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _Print(User);


        cout <<"Are You Sure U Want To update thiss User y/n  ";
        char Answer;
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
            cout <<"\n_________ Updating User __________\n\n";
            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;

            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::enSaveResults::svSucceeded:
                 cout <<"The User Has Been Updated Successfull :)";
                 _Print(User);
                break;
             
            case clsUser::enSaveResults::svFaildEmptyObject:
                 cout <<"The User Has Not Been Updated Because it's Empty ";
                 break;
            }

        }
    }
};