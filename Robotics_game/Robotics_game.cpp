#include <iostream>
#include <vector>
#include <string>
#include <chrono>

//#include "Field.h"
#include "Application.h"
#include "GameController.h"

int main(int argc, char* argv[]) {

    Application app(argc, argv);
    app.addField();
    app.addPlayersFactory();
    
    GameController gc(&app);
    gc.Run();

    return 0;
}