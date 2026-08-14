#pragma once
#include "../clsScreen.h"
#include "../clsInputValidate.h"
#include "clsUser.h"
#include <iostream>

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{

private:
    //readuser
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
  
    // Print user info
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
    
    // read permissions
    static int ReadPermissions()
    {
        return clsUser::ReadUserPermissions();
    }
    
public:
    

   static void ShowAddNewUserScreen()
   {

      _DrawScreenHeader("\t  Add New User ");


      string UserName = "";
      cout << "Enter User Name: ";
      UserName = clsInputValidate:: ReadString();
      
      while (clsUser::IsUserExist(UserName))
      {
          cout <<"this user name is already exist, try another one : ";
          UserName = clsInputValidate:: ReadString();
      }


      clsUser User = clsUser::GetAddNewClientObject(UserName);

      _ReadUserInfo(User);

      clsUser::enSaveResults  SaveResult;

      SaveResult =  User.Save();

      switch (SaveResult)
      {
        case clsUser::enSaveResults::svSucceeded:
            cout <<"\nThe User Has Been Added Successfyly :)\n";
            _Print(User);
            break;

        case clsUser::enSaveResults::svFaildEmptyObject:
            cout <<"\nError Couldn't Add User because The User Is Empty \n";  
            break;
      }
   }                 

    
};
