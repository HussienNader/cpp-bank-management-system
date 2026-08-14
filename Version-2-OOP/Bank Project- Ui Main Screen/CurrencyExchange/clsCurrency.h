#pragma once
#include "../clsString.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class clsCurrency
{

private:
    enum enMode{UpdateMode = 1,EmptyMode = 2};

    enMode _Mode;
    string _CountryName;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;



    static clsCurrency _ConvertCurrencyLineToRecord(string DataLine ,string separator="#//#")
    {
        vector<string> vCurrencies = clsString::Split(DataLine,separator);

        return clsCurrency(enMode::UpdateMode,vCurrencies[0],vCurrencies[1],vCurrencies[2],stof(vCurrencies[3]));

    }


    static string _ConvertCurrencyRecordToline(clsCurrency Currency ,string separator="#//#")
    {
        string CurrencyLine = "";

        CurrencyLine += Currency.CountryName() + separator;
        CurrencyLine += Currency.CurrencyCode() + separator;
        CurrencyLine += Currency.CurrencyName() + separator;
        CurrencyLine += to_string(Currency.Rate());

        return CurrencyLine;
    }

    static vector<clsCurrency> _LoadCurreciesDataFromFile()
    {
        vector<clsCurrency> vCurrencies;

        fstream Myfile;
        Myfile.open("Currencies.txt",ios:: in); // read mode

        if(Myfile.is_open())
        {
            string DataLine = "";
            while (getline(Myfile,DataLine))
            {
                clsCurrency Currency = _ConvertCurrencyLineToRecord(DataLine);
                vCurrencies.push_back(Currency);
            }

            Myfile.close();
        }

        return vCurrencies;
    }


    static clsCurrency _GetEmptyCurrencyObj()
    {
        return clsCurrency(enMode::EmptyMode,"","","",0);
    }

    static void _SaveCurrenciesDataToFile(vector<clsCurrency>vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt",ios:: out);// write mode    
        
        if(MyFile.is_open())
        {
            for(clsCurrency C1 : vCurrencies)
            {
                MyFile << _ConvertCurrencyRecordToline(C1) << endl;
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> vCurrencies = _LoadCurreciesDataFromFile();

        for(clsCurrency &C1 : vCurrencies)
        {
            if(C1.CurrencyCode() == this->CurrencyCode())
            {
                C1 = *this;
                break;
            }
        }

        _SaveCurrenciesDataToFile(vCurrencies);
    }

public:
    
    clsCurrency(enMode mode,string Countryname, string currencycode,string currencyname, float rate)
    {
        _Mode = mode;
        _CountryName = Countryname;
        _CurrencyCode = currencycode;
        _CurrencyName = currencyname;
        _Rate = rate;

    }


    string CountryName()
    {
        return _CountryName;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    float Rate()
    {
        return _Rate;
    }


    bool IsEmpty()
    {
        return _Mode == enMode::EmptyMode;
    }


    static clsCurrency FindCurrencyByCountryName(string CountryName)
    {
        string DataLine = "";

        CountryName = clsString::UpperAllString(CountryName);

        fstream  MyFile;
        MyFile.open("Currencies.txt",ios::in);// read mode

        if(MyFile.is_open())
        {
            while (getline(MyFile,DataLine))
            {
                clsCurrency Currency = _ConvertCurrencyLineToRecord(DataLine);
                if((clsString::UpperAllString(Currency.CountryName()) == CountryName))
                {
                    MyFile.close();
                    return Currency;
                }
            }
            
        }

        return _GetEmptyCurrencyObj();
    }


    static clsCurrency FindCurrencyByCurrencyCode(string CurrencyCode)
    {
        string DataLine = "";

        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        fstream  MyFile;
        MyFile.open("Currencies.txt",ios::in);// read mode

        if(MyFile.is_open())
        {
            while (getline(MyFile,DataLine))
            {
                clsCurrency Currency = _ConvertCurrencyLineToRecord(DataLine);
                if(Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            
        }

        return _GetEmptyCurrencyObj();
    }


    void UpdateRate(float rate)
    {
        _Rate = rate;
        _Update();
    }

    
    static bool IsCurrencyExistByCurrencyCode(string CurrencyCode)
    {
        clsCurrency Currency  = FindCurrencyByCurrencyCode(CurrencyCode);

        return (!Currency.IsEmpty());
    }


    static bool IsCurrencyExistByCountryName(string CountryName)
    {
        clsCurrency Currency  = FindCurrencyByCountryName(CountryName);

        return (!Currency.IsEmpty());
    }


    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurreciesDataFromFile();
    }
};