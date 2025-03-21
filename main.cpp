#include <iostream>
#include <iomanip>
#include <random>

#include <thread>
//chrono

//using multi-threading to represent a minecraft auto furnace in C++

int furnaces = 5;
int furnaceCapacity = 64;

int ironOre = 64 * 5; //5 stacks of iron ore
int ironIngots = 0;
int smeltTime = 10; //iron ore takes ten seconds to smelt

void smelt(int furnaceID) {
    for (int i = 0; i < furnaceCapacity; ++i) {
        std::cout << "  Furnace " << furnaceID << " smelting ingot " << (ironIngots + 1) << std::endl;
        ++ironIngots; //this furnace smelted an iron ingot

        std::this_thread::sleep_for(std::chrono::milliseconds(smeltTime)); //sleep_for() is part of <thread> *for now this is converting 10 seconds to 10 milliseconds
    }
}

void printResults(double totalTime) {
    std::cout << "\n\n";
    std::cout << "=====Results=====" << std::endl;
    std::cout << "  Furnaces: " << furnaces << std::endl;
    std::cout << "  Iron Ore Smelted: " << ironIngots << std::endl;
    std::cout << "  Simulated Time Elapsed (Real Time in Milliseconds): " << std::setprecision(4) << totalTime << " seconds " << std::endl;
    std::cout << "  Approx. Real Time Elapsed: " << totalTime * 1000.00 << " seconds " << std::endl;
    std::cout << "  Expected Time Elapsed: " << ironIngots * smeltTime << " seconds " << std::endl;

}

int main() {

    std::cout << std::endl << "=====Hello, Multithreading!=====" << std::endl << std::endl;


    auto startTime = std::chrono::high_resolution_clock::now();

    smelt(1);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    printResults(elapsed.count());
    
    return 0;
}