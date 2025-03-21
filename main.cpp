#include <iostream>
#include <iomanip>
#include <random>

#include <thread>

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

int main() {

    std::cout << std::endl << "=====Hello, Multithreading!=====" << std::endl << std::endl;

    smelt(1);

    return 0;
}