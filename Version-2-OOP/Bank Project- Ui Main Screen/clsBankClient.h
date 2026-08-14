#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{

public:

    struct stTransferLogRecord
    {
        string DateTime;
        string sourceAccount;
        string DestinationAccount;
        float Amount;
        float SourcBalance;
        float DestinationBalance;
        string User;
        
    };

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1,AddNewMode = 3 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool   _MarkedToDelete;


     static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
     {
         
        vector<string> vClientData = clsString::Split(Line,Seperator);

        return  clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],vClientData[2],vClientData[3],
                               vClientData[4],vClientData[5], stod(vClientData[6]));
     }


    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios:: in); // read mode

        if(MyFile.is_open())
        {
            string DataLine = "";
            while (getline(MyFile,DataLine))
            {
                clsBankClient Client = clsBankClient:: _ConvertLinetoClientObject(DataLine);
                vClients.push_back(Client);
            }

            MyFile.close();
        }


        return vClients;
    }



    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {
        string DataLine = "";
        fstream MyFile;

        MyFile.open("Clients.txt", ios:: out);
        if(MyFile.is_open())
        {
            for(clsBankClient c : vClients)
            {
                if(c.MarkedToDelete() == false)
                {
                    DataLine =  _ConverClientObjectToLine(c);
                    MyFile << DataLine << endl;
                }
            }
        }

        MyFile.close();
    }


     void _Update()
     {
        vector<clsBankClient> vClients;
        
        vClients = _LoadClientsDataFromFile();
        for(clsBankClient &c: vClients)
        {
            if(c.AccountNumber() == this-> AccountNumber())
            {
                c = *this;
                break;
            }
        }

        _SaveCleintsDataToFile(vClients);
     }
    

     void _AddNew()
     {
        _AddDataLine(_ConverClientObjectToLine(*this));
     }

    
    void _AddDataLine(string line)
    {
        fstream MyFile;
        MyFile.open("Clients.txt",ios::out | ios::app);

        if(MyFile.is_open())
        {
            MyFile << line << endl;
        }

        MyFile.close();
    } 


    string _PrepareTransferRecord(clsBankClient Destination ,float Amount,  string separator = "#//#")
    {
        string TransferRecord = "";

        TransferRecord +=  clsDate::GetSystemTimeInString() + separator;
        TransferRecord +=  this->AccountNumber() + separator;
        TransferRecord +=  Destination.AccountNumber() + separator;
        TransferRecord +=  to_string(Amount) + separator;
        TransferRecord +=  to_string(this->GetAccountBalance()) + separator;
        TransferRecord +=  to_string(Destination.GetAccountBalance()) + separator;
        TransferRecord +=  CurrentUser.GetUserName();
        
        return TransferRecord;
    }


    void _RegisterTransfer(clsBankClient Destination, float Amount)
    {
        string DataLine = _PrepareTransferRecord(Destination ,Amount);

        fstream MyFile;
        MyFile.open("TransferRegister.txt",ios:: out | ios:: app);

        if(MyFile.is_open())
        {
            MyFile << DataLine << endl;
            
            MyFile.close();
        }


    }


    static stTransferLogRecord _ConvertTransferLogToRecord(string line,string separator = "#//#")
    {
        vector<string> vTransferLog = clsString::Split(line,separator);

        stTransferLogRecord TransferLogRecord;

        TransferLogRecord.DateTime = vTransferLog[0];
        TransferLogRecord.sourceAccount = vTransferLog[1];
        TransferLogRecord.DestinationAccount = vTransferLog[2];
        TransferLogRecord.Amount = stof(vTransferLog[3]);
        TransferLogRecord.SourcBalance = stof(vTransferLog[4]);
        TransferLogRecord.DestinationBalance = stof(vTransferLog[5]);
        TransferLogRecord.User = vTransferLog[6];

        return TransferLogRecord;
    }

    static vector<stTransferLogRecord> _LoadTransferLogRecords()
    {
        vector<stTransferLogRecord> vTrsanferRecords;

        fstream MyFile;

        MyFile.open("TransferRegister.txt",ios::in); //read

        if(MyFile.is_open())
        {
            string Dataline;
            stTransferLogRecord TransferLogRecord;
            
            while (getline(MyFile,Dataline))
            {
                TransferLogRecord = _ConvertTransferLogToRecord(Dataline); 
                vTrsanferRecords.push_back(TransferLogRecord);  
            }
            
            MyFile.close();
        }

        return vTrsanferRecords;
    }
