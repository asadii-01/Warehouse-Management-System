//      This is a simple Warehouse Managment System.
//      Designed and Coded by Asad Tauqeer.
// 
//      Last modified : 26-06-2024  Time : 23:29
//

#include "warehouse.h"
#include "utility.h"

int main() {

    Warehouse main_warehouse;
    
    Intro();

    main_warehouse.Run();

    LoadingScreen("\033[31mExiting Program");
    Exit();

	return 0;
}