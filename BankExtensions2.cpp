#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

const string UsersDataFile = "Users.txt";

struct stUser
{
    string username;
    string password;
    int permissions = 0;
    bool MarkToDelete = false;
};

enum enMangaeUsers {UsersList = 1, Adduser, Deleteuser, Updateuser, Finduser, Mainmenue};

enum enPermissions {All = -1,pClientList = 1,pAddClients=2, pDeleteClients=4,pUpdateClients=8,
                        pFindClients = 16, pTransactions = 32, pManageUsers = 64};
//=======================================================================================


stUser CurrentUser;


bool CheckAccesPermissions(enPermissions Permission)
{
    if(CurrentUser.permissions == enPermissions::All)
        return true;

    if((CurrentUser.permissions & Permission) == Permission) 
        return true;
        
    else
        return false;    
}


vector<string> Split_String(string line ,string Delim = "#//#")
{
    vector<string> vStrings;
    short pos;
    string subString;

    while ((pos = line.find(Delim)) != string::npos)
    {
        subString = line.substr(0,pos);
        if(subString != "")
            vStrings.push_back(subString);

        line.erase(0,pos + Delim.length());    
    }

    if(line != "")
        vStrings.push_back(line);

    return vStrings;    
    
}


stUser ConvertUserLineToRecord(string line)
{
    vector<string>vStrings  = Split_String(line);
    stUser user;

    user.username = vStrings[0];
    user.password = vStrings[1];
    user.permissions = stoi(vStrings[2]);

    return user;
}


string ConvertUserRecordToLine(stUser User, string Separator = "#//#")
{
    string line = "";

    line += User.username + Separator;
    line += User.password + Separator;
    line += to_string(User.permissions);

    return line;
}


vector<stUser>ImportUsersDataFromFile(string FileName)
{
    vector<stUser> Users;

    fstream MyFile;
    MyFile.open(FileName,ios::in); // read mode
    
    if(MyFile.is_open())
    {
        stUser user;
        string line;
        while (getline(MyFile,line))
        {
            user = ConvertUserLineToRecord(line);
            Users.push_back(user);
        }
        
        MyFile.close();
    }

    return Users;
}


void SaveUserDataToFile(string Filename,vector<stUser> vUsers)
{
    fstream MyFile;
    MyFile.open(Filename,ios::out);

    if(MyFile.is_open())
    {
        string DataLine = "";
        for(stUser U : vUsers)
        {
            if(U.MarkToDelete == false)
            {
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine;
            }
        }
        MyFile.close();
    }
    
}

void  AddUserDataLineToFile(string Filename, string line)
{
    fstream Myfile;
    Myfile.open(Filename, ios::out | ios::app);

    if(Myfile.is_open())
    {
        Myfile << line;
    }

    Myfile.close();
}


bool FindUserByUsernameAndPassword(string Username, string Password,stUser &User)
{
    vector<stUser> Users = ImportUsersDataFromFile(UsersDataFile);

    for( stUser&U : Users)
    {
        if(U.username == Username && U.password == Password)
        {
            User = U;
            return true;
        }
    }

    return false;
}

bool LoadUserData(string Username,string Password)
{
    if(FindUserByUsernameAndPassword(Username,Password,CurrentUser))
        return true;
    
    else
        return false;
}


bool UserExistByUserName(string username)
{
    vector<stUser>vUsers = ImportUsersDataFromFile(UsersDataFile);

    for(stUser U : vUsers)
    {
        if(U.username == username)
            return true;
    }

    return false;
}


bool FindUserByUserName(string UserNaame, vector<stUser>vUsers, stUser &User)
{
    for(stUser U : vUsers)
    {
        if(U.username == UserNaame)
        {
            User = U;
            return true;
        }
    }

    return false;
}