public:
    
    clsBankClient(enMode mode,string firstname, string lastname, string email ,string Phone,
                    string accountnumber, string pincode, double accountbalance):
                    clsPerson(firstname,lastname,email,Phone)
    {
        _AccountNumber = accountnumber;
        _PinCode = pincode;
        _AccountBalance = accountbalance;
        _MarkedToDelete = false;
        _Mode = mode;
    }                

        // Getter for MarkedToDelete
        bool MarkedToDelete() const
        {
            return _MarkedToDelete;
        }

        // Setter for MarkedToDelete
        void SetMarkedToDelete(bool value)
        {
            _MarkedToDelete = value;
        }

        // Property declaration for MarkedToDelete
        // __declspec(property(get = MarkedToDelete, put = SetMarkedToDelete)) bool _MarkedToDelete;

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }


     void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    // __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    // __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFirstName();
        cout << "\nLastName    : " << GetLastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << GetPinCode();
        cout << "\nBalance     : " << GetAccountBalance();
        cout << "\n___________________\n";

    }


    static clsBankClient Find(string AccountNumber)
    {
        vector<clsBankClient> vBankClients;

        fstream MyFile;
        string line = "";
        MyFile.open("Clients.txt",ios::in); // read mode
        if(MyFile.is_open())
        {
            while (getline(MyFile,line))
            {
                 clsBankClient Client = _ConvertLinetoClientObject(line,"#//#");
                 if(Client.AccountNumber() == AccountNumber)
                 {
                    MyFile.close();
                    return Client; 
                 }
            }

             MyFile.close();
        }
        
        return GetEmptyClientObject();
    }


    
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector<clsBankClient> vBankClients;

        fstream MyFile;
        string line = "";
        MyFile.open("Clients.txt",ios::in); // read mode
        if(MyFile.is_open())
        {
            while (getline(MyFile,line))
            {
                 clsBankClient Client = _ConvertLinetoClientObject(line,"#//#");
                 if(Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                 {
                    MyFile.close();
                    return Client; 
                 }
            }
        }
        
        return GetEmptyClientObject();
    }


    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = Find(AccountNumber);

        return (!Client.IsEmpty());
    }


    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
     {
       
        string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;

    }


    static clsBankClient GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode,"","","","","","",0);
    }



    static clsBankClient  GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }


    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    
    static double GetTotalBalances()
    {
        double TottalBalnces = 0;
        vector<clsBankClient>vCLients = GetClientsList();

        for(clsBankClient Client : vCLients)
        {
            TottalBalnces += Client.GetAccountBalance();
        }

        return TottalBalnces;
    }


    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save()
    {
        enSaveResults Result;
        switch (_Mode)
        {
            case enMode::EmptyMode:
                Result =  enSaveResults::svFaildEmptyObject;
                break;

            case enMode::UpdateMode:
                _Update();
                Result =  enSaveResults::svSucceeded;    
                break;
                
            case enMode::AddNewMode:
                if(clsBankClient::IsClientExist(_AccountNumber))
                {
                    Result = enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;

                    Result =  enSaveResults::svSucceeded;
                    break;
                }
        
        }
          return Result;
    }


    bool Delete()
    {
        vector<clsBankClient> vClients;

        vClients = _LoadClientsDataFromFile();
        
        for(clsBankClient &C : vClients)
        {
            if(C.AccountNumber() == AccountNumber())
            {
                C.SetMarkedToDelete(true);
                break;
            }
        }

        _SaveCleintsDataToFile(vClients);

        *this = GetEmptyClientObject();

        return true;
    }


    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }


    bool Withdrawl(double Amount)
    {
        if(Amount > _AccountBalance)
            return false;
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }    
    }

    
    bool Transfer(float Amount, clsBankClient &DestinationClient)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
    
        Withdrawl(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransfer(DestinationClient,Amount);
        return true;
    }
    
    static vector<stTransferLogRecord> GetTransferLogRecordsList()
    {
        return _LoadTransferLogRecords();
    }
    
};