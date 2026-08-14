#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include "clsString.h"
//#include "StringLibrary.h"
using namespace std;


class clsDate
{

private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;
    
public:
    clsDate()
    {
        // get system date
        time_t t = time(0);
        tm* Now  = localtime(&t);

        _Day   = Now->tm_mday;
        _Month = Now->tm_mon + 1;
        _Year  = Now->tm_year + 1900;
       
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate,"/");

        _Day   = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year  = stoi(vDate[2]);
    }

    clsDate(short day,short month, short yaer)
    {
        _Day   = day;
        _Month = month;
        _Year  = yaer;
    }

    clsDate(short DateOrderInYear, short Year)
	{
		//This will construct a date by date order in year
		clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
	    _Day = Date1._Day;
		_Month = Date1._Month;
		_Year = Date1._Year;
	}

    void SetDay(short day)
    {
        _Day = day;
    }

    short GetDay () 
    {
        return _Day;
    }


    void SetMonth(short month)
    {
        _Month = month;
    }

    short GetMonth ()
    {
        return _Month;
    }

    
    void SetYear(short year)
    {
        _Year = year;
    }

    short GetYear () 
    {
        return _Year;
    }

    // -------------------------  Date Methods  ------------------------------------

    void Print()
    {
        cout << DateToString() << endl;
    }

    static clsDate GetSystemDate()
    {
        time_t t = time(nullptr);
        tm* Now = localtime(&t);

        short day, month, year;

        day = Now->tm_mday;
        month = Now->tm_mon + 1;
        year =  Now->tm_year + 1900;

        return clsDate(day,month,year);
    }


    static string GetSystemTimeInString()
    {
        short year,day, month,hour,minut,second;
        time_t t = time(nullptr);
        tm* Now = localtime(&t);

        year   = Now->tm_year + 1900;
        month  = Now->tm_mon + 1;
        day    = Now->tm_mday;
        hour   = Now->tm_hour;
        minut  = Now->tm_min;
        second = Now->tm_sec;

        return (to_string(day) + "/" + to_string(month)+"/"+to_string(year)
                + " - "+ to_string(hour)+":"+to_string(minut)+":" + to_string(second)+"   ");
    }


    static bool IsValidDate(clsDate Date)
    {
        if(Date._Day < 1 || Date._Day > 31)
            return false;

        if(Date._Month < 1 || Date._Month > 12)
            return false;
            
        if(Date._Month == 2)
        {
            if(IsLeapYear(Date._Year))
            {
                if(Date._Day > 29)
                    return false;
            }

            else
            {
                if(Date._Day > 28)
                    return false;
            }
        }
        
        short MonthDays = NumberOfDaysInMonth(Date._Month, Date._Year);
        return  Date._Day <= MonthDays;
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }


    static string DateToString(clsDate Date)
    {
        string st = "";

        st += to_string(Date._Day) + "/";
        st += to_string(Date._Month) + "/";
        st += to_string(Date._Year);

        return st;
    }

    string DateToString()
    {
        return DateToString(*this);
    }


    static bool IsLeapYear(short year)
    {
        return((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }


    static short NumberOfDaysInYear(short year)
    {
        return IsLeapYear(year) ? 366 : 365;
    }

    short NumberOfDaysInYear()
    {
        return NumberOfDaysInYear(_Year);
    }


    static short NumberOfHoursinYear(short year)
    {
        return NumberOfDaysInYear(year) * 24;
    }

    short NumberOfHoursinYear()
    {
        return NumberOfHoursinYear(_Year);
    }


    static int NumberOfMinutsInYear(short year)
    {
        return NumberOfHoursinYear(year) * 60;
    }

    int NumberOfMinutsInYear()
    {
        return NumberOfMinutsInYear(_Year);
    }


    static int NumberOfSecondsInYear(short year)
    {
        return NumberOfMinutsInYear(year) * 60;
    }

    int NumberOfSecondsInYear()
    {
        return NumberOfSecondsInYear(_Year);
    }


    static short NumberOfDaysInMonth(short Month, short Year)
	{

		if (Month < 1 || Month>12)
			return  0;

		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }
    
    short NumberOfDaysInMonth()
    {
        return NumberOfDaysInMonth(_Month,_Year);
    }


    static short NumberOfHoursInMonth(short month, short year)
    {
        return NumberOfDaysInMonth(month,year) * 24;
    }

    short NumberOfHoursInMonth()
    {
        return NumberOfHoursInMonth(_Month,_Year);
    }


    static int NumberOfMinutsInMonth(short month, short yaer)
    {
        return NumberOfHoursInMonth(month,yaer) * 60;
    }

    int NumberOfMinutsInMonth()
    {
        return NumberOfMinutsInMonth(_Month,_Year);
    }


    static int NumberOfSecondsInMonth(short month,short year)
    {
       return NumberOfMinutsInMonth(month,year) * 60;
    }
 
    int NumberOfSecondsInMonth()
    {
       return  NumberOfSecondsInMonth(_Month,_Year);  
    }


    static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day,_Month,_Year);
    }


    static string DayShortName(short DayWeekOrder)
    {
        string arrDayNames[] = {"Sun","Mon","Tus","Wed","Thu","Fri","sat"};
        return arrDayNames[DayWeekOrder];
    }


    static string DayShortName(short Day, short Month, short Year)
	{

		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];

	}

	string DayShortName()
	{

		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];

	}


    static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
						      "Apr", "May", "Jun",
						      "Jul", "Aug", "Sep",
						      "Oct", "Nov", "Dec"
		};

		return (Months[MonthNumber - 1]);
	}

    string MonthShortName()
	{

		return MonthShortName(_Month);
	}


    static void PrintMonthCalender(short Month, short Year)
    {
        short DaysOfMonth = NumberOfDaysInMonth(Month,Year);
        short current = DayOfWeekOrder(1,Month,Year);


        // Print the current month name
		printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str()); 

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    
        int i = 0;
        for(i = 0; i < current; i++)
            printf("     ");

        for(int j = 1; j <= DaysOfMonth; j++)
        {
            if(++i == 7)
            {
                cout <<"\n";
                i = 0;
            }

            printf("%5d",j);
            
        }
        
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(_Month,_Year);
    }


    static void PrintCalenderofYear(short year)
    {
        printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");


        for(int i = 1; i <= 12; i++)
          PrintMonthCalender(i,year);
    }

    void PrintCalenderofYear()
    {
        PrintCalenderofYear(_Year);
    }

    
    static short DaysfromTheBeginngOfTheYear(short day, short month, short year)
    {
        short TotalDays = day;

        for(int i = 1; i <= month-1; i++)
        {
            TotalDays += NumberOfDaysInMonth(i,year);
        }

        return TotalDays;
    }
    
    short DaysfromTheBeginngOfTheYear()
    {
        return DaysfromTheBeginngOfTheYear(_Day,_Month,_Year);
    }


    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;

        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInMonth(Date._Month,Year);
            
            if(RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date._Month++;
            }

            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;
    }


    void AddDays(short DaysToAdd)
    {
        short RemainingDays =  DaysToAdd + DaysfromTheBeginngOfTheYear(_Day,_Month,_Year);
        short MonthDays = 0;
        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInMonth(_Month,_Year);
            if(RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;
                if(_Month > 12)
                {
                    _Year++;
                    _Month = 1;
                }
            }

            else
              _Day = RemainingDays;
        }
        
    }


    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        if(Date1._Year != Date2._Year)
        {
            if(Date1._Year < Date2._Year)
                return true;
            else
                return false;    
        }

        if(Date1._Month != Date2._Month)
        {
            if(Date1._Year < Date2._Year)
                return true;
            else 
                return false;    
        }

        if(Date1._Day != Date2._Day)
        {
            if(Date1._Day < Date2._Day)
                return true;
            else
                return false;    
        }

        else
            return false;
    }

    bool IsDateBeforeDate2(clsDate Date2)
	{
		//note: *this sends the current object :-) 
		return  IsDate1BeforeDate2(*this, Date2);
	}


    static bool IsDat1EqualDate2(clsDate Date1, clsDate Date2)
    {
        if(Date1._Year  != Date2._Year)    return false;
        if(Date1._Month != Date2._Month)   return false;
        if(Date1._Day   != Date2._Day)     return false;

        else
            return true;
    }

    bool IsDat1EqualDate2(clsDate Date2)
    {
        return IsDat1EqualDate2(*this, Date2);
    }


    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1,Date2) && !IsDat1EqualDate2(Date1,Date2));
    }


    static bool IsLastDayInMonth(short day,short month, short year)
    {
        return day == NumberOfDaysInMonth(month,year);
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(_Day,_Month, _Year);
    }


    static bool IsLastMonthInYear(short Month)
    {
        return Month == 12;
    }

    bool IsLastMonthInYear()
    {
        return IsLastMonthInYear(_Month);
    }


    static clsDate AddOneDay(clsDate Date)
    {
        if(IsLastDayInMonth(Date._Day,Date._Month,Date._Year))
        {
            if(IsLastMonthInYear(Date._Month))
            {
                Date._Year++;
                Date._Month = 1;
                Date._Day = 1;
            }

            else
            {
                Date._Month ++;
                Date._Day = 1;
            }
        }

        else
            Date._Day ++;

        return Date;    
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }


    
	static void  SwapDates(clsDate & Date1, clsDate & Date2)
	{

		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

	}


    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short  SwapFalgvalue = 1;

        if(!IsDate1BeforeDate2(Date1,Date2))
        {
            SwapDates(Date1,Date2);
            SwapFalgvalue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        return IncludeEndDay ? ++Days * SwapFalgvalue: Days * SwapFalgvalue;
        
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return  GetDifferenceInDays(*this,Date2,IncludeEndDay);
    }


    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        // Get systeem Date
       // clsDate sysDate = GetSystemDate();

        return GetDifferenceInDays(DateOfBirth,clsDate::GetSystemDate(),true);
    }


    static /* clsDate */void  IncreaseDateByOneWeek(clsDate & Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		//return Date;
	}

    void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

   /*  clsDate */ void IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			/* Date = */ IncreaseDateByOneWeek(Date);
		}
		// return Date;
	}

    void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

    static void IncreaseDateByOneMonth(clsDate & Date)
    {
        if(Date._Month == 12)
        {
            Date._Year++;
            Date._Month = 1;
        }

        else
            Date._Month++;

            
		//last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
		// be 28/2/2022
        short MonthDays = NumberOfDaysInMonth(Date._Month,Date._Year);   
        if(Date._Day > MonthDays )
        {
            Date._Day = MonthDays;
        }
    }

    void IncreaseDateByOneMonth()
	{

		IncreaseDateByOneMonth(*this);
	
    }


   /*  clsDate */void IncreaseDateByXDays(short Days, clsDate& Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		// return Date;
	}

    void IncreaseDateByXDays(short Days)
	{

		IncreaseDateByXDays(Days, *this);
	}


   /*  clsDate */void IncreaseDateByXMonths(short Months, clsDate& Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			/* Date = */ IncreaseDateByOneMonth(Date);
		}
		// return Date;
	}

    void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}


    static/*  clsDate */void IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year++;
		// return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}


   /*  clsDate */void IncreaseDateByXYears(short Years, clsDate& Date)
	{
		Date._Year += Years;
		// return Date;
		
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years);
	}


    /* clsDate */ void IncreaseDateByOneDecade(clsDate& Date)
	{
		//Period of 10 years
		Date._Year += 10;
		// return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

    
   /*  clsDate */void IncreaseDateByOneCentury(clsDate& Date)
	{
		//Period of 100 years
		Date._Year += 100;
		// return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}


   /*  clsDate */void IncreaseDateByOneMillennium(clsDate& Date)
	{
		//Period of 1000 years
		Date._Year += 1000;
		// return Date;
	}

	/* clsDate */void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

};