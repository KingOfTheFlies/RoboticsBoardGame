#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <stdio.h> 
#include <time.h> 

#include "Application.h"
#include "GameController.h"
#include "IpException.h"

int main(int argc, char* argv[]) {
    clock_t start = clock();
    try {
        Application app(argc, argv);
        app.addField();
        app.addPlayersFactory();

        GameController gc(&app);
        gc.Run();

        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The time: %f seconds\n", seconds);
    }
    catch (const IpException& e) {
        std::cout << e.What() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unexpected Error" << std::endl;
    }
    return 0;
}