int ReadPermissions()
{
    int Permessions = 0;
    char Answer;

    cout <<"Do you want to give this user full acces ? y/n";
    cin >> Answer;
    if(toupper(Answer == 'y'))
    {
        Permessions = -1;
        return Permessions;
    }
    

    else
    {
        cout <<"Do you want to give this user acces to [ClientList]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pClientList;    
        } 
        
        
        cout <<"Do you want to give this user acces to [Adding Clients]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pAddClients;    
        }
        
        
        cout <<"Do you want to give this user acces to [Deleting Clients]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pDeleteClients;    
        }
        
        
        cout <<"Do you want to give this user acces to [Updating clients]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pClientList;    
        }
        
        
        cout <<"Do you want to give this user acces to [Find Clients]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pFindClients;    
        }
        
        
        cout <<"Do you want to give this user acces to [Transactions]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pTransactions;    
        }
        
        
        cout <<"Do you want to give this user acces to [Manage Users]? y/n ";
        cin >> Answer;
        if(toupper(Answer == 'y'))
        {
            Permessions += enPermissions::pManageUsers;    
        }
        
        return Permessions;
    }

}


string ReadUserName()
{
    string username;
    cout <<"Please Enter Username: ";
    getline(cin >>ws, username);

    return username;
}


stUser ReadNewUser()
{
    stUser user;
    cout <<"Enter UserName: \n";
    getline(cin>>ws,user.username);
    while(UserExistByUserName(user.username))
    {
        cout <<"The UserName You Entered [ "<<user.username<<" ] Is Already Used"
        <<"Please try Another Username ";
        getline(cin>>ws,user.username);     
    }
    
    cout <<"Enter Password: ";
    cin >> user.password;
    
    user.permissions = ReadPermissions();

    return user;
}


void AddingNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddUserDataLineToFile(UsersDataFile,ConvertUserRecordToLine(User));
}

void AddingNewUsers()
{
    char Addmore;
    do
    {
        cout <<"Adding new user: \n";
        AddingNewUser();
        cout <<"Do yiu want to add new user ? y/n";
        cin >> Addmore;
    } while (toupper(Addmore == 'y'));
    
}


void PrintUserCard(stUser User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername : " << User.username;
    cout << "\nPassword : " << User.password;
    cout << "\nPermissions : " << User.permissions;
    cout << "\n-----------------------------------\n";
}


bool MarkUserToDelete(string UserName, vector<stUser>vUsers)
{
    for(stUser &U : vUsers)
    {
        if(U.username == UserName)
        {
            U.MarkToDelete = true;
            return true;
        }
    }

    return false;
}


void ChangeUserData(stUser User)
{
    cout <<"Please Enter Password: ";
    getline(cin>>ws,User.password);
    
    User.permissions = ReadPermissions();
}


void DeletingUserByUserName(string UserName)
{
    if(UserName == "Admin")
    {
        cout <<"You Can't delete this User";
        return;
    }

    vector<stUser>vUsers = ImportUsersDataFromFile(UsersDataFile);
    stUser User;
    char Del;

    if(FindUserByUserName(UserName,vUsers,User))
    {
        PrintUserCard(User);

        cout <<"Are You sure to Delete this User: ? y/n";
        cin >> Del;

        if(toupper(Del)== 'y')
        {
            MarkUserToDelete(UserName,vUsers);
            SaveUserDataToFile(UsersDataFile,vUsers);
            cout <<"The User [ "<<UserName<<"] has been Deleted successfully\n";
            vUsers = ImportUsersDataFromFile(UsersDataFile);
        }
    }

    else
        cout <<"The User [ "<<UserName<<"] Is Not Found in Your Data\n";    
}
//==========================================================================

void UpdateUserByUserName(string UserName ,vector<stUser> vUsers)
{
    stUser User; char Up;

    if(FindUserByUserName(UserName,vUsers,User))
    {
        PrintUserCard(User);

        cout <<"Are You sure You Want To Update this user ? y/n";
        cin >> Up;

        if(toupper(Up) == 'y')
        {
           for(stUser &U : vUsers)
           {
             if(U.username == UserName)
             {
                ChangeUserData(U);
                break;
             }
           }

           SaveUserDataToFile(UsersDataFile,vUsers);
           cout <<"The User [ "<<UserName<<" ] has been Updated succefully\n";

        }

    }

    else
        cout <<"The User [ "<<UserName<<" ] Is Not Found\n";
}


void FindUserByUserName(string UserName,vector<stUser> vUsers)
{
    stUser User;
    if(FindUserByUserName(UserName,vUsers,User))
    {
        PrintUserCard(User);
    }

    else
        cout <<"The User [ "<<UserName<<" ] Is not Found\n";
}


