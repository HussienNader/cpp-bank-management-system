#pragma once
#include "../clsScreen.h"
#include "../clsBankClient.h"
#include <iostream>
#include <iomanip>

class clsTransferLogScreen : protected clsScreen
{

private:

    static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.sourceAccount;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccount;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.SourcBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.DestinationBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.User;

      
    }

public:

    static void ShowTransferLogScreen()
    {

        vector<clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogRecordsList();

        string Title = "\t  Transfer Log screen";
        string Subtitle = "( " + to_string(vTransferLogRecord.size()) + " ) ";
        
        _DrawScreenHeader(Title,Subtitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }





   

};