
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

const string CLientsFilename = "Bank_Data.txt";
const string UsersDataFile = "Users.txt";


//todo ---> The Enums ------------------------->

enum enCrudOperations {ShowList = 1, AddClient, DeleteClient, UpdateClient, FindClient,TransMenue,
                        ManageUserMenue, Exit};


enum enMangaeUsers {UsersList = 1, Adduser, Deleteuser, Updateuser, Finduser, Mainmenue};

enum enPermissions {All = -1,pClientList = 1,pAddClients=2, pDeleteClients=4,pUpdateClients=8,
                        pFindClients = 16, pTransactions = 32, pManageUsers = 64};
//=======================================================================================


struct stClientInfo
{
  string Name;
  string AccountNumber;
  string Pincode;
  string Phone;
  double AccountBalance;
  bool ToDelete = false;  
};


struct stUser
{
    string username;
    string password;
    int permissions = 0;
    bool MarkToDelete = false;
};





// Forward declaration
stUser CurrentUser;

void PrintTransactionMenue();
void StartBank_Entensions(vector<stClientInfo> &vClients);
void PrintMangeUsersMenue();
void Login();
bool CheckAccesPermissions(enPermissions Permission);
void StartUsersOperations();




void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied"<<endl;
    cout << "You dont Have Permission To Do this" << endl;
    cout << "Please Conact Your Admin.";
    cout << "\n------------------------------------\n";
}
//todo --> this method to read data from user
stClientInfo ReadClientFromUser()
{
    stClientInfo Client;

    cout <<"Enter Account number: ";
    getline(cin >>ws,Client.AccountNumber);

    cout <<"Enter Name: ";
    getline(cin ,Client.Name);

    cout <<"Enter Pincode: ";
    getline(cin ,Client.Pincode);

    cout <<"Enter Phone: ";
    getline(cin, Client.Phone);

    cout <<"Enter Balance: ";
    cin >> Client.AccountBalance;

    return Client;
}

//todo ---> this method takes a client record an convert it to a line string to be saved in File
string ConverRecordToLne(stClientInfo Client, string separator = "#//#")
{
    //Format will be  account number + pincode + name + phone + balance
    string Linerecord = "";

    Linerecord += Client.AccountNumber + separator;
    Linerecord += Client.Pincode + separator;
    Linerecord += Client.Name + separator;
    Linerecord += Client.Phone + separator;
    Linerecord += to_string(Client.AccountBalance) + separator;

    return Linerecord;
}


//todo ---> this method to split the line into strings in a vector without the separator
vector<string> Split_String(string line, string separator = "#//#")
{
    vector<string> vString;
    short pos;
    string subword;

    while ((pos = line.find(separator)) != string::npos)
    {
        subword = line.substr(0,pos);
        if(subword != "")
            vString.push_back(subword);

        line.erase(0,pos + separator.length());    
    }

    if(line != "")
      vString.push_back(line);
    
    return vString;
}


//todo ---> this method to convert a line to record (used when reading from file)
stClientInfo ConvertLineToRecord(string line, string separator = "#//#")
{
    vector<string> vString;
    // to split the separator from line
    vString = Split_String(line,separator);

    stClientInfo Client; // to save data in it
    //Format account number - pincode - name - phone - balance
    Client.AccountNumber  = vString[0];
    Client.Pincode        = vString[1];
    Client.Name           = vString[2];
    Client.Phone          = vString[3];
    Client.AccountBalance = stod(vString[4]);

    return Client;
}

//todo ---> this method is to search for a client by it's account number check if exist or not only!
bool FindClientByAccountNumber(string accountnumbr, vector<stClientInfo> Client_list, stClientInfo &client)
{
    
    for(stClientInfo c : Client_list)
    {
        if(accountnumbr == c.AccountNumber)
        {
            client  = c;
            return true;
        }
    }
    return false;
}