void ShowAddingNewUsersScreen()
{
    system("cls");
    cout <<"===============================\n\n";
    cout <<"\t\tAddnig NewUsers Screen\n";
    cout <<"===============================\n\n";

    AddingNewUsers();
    
}

 void PrintUserRecordLine(stUser User)
 {
    cout << "| " << setw(15) << left << User.username;
    cout << "| " << setw(10) << left << User.password;
    cout << "| " << setw(40) << left << User.permissions;
 }


void PrintMangeUsersMenue()
{
    system("cls");
    cout <<"=============================================\n\n";
    cout <<"\t\tManage Users Menue Screen\n";
    cout <<"\t[1] List Of Users \n";
    cout <<"\t[2] Add New User \n";
    cout <<"\t[3] Delete User \n";
    cout <<"\t[4] Update User \n";
    cout <<"\t[5] Find User \n";
    cout <<"\t[6] Main Menue User \n";
    cout <<"=============================================\n\n";
}


void ShowUsersLitMenueScreen()
{
    vector <stUser> vUsers = ImportUsersDataFromFile(UsersDataFile);
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ")User(s).";
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else
        for (stUser User : vUsers)
        {
            PrintUserRecordLine(User);
            cout << endl;
        }
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}


void ShowDeletUserScreenMenue()
{
    system("cls");
    cout <<"===============================\n\n";
    cout <<"\t\tDeleting Users Screen\n";
    cout <<"===============================\n\n";

    string UserName = ReadUserName();
    DeletingUserByUserName(UserName);
}


void ShowUpdateUserScreen()
{
    system("cls");
    cout <<"===============================\n\n";
    cout <<"\t\tUpdating Users Screen\n";
    cout <<"===============================\n\n";

    string UserName = ReadUserName();
    vector<stUser>vUsers = ImportUsersDataFromFile(UsersDataFile);
    UpdateUserByUserName(UserName,vUsers);
}


void ShowFindUserScreen()
{
    system("cls");
    cout <<"===============================\n\n";
    cout <<"\t\t Find Users Screen\n";
    cout <<"===============================\n\n";

    string UserName = ReadUserName();
    vector<stUser>vUsers = ImportUsersDataFromFile(UsersDataFile);
    FindUserByUserName(UserName,vUsers);

}


void GoBackToManagUsersMenue()
{
    cout <<"\nPress Any Key To Go Back To Manage Users Menue...\n";
    system("Pause>0");
    PrintMangeUsersMenue(); 
}


void StartUsersOperations()
{
    short choice;

    while (true)
    {
        cout <<"Enter your choice [1 - 6] : ";
        cin >> choice;

        switch (enMangaeUsers(choice))
        {
        case enMangaeUsers::UsersList:
            system("cls");
            ShowUsersLitMenueScreen();
            GoBackToManagUsersMenue();
            break;

        case enMangaeUsers::Adduser:
             system("cls");
             ShowAddingNewUsersScreen();
             GoBackToManagUsersMenue();
             break;

        case enMangaeUsers::Deleteuser:
             system("cls");
             ShowDeletUserScreenMenue();
             GoBackToManagUsersMenue();     
             break;

        case enMangaeUsers::Updateuser:
             system("cls");
             ShowUpdateUserScreen();
             GoBackToManagUsersMenue();     
             break;
             
        case enMangaeUsers::Finduser:
             system("cls");
             ShowFindUserScreen();
             GoBackToManagUsersMenue();     
             break;
             
        case enMangaeUsers::Mainmenue:
             system("cls");
             //showw main menue
             //break    
             break;     
        }
        
        if(enMangaeUsers(choice) == enMangaeUsers::Mainmenue) break;
    }
    
}


void Login()
{
    bool LoginFailed = false;
    string Username, Password;
    system("cls");

    cout <<"\n==============================\n\n";
    cout <<"\t\tLoginScreeen                \n\n";
    cout <<"================================\n\n";

    do
    {
        if(LoginFailed)
        {
            cout <<"\nYou Entered An Invalid Username Or Password\n";
        }

       
        cout <<"\nPlease Enter Valid Username And Password: \n";
        cout <<"Please Enter Username: ";
        cin >> Username;
        cout <<"Please Enter Password: ";
        cin >> Password;
       
        
        LoginFailed = !LoadUserData(Username,Password);

    } while (LoginFailed);

    
    
}