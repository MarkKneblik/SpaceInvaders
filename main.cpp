#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include "invaderManager.h"
#include "playerShip.h"
#include "game.h"
#include "data.h"
#include "interfaces.h"

using namespace std;
 
int main(void) {
   
    interfaces* interface = new interfaces();

    interface->createMainWin();
    interface->createPauseWin();
    interface->createMenuWin();
    interface->runInterfaces();
    
    

 
    return EXIT_SUCCESS;
}