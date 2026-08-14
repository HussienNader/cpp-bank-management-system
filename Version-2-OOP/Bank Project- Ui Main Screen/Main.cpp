#include <iostream>
#include "Global.h"
// #include "clsMainScreen.h"
#include "clsLoginScreen.h"

using namespace std;

int main()

{
  
    // clsMainScreen::ShowMainMenue();
       
    while (true)
    {
        
        if (!clsloginScreen::ShowLoginScreen())
        {
            break;
        }
        
    }
    
    system("pause>0");
    return 0;
}