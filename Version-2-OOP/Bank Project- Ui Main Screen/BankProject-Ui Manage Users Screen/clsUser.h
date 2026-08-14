#pragma once
#include "../clsPerson.h"
#include "../clsInputValidate.h"
#include "../clsString.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class clsUser : public clsPerson
{
    public:

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;

    };

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;
    string _UserName;
    string _Password;
    int  _Permissions;
    bool _MarkedForDelete;

    // struct stLoginRegisterRecord;


    static string _ConvertUserObjectToline(clsUser User, string separator = "#//#")
    {
        string st = "";

        st += User.GetFirstName() + separator;
        st += User.GetLastName()  + separator;
        st += User.GetEmail()     + separator;
        st += User.GetPhone()     + separator;
        st += User.GetUserName()  + separator;
        st += clsString::EncyreptString( User.GetPassword() )  + separator;
        st += to_string(User.GetPermissions());

        return st;
    }

    static clsUser _ConvertUserLineToObject(string Line, string separator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line,separator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4],clsString::DeycrePtString( vUserData[5] ), stoi(vUserData[6]));

    }


    static stLoginRegisterRecord _ConvertRegisterLineToUserRecord(string line, string separator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(line, separator);
        
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsString::DeycrePtString( LoginRegisterDataLine[2] );
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }


    static vector<stLoginRegisterRecord> _LoadLoginRegisterData()
    {
        vector <stLoginRegisterRecord> vLoginRegisterRecord;

         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);//read Mode

         if (MyFile.is_open())
         {

             string Line;

             stLoginRegisterRecord LoginRegisterRecord;

             while (getline(MyFile, Line))
             {

                 LoginRegisterRecord = _ConvertRegisterLineToUserRecord(Line);

                 vLoginRegisterRecord.push_back(LoginRegisterRecord);

             }

             MyFile.close();

         }

         return vLoginRegisterRecord;

     }
    


    static vector<clsUser> _LoadUserDataFromFile()
    {
        vector<clsUser> vUsers;

        fstream MyFile;

        MyFile.open("UsersData.txt",ios:: in); // read mode
        if(MyFile.is_open())
        {
            string DataLine = "";
            while (getline(MyFile,DataLine))
            {
                clsUser User = _ConvertUserLineToObject(DataLine);
                vUsers.push_back(User);
            }

            MyFile.close();
        }

        else 
            cout <<"\n\n couldn't open the file\n";

        return vUsers;
    }


    static void _SaveUserDataToFile(vector<clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("UsersData.txt", ios:: out); // write mode
        if(MyFile.is_open())
        {
            string DataLine = "";
            for(clsUser U : vUsers)
            {
                if(U.MarkedForDeleted() == false)
                {
                    DataLine = _ConvertUserObjectToline(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }


    void _Update()
    {
        vector<clsUser> vUsers = _LoadUserDataFromFile();

        for(clsUser &U: vUsers)
        {
           if(U.GetUserName() == this->GetUserName())
           {
              U = *this;
              break;
           } 
        }

        _SaveUserDataToFile(vUsers);

    }

    
    void _AddNew()
    {
        _AddDataLine(_ConvertUserObjectToline(*this));
    }
    

    void _AddDataLine(string line)
    {
        fstream MyFile;
        MyFile.open("UsersData.txt",ios::out | ios::app);

        if(MyFile.is_open())
        {
            MyFile << line << endl;
        }

        MyFile.close();
    } 

    string _PrepareLogInRecord(string separator = "#//#")
    {
        string LogInRecord = clsDate::GetSystemTimeInString() + separator;
        LogInRecord += this->GetUserName() + separator;
        LogInRecord += clsString::EncyreptString( this->GetPassword() ) + separator;
        LogInRecord += to_string(this->GetPermissions());

        return LogInRecord;
    }
    
            
public:
    
     enum enPermissions{ eAll = -1, pListClients = 1, pAddClients = 2, pDeleteClients = 4,
                        pUpdateClient= 8, pFindclients= 16, pTransactions= 32,pManageUsers= 64,
                        pLoginRegister= 128
                       
                    };

    
     enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };               


    

    clsUser(enMode mode,string firstname, string lastname, string email ,string Phone,
                    string userNaame, string password,int permissions):
                    clsPerson(firstname,lastname,email,Phone)
    {
        _Mode = mode;
        _UserName = userNaame;
        _Password = password;
        _Permissions = permissions;
        _MarkedForDelete = false; 
    }

    /* clsUser(string datetime, string username, string password,int permissions):clsPerson("","","","")
    {
        this->_DateTime = datetime;
        this->_UserName = username;
        this->_Password = password;
        this->_Permissions = permissions;
    } */
 
    
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    // Add method to mark user for deletion
    void SetMarkForDelete(bool value = true)
    {
        _MarkedForDelete = value;
    }


    string GetUserName()
    {
        return _UserName;
    }


    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }


    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }


    int GetPermissions()
    {
        return _Permissions;
    }


    static clsUser Find(string UserName)
    {
       fstream MyFile;
       MyFile.open("UsersData.txt", ios:: in); // read mode

       if(MyFile.is_open())
       {
          string DataLine = "";

          while (getline(MyFile,DataLine))
          {
             clsUser User = _ConvertUserLineToObject(DataLine);
             if(User.GetUserName() == UserName)
             {
                MyFile.close();
                return User;
             }
          }  
       }

       return GetEmptyUser();
    }


    static clsUser Find(string UserName, string Password)
    {
       fstream MyFile;
       MyFile.open("UsersData.txt", ios:: in); // read mode

       if(MyFile.is_open())
       {
          string DataLine = "";

          while (getline(MyFile,DataLine))
          {
             clsUser User = _ConvertUserLineToObject(DataLine);
             
             if(User.GetUserName() == UserName && User.GetPassword() == Password)
             {
                MyFile.close();
                return User;
             }
          }  
       }

       return GetEmptyUser();
    }


    static bool IsUserExist(string UserName)
    {
        clsUser User = Find(UserName);
        return (!User.IsEmpty());
    }


    static clsUser GetEmptyUser()
    {
       return clsUser(enMode::EmptyMode,"","","","","","",0);
    }


    static clsUser  GetAddNewClientObject(string UserName)
    {
        return clsUser (enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }


    static vector<clsUser> GetUsersList()
    {
        return _LoadUserDataFromFile();
    }


    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser (enMode::AddNewMode,"","","","",UserName,"",0);
    }


    bool DeleteUser()
    {
        vector<clsUser> vUsers =_LoadUserDataFromFile();

        for(clsUser &U : vUsers)
        {
            if(U.GetUserName() == this->GetUserName())
            {
                U.SetMarkForDelete();// true;
            }
        }

        _SaveUserDataToFile(vUsers);

        *this = GetEmptyUser();

        return true;
    }


    enSaveResults Save()
    {
        enSaveResults Result;
        switch (_Mode)
        {
        case enMode::AddNewMode:
            if(IsUserExist(this->GetUserName()))
            {
                Result =  enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                Result =  enSaveResults::svSucceeded;
            }
        
        case enMode::UpdateMode:
            _Update();
             Result =  enSaveResults::svSucceeded;
             
        case enMode::EmptyMode:
             Result =  enSaveResults::svFaildEmptyObject;     
        
        }

        return Result;
    }


    static int ReadUserPermissions()
    {
       int permissions = 0;
        char Answer;
        
        cout <<"Do you want to give this user Full Access ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
            return -1;
        }

        cout <<"Do You Want To Give This User Access to \n";

        cout <<"\nShow Clients List ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pListClients;
        }


        cout <<"\nAdd New Clients ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pAddClients;
        }


        cout <<"\nDelete Clients ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pDeleteClients;
        }


        cout <<"\nUpdate Clients ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pUpdateClient;
        }


        cout <<"\nFind Clients ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pFindclients;
        }


        cout <<"\nTransactions ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pTransactions;
        }


        cout <<"\nManage Users ? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pManageUsers;
        }


        cout <<"\nLogin Registers? y/n: ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
        {
           permissions += clsUser::enPermissions::pLoginRegister;
        }


        return permissions;
    }    


    bool CheckAccessPermossions(enPermissions permission)
    {
        if(this->GetPermissions() == enPermissions::eAll)
            return true;

        if((this->_Permissions & permission) == permission)
            return true;
        
        else
            return false;    
    }



    void RegisterLogin()
    {
        string DataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        
        if(MyFile.is_open())
        {
            MyFile << DataLine << endl;
            
            MyFile.close();
        }

    }
    

    
    
    static  vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        return _LoadLoginRegisterData();
    }
    
};
