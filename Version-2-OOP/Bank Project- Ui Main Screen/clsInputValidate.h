#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"

using namespace std;


class clsInputValidate
{

public:
    static bool IsNumberBetween(short Number, short From, short To)
    {
        return (Number >= From && Number <= To);
    }


    static bool IsNumberBetween(int Number, int From, int To)
    {
        return (Number >= From && Number <= To);
    }


    static bool IsNumberBetween(float Number, float From, float To)
    {
        return (Number >= From && Number <= To);
    }

    static bool IsNumberBetween(double Number, double From, double To)
    {
        return (Number >= From && Number <= To);
    }

    
    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        short Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }


    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        short Number = ReadShortNumber();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadShortNumber();
        }
        return Number;
    }


    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        // first case
        if((clsDate::IsDate1AfterDate2(Date,From) || clsDate::IsDat1EqualDate2(Date,From))
           
            &&

            (clsDate::IsDate1BeforeDate2(Date,To) || clsDate::IsDat1EqualDate2(Date,To))
        )
        {
            return true;
        }



        // second case
        if((clsDate::IsDate1AfterDate2(Date,To) || clsDate::IsDat1EqualDate2(Date,To))
           
            &&

            (clsDate::IsDate1BeforeDate2(Date,From) || clsDate::IsDat1EqualDate2(Date,From))
        )
        {
            return true;
        }

        return false;
    }


    static int ReadIntNumber(string ErrorMessage="Invalid Number, Enter again\n")
    {
        int Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        
        return Number;
    }


    static int ReadIntNumberBetween(int From, int To, string ErrorMessage="Number is not within range, Enter again:\n")
    {
        int Number = ReadIntNumber();
        
        while (!IsNumberBetween(Number,From,To)) 
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}

		return Number;
    }


        static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
        {
            float Number;
            while (!(cin >> Number))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ErrorMessage;
            }
            return Number;
        }

        static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
        {
            float Number = ReadFloatNumber();
            while (!IsNumberBetween(Number, From, To))
            {
                cout << ErrorMessage;
                Number = ReadFloatNumber();
            }
            return Number;
        }


    
	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        double Number;

        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }

        return Number;
    }


    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number,From,To))
        {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }

        return Number; 
    }


    static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}


    static string ReadString()
    {
        string st = "";

        getline(cin >> ws, st);
        return st;
    }

};
