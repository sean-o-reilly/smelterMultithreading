#include <iostream>
#include <iomanip>
#include <random>

#include <thread>
#include <mutex>
//chrono

//!!!!!!!!! Based off tutorial by Ghost The Engineer on youtube

//using multi-threading to represent a minecraft auto furnace in C++, where each thread represents a furnace (see smelter.jpg)
//this achieves (ironOre * smeltTime) seconds of smelting time in 1/5 of the time, due to the use of 5 threads instead of 1

//TODO:
// - FIX run.sh not waiting after execution
// - std::atomic

int furnaces = 5;
int furnaceCapacity = 64;

int ironOre = 64 * 5; //5 stacks of iron ore
int ironIngots = 0;
int smeltTime = 10; //iron ore takes ten seconds to smelt

int expectedTime = (double)(ironOre * smeltTime) / (double)furnaces; //# of ingots to smelt , * smelt time, evenly distributed over the number of furnaces
//this is the target time^, which has to be achieved with multithreading to simulate multiple furnaces working together to distribute the smelting load
//is likely to be > than because of cout statements 

std::mutex mtx; //mutual exclusion

void smelt(int furnaceID) {
    for (int i = 0; i < furnaceCapacity; ++i) {

        //lock global accessing here, so multiple threads dont access the same operations and variables resulting in race condition
        {
            std::lock_guard<std::mutex> lock(mtx); //passing mtx in this constructor causes .lock() for us, and handles exceptions
            std::cout << "  Furnace " << furnaceID << " smelting ingot: " << (ironIngots + 1) << std::endl;
            ++ironIngots; //this furnace smelted an iron ingot
        } //scope destructor will destroy the lock, unlocking these operations for access

        //make sure this isn't in the lock!! (causes thread blocking)
        std::this_thread::sleep_for(std::chrono::milliseconds(smeltTime)); //sleep_for() is part of <thread> *for now this is converting 10 seconds to 10 milliseconds
    }
}

void printResults(double totalTime) {
    std::cout << "\n\n";
    std::cout << "=====Results=====" << std::endl;
    std::cout << "  Furnaces: " << furnaces << std::endl;
    std::cout << "  Iron Ore Smelted: " << ironIngots << std::endl;
    std::cout << "  Simulated Time Elapsed (Real Time but in Milliseconds): " << std::setprecision(4) << totalTime << " seconds " << std::endl;
    std::cout << "  Approx. Real Time Elapsed: " << totalTime * 1000.00 << " seconds " << std::endl;
    std::cout << "  Expected Time Elapsed: " << expectedTime << " seconds " << std::endl;

}

int main() {

    std::cout << std::endl << "=====Smelting=====" << std::endl << std::endl;


    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread furnace1(smelt, 1); //run the smelt function on a thread
    std::thread furnace2(smelt, 2);
    std::thread furnace3(smelt, 3);
    std::thread furnace4(smelt, 4);
    std::thread furnace5(smelt, 5);

    //join threads together
    furnace1.join();
    furnace2.join();
    furnace3.join();
    furnace4.join();
    furnace5.join();
    //after joining these threads, execution is already wayy closer to expected

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    printResults(elapsed.count());
    
    return 0;
}

//sequential execution examples

    // smelt(1);
    // smelt(2);
    // smelt(3);
    // smelt(4);
    // smelt(5);

    //or..

    // for (int i = 1; i <= furnaces; ++i) {
    //     smelt(i);
    // }