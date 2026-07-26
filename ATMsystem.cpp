#include <iostream>
#include "Header.h"
using namespace std;


stClientInfo CurrentClient;

enum enATMChoice {C_QuickWithDraw = 1, C_NormalWithdraw, C_Deposit,CheckBalance,C_LogOut};

// forward declaration
 void Login_Client();


bool FindClientByUsernameAndPassword(string Username, string Password,stClientInfo &Client)
{
    vector<stClientInfo> vClients = Import_ClientDataFromFile(CLientsFilename);

    for(stClientInfo C : vClients)
    {
        if(C.Name == Username && C.Pincode == Password)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

bool LoadClientData(string Username,string Password)
{
    if(FindClientByUsernameAndPassword(Username,Password,CurrentClient))
        return true;
    
    else
        return false;
}


bool IsMultpleOfFive(int Amount)
{
    return (Amount % 5 == 0);
}


void SaveCuerrentClietDataToFile(string FileName)
{
    vector<stClientInfo> vClients = Import_ClientDataFromFile(CLientsFilename);
    fstream MyFile;
    MyFile.open(FileName,ios::out);

    if(MyFile.is_open())
    {
        string Line;
        for(stClientInfo &C : vClients)
        {
            if(C.AccountNumber == CurrentClient.AccountNumber)
                C = CurrentClient;

            MyFile << ConverRecordToLne(C) << endl;    
        }

        MyFile.close();
        
    }

}


void QuickWithDrawForClient(int Ammount)
{
   if(CurrentClient.AccountBalance >= Ammount)
   {
      CurrentClient.AccountBalance -= Ammount;
      cout <<"\nThe transaction has been Done sucesfully your balance became : "<<CurrentClient.AccountBalance<<endl;
      SaveCuerrentClietDataToFile(CLientsFilename);
   }

   else
        cout <<"Ammount Exceeds the balance, you can withdraw up to :"<<CurrentClient.AccountBalance<<endl;

}


void DepositMoneyForCurrentClient()
{
       int Amount;  char Answer;

    do
    {
        cout <<"Enter A possitive Ammount: ";
        cin >> Amount;
    } while (Amount <= 0);

    cout <<"Are You sure you want to perform this transaction";
    cin >> Answer;
    if(tolower(Answer) == 'y')
    {
        CurrentClient.AccountBalance += Amount;
        cout <<"Done Successfuly. Your Balance Now is: "<<CurrentClient.AccountBalance<<endl;
        SaveCuerrentClietDataToFile(CLientsFilename);
    }
}


void PrintATM_MainMenueScreen()
{
    system("cls");
    cout <<"\n================================================\n";
    cout <<"\t\t ATM Main Menue Screen                          ";
    cout <<"\n================================================\n";
    
    cout <<"\t[1]Quick Withdraw\n";
    cout <<"\t[2]Normal Withdraw\n";
    cout <<"\t[3]Deposit\n";
    cout <<"\t[4]Check Blalnce\n";
    cout <<"\t[5]Log Out\n";
    cout <<"=================================================\n";

}

void ShowQuickWithdrawScreenForCuurentClient()
{
    system("cls");
    cout <<"\n============================================\n";
    cout <<"\t\t Quick WithDraw Screen                      ";
    cout <<"\n============================================\n";
    cout <<"\t\t[1] 20\t\t[2] 50\n";
    cout <<"\t\t[3] 100\t\t[4] 200\n";
    cout <<"\t\t[5] 400\t\t[6] 600\n";
    cout <<"\t\t[7] 800\t\t[8] 1000\n";
    cout <<"\t\t[9] Exit";
    cout <<"\n============================================\n";
    cout <<"Your Balance: "<<CurrentClient.AccountBalance << endl;

    int choice;
    cout <<"Choose What To Withdraw From [1 - 8] ";
    cin >> choice;
    if(choice == 9)
        return;
    // if choice == 9 go back to Atm Screen
    int withdrawAmount[]{20,50,100,200,400,600,800,1000};
    int Amount = withdrawAmount[choice-1];
    QuickWithDrawForClient(Amount);
}


void ShowNormalWithdrawScreenForCuurentClient()
{
    int Amount;  char Answer;
    
    system("cls");
    cout <<"\n=============================================\n";
    cout <<"\t\t Quick WithDraw Screen                       ";
    cout <<"\n=============================================\n";

    do
    {
        cout <<"Enter Amount Multiple Of 5 : ";
        cin >> Amount;
    } while (!IsMultpleOfFive(Amount));
    
    cout <<"\nAre You sure you want to perform this transaction";
    cin >> Answer;
    if((tolower(Answer)) == 'y')
    {
        QuickWithDrawForClient(Amount);
    }
}


void ShowDepositScreenForCuurentClient()
{
 
    
    system("cls");
    cout <<"\n=============================================\n";
    cout <<"\t\t Deposit Screen                              ";
    cout <<"\n=============================================\n";
       
    DepositMoneyForCurrentClient();   
}


void ShowCheckBlalnceScreenForCurrentUser()
{
    system("cls");
    cout <<"\n============================================\n";
    cout <<"\t\t Check Blalnce Screen                       ";
    cout <<"\n============================================\n";

    cout <<"Your Balance Is : "<<CurrentClient.AccountBalance<<endl;
}


void GoBackToATM_MainMenue()
{
    cout <<"\n\n\nPress Any Key To GoBack To MainMenue...\n";
    system("Pause>0");
    PrintATM_MainMenueScreen();
}


void StartATMsystem()
{
    int choice;
    PrintATM_MainMenueScreen();
    while (true)
    {
        cout <<"Make Your Choice From [1 - 5]:";
        cin >> choice;

        switch (enATMChoice(choice))
        {
        case enATMChoice::C_QuickWithDraw:
            ShowQuickWithdrawScreenForCuurentClient();
            GoBackToATM_MainMenue();
            break;
        
        case enATMChoice::C_NormalWithdraw:
            ShowNormalWithdrawScreenForCuurentClient();
            GoBackToATM_MainMenue();
            break;

        case enATMChoice::C_Deposit:
            ShowDepositScreenForCuurentClient();
            GoBackToATM_MainMenue();
            break;

        case enATMChoice::CheckBalance:
            ShowCheckBlalnceScreenForCurrentUser();
            GoBackToATM_MainMenue();
            break;
            
        case enATMChoice::C_LogOut:
            break;
        }

        if(choice == 5) break;
    }
    
    Login_Client();
}


void Login_Client()
{
    string CUserName, CPassword;
    bool LoginFailed = false;

    system("cls");
    cout <<"\n===================================================\n";
    cout <<"\t\t LogIn Screen                                      ";
    cout <<"\n===================================================\n";

    do
    {
        if(LoginFailed)
            cout <<"You Enterd An InValid Username/Password\n";

        cout <<"Please Enter A Valid UserName/Password\n";
        
        cout <<"\nEnter User Name: ";
        cin >> CUserName;
        cout <<"Enter Password: ";
        cin >> CPassword;

        LoginFailed = !LoadClientData(CUserName,CPassword);

    } while (LoginFailed);

    StartATMsystem();
    
}

int main()
{
    Login_Client();
}