//todo ---> this method prints the clients informations in columns( use it for printing separately)
void Print_AclientInfo(stClientInfo Client)
{
    cout <<"The folowing is client informations: \n";
    cout <<"--------------------------------------------------\n";
    cout <<"Account Number : "<< Client.AccountNumber << endl;
    cout <<"pin code       : "<< Client.Pincode << endl;
    cout <<"Name           : "<< Client.Name << endl;
    cout <<"Phone          : "<< Client.Phone << endl;
    cout <<"Balance        : "<< Client.AccountBalance << endl;
    cout <<"--------------------------------------------------\n";

}


//todo ---> this method is relevant to the printing table method
void PrintClientRecord(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber; 
     
    cout << "| " << setw(30) << left << Client.Name; 
    cout << "| " << setw(12) << left << Client.Phone; 
    cout << "| " << setw(12) << left << Client.AccountBalance; 
}

// todo ---> this method prints the all clients in a table
void Print_Clientlist_Data(vector<stClientInfo> clientlist)
{

    if(!CheckAccesPermissions(enPermissions::pClientList))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout <<"\n\t\t\t\t\tclientlist( "<<clientlist.size()<<" ) clients";
    cout <<
    "\n__________________________________________________________________";
    cout <<"_____________________________________________________________\n"<<endl;

    cout <<"| "<<left << setw(15) <<"Account Number";
    cout <<"| "<<left << setw(10) <<"Pin Code";
    cout <<"| "<<left << setw(40) <<"Client Name";
    cout <<"| "<<left << setw(12) <<"Phone";
    cout <<"| "<<left << setw(12) <<"Balance";
    cout <<
    "\n__________________________________________________________________";
    cout<<"______________________________________________________________\n"<<endl;

    for(stClientInfo client : clientlist)
    {
        PrintClientRecord(client);
        cout << endl;
    }
}

vector<stClientInfo> Import_ClientDataFromFile(string filename)
{
    vector<stClientInfo> Clients_list;// vector of clients to save all clients in it

    fstream Myfile;
    Myfile.open(filename,ios::in);// open file in read mode
    
    if(Myfile.is_open())
    {
        stClientInfo Client;
        string line;

        while (getline(Myfile,line))
        {
            Client = ConvertLineToRecord(line);
            Clients_list.push_back(Client);
        }
        
        Myfile.close();
        
    }

    else
    {
        cout <<"The file couldn't open properly\n";
    }

    return Clients_list;

}

//todo ---> this method is converting list of Clients to string format and save it to a file
void SaveDataToFile(string filename,vector<stClientInfo> CLient_list)
{
    fstream Myfile;
    Myfile.open(filename,ios:: out);
    
    if(Myfile.is_open())
    {
        string Dataline = "";

        for(stClientInfo c : CLient_list)
        {
            if(c.ToDelete == false) // check if it was true then should ignore it(delete)
            {
                Dataline = ConverRecordToLne(c);
                Myfile << Dataline << endl;
            }
        }
        
        Myfile.close();
    }

    else
    {
        cout <<"The file Couldn't open properly\n";
    }
}

//todo ---> this method to mark client (true) for deletion check from the list of clients  with ref
 void MarktoDelete(string accountnumber, vector<stClientInfo> &Client_list)
 {
    for(stClientInfo &c : Client_list)
    {
        if(accountnumber == c.AccountNumber)
        {
            c.ToDelete = true;
            break;
        }
    }
 }

//todo ---> this method to search for a client and delete it if exist 
void DeleteClientFromData(string accountnumber, vector<stClientInfo> &Client_list)
{
    //first make client to receive data in it for printing and manipulating
    stClientInfo client; char Del = 'n'; 
    //second check if the client exist or not
    if(FindClientByAccountNumber(accountnumber, Client_list, client))
    {
         Print_AclientInfo(client);

         cout <<"\n Are you sure you wan do delete this client ? ";
         cin >> Del;
         if(Del == 'y' || Del == 'Y')
         {
            MarktoDelete(accountnumber, Client_list);   // mark to prepare to delete
            SaveDataToFile(CLientsFilename,Client_list);// save all data without the marked client
            cout <<"The client has been deleted sucscesfully\n";
            //update data after deletion
            Client_list = Import_ClientDataFromFile(CLientsFilename);
         }
    }
    
    else
    {
        cout <<"The client of account number "<< accountnumber <<" is not found"<< endl;
    }

}


