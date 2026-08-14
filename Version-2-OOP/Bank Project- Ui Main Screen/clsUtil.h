#pragma oncce
#include<iostream>
#include<string>
#include "clsDate.h"

using namespace std;

class clsUtil
{

public:
       enum enCharType {
        SamallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
        };
    
   static void Srand()
   {
      srand((unsigned)time(nullptr));
   }


   static int RandomNumber(int From, int To)
   {
      return rand() % (To - From + 1) + From;
   }


   static char GetRandomCharacter(enCharType chartype)
   {

      if(chartype == MixChars)
      {
         chartype = enCharType(RandomNumber(1,3));
      }    
      char ch;
      switch (chartype)
      {
        case enCharType::CapitalLetter:
           ch = char(RandomNumber(65,90));
            break;
        case enCharType::SamallLetter:
           ch = char(RandomNumber(97,122));
           break;

        case enCharType::Digit:
           ch = char(RandomNumber(48,57)); 
           break;

        case enCharType::SpecialCharacter:
           ch = char(RandomNumber(33,47));
           break;
        default:
            ch = char(RandomNumber(65,90));   
          break;
      }

      return ch;
   }


   static string  GenerateWord(enCharType chartype, short length = 4)
   {
      string word = "";
      for (int i = 1; i <= length; i++)
      {
            word += GetRandomCharacter(chartype);
      }

      return word;
   }


   static string  GenerateKey(enCharType CharType = CapitalLetter, short length = 4)
   {
      string key = "";

      for(int i = 1; i <= length; i++)
      {
        if(i < length)
              key += GenerateWord(CharType) + "-";
        else
              key += GenerateWord(CharType);
      }

      return key;
   }

   static void GenerateKeys(short NumberOfKeys, enCharType CharType)
   {
      for (int i = 1; i <= NumberOfKeys; i++)
      {
         cout << "Key [" << i << "] : ";
         cout << GenerateKey(CharType) << endl;
      }
      
   }

   static void FillArrayWithRandomNumbers(int arr[], int arrLength, int From, int To)
   {
      for (int i = 0; i < arrLength; i++)
      {
         arr[i] = RandomNumber(From,To);
      }
      
   }


   static void FillArrayWithRandomWords(string arr[], int arrLength, enCharType CharType, short Wordlength)
   {
      for (int i = 0; i < arrLength; i++)
      {
         arr[i] = GenerateWord(CharType, Wordlength);
      }
      
   }


   static void FillArrayWithRandomKeys(string arr[], int arrLength, enCharType CharType)
   {
      for (int i = 0; i < arrLength; i++)
      {
         arr[i] = GenerateKey(CharType);
      }
      
   }


    static  void Swap(int& A, int& B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }


    static  void Swap(double& A, double& B)
    {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(char& A, char& B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(string& A, string& B)
    {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }


    
    static  void Swap(clsDate& A, clsDate& B)
    {
        clsDate::SwapDates(A, B);

    }


    static  void ShuffleArray(int arr[], int arrLength)
    {
        
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }


    static  void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }


    static string  Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }


   // Note: If you make an explicit cast for the input (e.g., to int),
   // you must also explicitly cast the result back to char before assigning/appending.
   // If you don't use any explicit casts, C++ handles the conversions for you,
   // so no explicit cast is needed for the result. like this " Encyperted += (OrginalName[i] + encryptionKey);"
    static string  EncryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);

        }

        return Text;
    }    

   
     static string  DecryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;

    }



    static string NumberToText(int Number)
    {
        if(Number == 0)
            return "";
        if(Number >=1 && Number <=19)
        {
            string arr[]{"","One","Tow","Three","Four","Five","six","Seven","Eight","Nine","Ten","Eleven","tewelve",
                        "thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Ninteen"};
            
            return arr[Number] + " ";         
        }

        if(Number >= 20 && Number <= 99)
        {
            string arr[]{"","","Twinty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninty",};

            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }
        
        if(Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100); 
        }

        if(Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100); 
        }
        
        if(Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000); 
        }
        
        if(Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000); 
        }

        //todo من مليون الي مليون وتسعمائة وتسعة وتسعون الف
        if(Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }
        
        //todo من 2 مليون الي تسعمائة وتسعة وتسعون مليون و تسعمائة وتسعة وتسعون الف
        if(Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);   
        }
        
        if(Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billions " + NumberToText(Number % 1000000000);   

        }

        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }

};