//todo ---> this method is relevant to UpdateMethod for re-writing client_data
 stClientInfo ReUpdate_A_clientData(string accountnumber)
 {
    stClientInfo Client;
    Client.AccountNumber = accountnumber;

        cout <<"Enter Name: ";
        getline(cin >> ws,Client.Name);

        cout <<"Enter Pincode: ";
        getline(cin ,Client.Pincode);

        cout <<"Enter Phone: ";
        getline(cin ,Client.Phone);

        cout <<"Enter Balance: ";
        cin >> Client.AccountBalance;

    return Client;

 }

//todo ---> this method for updating data for existing client
void UpdateClientsData(string accountnumber, vector<stClientInfo>&Client_list)
{
    //first creat a temp client to do operation on it
    stClientInfo Client;  char Up = 'n'; 

    // second search if client exist or not
    if(FindClientByAccountNumber(accountnumber, Client_list, Client))
    {
        Print_AclientInfo(Client);

        cout <<"Are you sure you want to update this client ? ";
        cin >> Up;
        if(Up == 'y' || Up == 'Y')
        {
            for(stClientInfo &c : Client_list)
            {
                if(accountnumber == c.AccountNumber)
                {
                    c = ReUpdate_A_clientData(accountnumber);// read new data to client
                    break;         
                }
            }

            SaveDataToFile(CLientsFilename,Client_list); // save the new data to file
            cout <<"The Client has been Updated sucsesfully\n";
            // update the list after modification a client
            Client_list = Import_ClientDataFromFile(CLientsFilename);
        
        }
    }
    else
    {
        cout <<"The Client With Account number "<<accountnumber<<" is not found\n";
    }

}

void Find_SpeceficClient(string accountnumber, vector<stClientInfo>Client_list)
{
    stClientInfo Client;
    if(FindClientByAccountNumber(accountnumber, Client_list, Client))
    {
        Print_AclientInfo(Client);
    }

    else
    {
        cout <<"The client with accountnumber "<<accountnumber <<" is not found\n";
    }   
}

void PrintMainMenueScreen()
{
    system("cls");
    cout <<"\n========================================================\n";
    cout <<"                 Main Menue Screen                          ";
    cout <<"\n========================================================\n";
    
    cout <<"        [1] Show Client List\n";
    cout <<"        [2] Add New Client\n";
    cout <<"        [3] Delete Client\n";
    cout <<"        [4] Update Client\n";
    cout <<"        [5] Find Client\n";
    cout <<"        [6] Transactions Menue \n";
    cout <<"        [7] Manage Users Menue \n";
    cout <<"        [8] Log Out \n";

}

string ReadAccountNumber()
{
    string accounNum;
    cout <<"Please Enter The account Number: ";
    cin >> accounNum;

    return accounNum;
}

void GoBackToMainMenue()
{
    cout <<"\nPress Any Key To Go Back To Main Menue...\n";
    system("Pause>0"); 
    PrintMainMenueScreen();           
}

void AddClientScreen(vector<stClientInfo>&Client_list)
{
    
    if(!CheckAccesPermissions(enPermissions::pAddClients))
    {
        ShowAccessDeniedMessage();
        return;
    }

    stClientInfo Client;
    string accountnumber;
    char again;
    cout <<"\n------------------------------------------\n";
    cout <<"            Adding New Client Screen          ";
    cout <<"\n-------------------------------------------\n";
    cout <<"Adding Client: \n";

    do
    {
        accountnumber = ReadAccountNumber();
        if(FindClientByAccountNumber(accountnumber,Client_list,Client))
        {
            cout <<"The Client [ "<< accountnumber <<" ] is already exist, Please Enter Another id: ";
             // or break and call main menue
        }

        else
        {
            Client  = ReadClientFromUser();
            Client_list.push_back(Client);
            SaveDataToFile(CLientsFilename,Client_list);
            // Client_list = Import_ClientDataFromFile(CLientsFilename);
            cout <<"Client has been added sucesfully\n";
            cout <<"Do you want to add more clients: y , n\n";
            cin >> again;
            if(again == 'n' || again == 'N')
            {
                break;
            }
        }
    } while (true);
    
         
}

void Delete_ClientScreen(vector<stClientInfo>&Clients_list)
{
    if(!CheckAccesPermissions(enPermissions::pDeleteClients))
    {
        ShowAccessDeniedMessage();
        return;
    }


    cout <<"\n------------------------------------------\n";
    cout <<"            Delete Clients Screen             ";
    cout <<"\n--------------------------------------------\n";
    
    // stClientInfo Client;
    string accountnumber;

    accountnumber = ReadAccountNumber();
    
    DeleteClientFromData(accountnumber,Clients_list);
}

void UpdateClientsScreen(vector<stClientInfo>&Clients_list)
{
    if(!CheckAccesPermissions(enPermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        return;
    }


    cout <<"\n------------------------------------------\n";
    cout <<"            Update Clients Screen             ";
    cout <<"\n------------------------------------------\n";
    
    string accountnumber = ReadAccountNumber();
    UpdateClientsData(accountnumber,Clients_list);
    // GoBackToMainMenue();
    // PrintMainMenueScreen();
}

void FindClientScreen(vector<stClientInfo>Clients_list)
{
    if(!CheckAccesPermissions(enPermissions::pFindClients))
    {
        ShowAccessDeniedMessage();
        return;
    }


    cout <<"\n------------------------------------------\n";
    cout <<"            Find Clients Screen               ";
    cout <<"\n------------------------------------------\n";
    
    string accountnumber = ReadAccountNumber();

    Find_SpeceficClient(accountnumber,Clients_list);
 
}

void FinishedScreen()
{
    system("cls");
    cout <<"\n============================\n";
    cout <<"     Programm Finisehed         ";
    cout <<"\n============================\n";
}

void StartBankOperations(vector<stClientInfo>&Clients_list)
{
    short choice;
    PrintMainMenueScreen();
    
    while (true)
    {
        cout <<"Enter your choice [1 - 8] : ";
        cin >> choice;
        cin.ignore();

        switch (enCrudOperations(choice))
        {
            case enCrudOperations::ShowList:
                system("cls");
                Print_Clientlist_Data(Clients_list);
                GoBackToMainMenue();
                break;             
                
            case enCrudOperations::AddClient:
                system("cls");
                AddClientScreen(Clients_list);
                GoBackToMainMenue();
                break;             
                
            case enCrudOperations::DeleteClient:
                system("cls");    
                Delete_ClientScreen(Clients_list); 
                GoBackToMainMenue();
                break;             
                
            case enCrudOperations::UpdateClient:
                system("cls");
                UpdateClientsScreen(Clients_list);
                GoBackToMainMenue();
                break;             
            
            case enCrudOperations::FindClient:
                system("cls");
                FindClientScreen(Clients_list);
                GoBackToMainMenue();
                break;
                
            case enCrudOperations::TransMenue:
                system("cls");
                PrintTransactionMenue();
                StartBank_Entensions(Clients_list);
                break;

            case enCrudOperations::ManageUserMenue:
                 system("cls");
                 PrintMangeUsersMenue();
                 StartUsersOperations();
                 break;
   

            case enCrudOperations::Exit:
                //FinishedScreen();
                break;             
            
              
        }
        
        if(choice == 8)
        {
            
            break;
        } 
            
        
    }

    Login();
    
}

//===============================================================================================
//                                                                                              =
//                            The second Part Of Extensions Of the Bank                         =
//                                                                                              =
//===============================================================================================   





/* #include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
 */
enum enTransMenue {Deposit = 1, Withdraw, TotalBalances, MainMenue};

double AmmountOfMoney()
{
    double ammount;
    do
    {
        cout <<"Please Enter the ammount of money: ";
        cin  >> ammount;
    
    } while (ammount <= 0 );
    
    return ammount;
}

void ShowMainMenue()
{
    GoBackToMainMenue();
}

void Deposit_Money(string accountnumber,vector<stClientInfo> &vClients)
{
    // string accountnumber = ReadAccountNumber;
    stClientInfo client;  char AddAmount;
    if(FindClientByAccountNumber(accountnumber,vClients,client))
    {
        Print_AclientInfo(client);
        cout <<"\nAre you sure you want to perform this transaction ? ";
        cin >> AddAmount;
        if(AddAmount == 'y' || AddAmount == 'Y')
        {
            for(stClientInfo &C : vClients)
            {
                if(accountnumber == C.AccountNumber)
                {
                    C.AccountBalance += AmmountOfMoney();
                    cout <<"The deposit has been added sucesfully your balance became : "<<C.AccountBalance<<endl;
                    break;
                }
            }
            SaveDataToFile(CLientsFilename,vClients);
        }
    }

    else
    {
        cout <<"The [ "<<accountnumber <<" ] you Entered is not exsist\n";
    }

}


void WithDraw_Money(string accountnumber,vector<stClientInfo> &vClients)
{
    // string accountnumber = ReadAccountNumber();
    stClientInfo Client; char discount;
    if(FindClientByAccountNumber(accountnumber,vClients,Client))
    {
        Print_AclientInfo(Client);
        cout <<"\nAre you sure you want to perform this transaction ? ";
        cin >> discount;
        if(discount == 'y' || discount == 'Y')
        {
            double Balance = Client.AccountBalance;
            double MoneyToWithdraw ;
            do
            {
                MoneyToWithdraw = AmmountOfMoney();
                if(MoneyToWithdraw <= Balance)
                {
                    for(stClientInfo &C : vClients)
                    {
                        if(accountnumber == C.AccountNumber)
                        {
                            C.AccountBalance -= MoneyToWithdraw;
                            cout <<"The transaction has been Done sucesfully your balance became : "<<C.AccountBalance<<endl;
                            break;                            
                        }
                    }
                }
                else
                {
                    cout <<"Ammount Exceeds the balance, you can withdraw up to :"<<Client.AccountBalance<<endl;
                    cout <<"Please Enter Another ammount \n\n";
                    //  MoneyToWithdraw = AmmountOfMoney();
                }    
            } while (MoneyToWithdraw > Balance);

            SaveDataToFile(CLientsFilename,vClients);
            
        }

    }

    else
    {
        cout <<"The [ "<<accountnumber <<" ] you Entered is not exsist\n";
    }
}


void PrintClient_SpeceficRecord(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;  
    cout << "| " << setw(30) << left << Client.Name;  
    cout << "| " << setw(12) << left << Client.AccountBalance; 
}


void ShowClients_TotalBalances(vector<stClientInfo> vClients)
{
    double TotalBalances = 0;
    cout <<"\n\t\t\t\t\tclientlist( "<<vClients.size()<<" ) clients";
    cout <<
    "\n__________________________________________________________________";
    cout <<"_____________________________________________________________\n"<<endl;

    cout <<"| "<<left << setw(15) <<"Account Number";
    cout <<"| "<<left << setw(30) <<"Client Name";
    cout <<"| "<<left << setw(12) <<"Balance";
    cout <<
    "\n__________________________________________________________________";
    cout<<"______________________________________________________________\n"<<endl;

    for(stClientInfo client : vClients)
    {
        PrintClientRecord(client);
        TotalBalances += client.AccountBalance;
        cout << endl;
    }
    cout <<"\nThe Total balances is: "<<to_string(TotalBalances)<<endl;
}


void PrintTransactionMenue()
{

    if(!CheckAccesPermissions(enPermissions::pTransactions))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout <<"\n==================================================\n";
    cout <<"\t\t Transactions Menue Screen                      \n";
    cout <<"====================================================\n";

    cout <<"[1]Deposit\n";
    cout <<"[2]Withdraw\n";
    cout <<"[3]TotalBalances\n";
    cout <<"[4]Main Menue\n";
    cout <<"------------------------\n";
}

void Display_DepositScreen(vector<stClientInfo> &vClients)
{
    cout <<"\n=========================================\n";
    cout <<"\t\t Deposit Screen                        \n";
    cout <<"===========================================\n";

    string accountnumber = ReadAccountNumber();
    Deposit_Money(accountnumber,vClients);
}

void Display_WithdrawScreen(vector<stClientInfo> &vClients)
{
    cout <<"\n=========================================\n";
    cout <<"\t\t Withdraw Screen                       \n";
    cout <<"===========================================\n";

    string accountnumber = ReadAccountNumber();
    WithDraw_Money(accountnumber,vClients);
}

void Display_TotalBalances(vector<stClientInfo> vClients)
{
    ShowClients_TotalBalances(vClients);
    cout <<" \n";
}

void GoBackToTransMenue()
{
    cout <<"\n\nPlease Enter Any Key To Go Back To Trans Menue...";
    system("Pause>0");
    system("cls");
    PrintTransactionMenue();
}

void StartBank_Entensions(vector<stClientInfo> &vClients)
{

    if(!CheckAccesPermissions(enPermissions::pTransactions))
    {
        ShowAccessDeniedMessage();
        return;
    }


    short Make_Choice;
    
    while(true)
    {
        cout <<"\nPlease Enter Your Choice From [1-4]: ";
        cin >> Make_Choice;

        switch (enTransMenue(Make_Choice))
        {
        case enTransMenue::Deposit:
            system("cls");
            Display_DepositScreen(vClients);
            GoBackToTransMenue();
            break;
        
        case enTransMenue::Withdraw:
            system("cls");
            Display_WithdrawScreen(vClients);
            GoBackToTransMenue();
            break;
        
        case enTransMenue::TotalBalances:
            system("cls");
            Display_TotalBalances(vClients);
            GoBackToTransMenue();
            break;
            
        case enTransMenue::MainMenue:
            system("cls");
            PrintMainMenueScreen();
            // GoBackToMainMenue();
            break;
        }

        if(Make_Choice == 4) break;
    }
    
}



//===============================================================================================
//                                                                                               =
//                            The thir Part Of Extensions Of the Bank                            =
//                                 The USers Part                                                              =
//===============================================================================================


bool CheckAccesPermissions(enPermissions Permission)
{
    if(CurrentUser.permissions == enPermissions::All)
        return true;

    if((CurrentUser.permissions & Permission) == Permission) 
        return true;
        
    else
        return false;    
}


vector<string> Split_String2(string line ,string Delim = "#//#")
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
        Myfile << line << endl;
    }

    Myfile.close();
}


bool FindUserByUsernameAndPassword(string Username, string Password,stUser &User)
{
    vector<stUser> Users = ImportUsersDataFromFile(UsersDataFile);

    for(stUser &U : Users)
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
        cout <<"Do yiu want to add new user ? y/n  ";
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

    if(!CheckAccesPermissions(enPermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        return;
    }


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


    if(!CheckAccesPermissions(enPermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        return;
    }



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
             PrintMainMenueScreen();     
             break;     
        }
        
        if(enMangaeUsers(choice) == enMangaeUsers::Mainmenue) break;
    }
    
}

void LoginScreen()
{
    system("cls");

    cout <<"\n==============================\n\n";
    cout <<"\t\tLoginScreeen                \n\n";
    cout <<"================================\n\n";
}
void Login()
{
    //LoginScreen();
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

    
     vector<stClientInfo>Clients_list = Import_ClientDataFromFile(CLientsFilename);
     StartBankOperations(Clients_list);

}





//=================================================================================================
 int main()
    {
        Login();  
    } 