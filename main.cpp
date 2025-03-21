#include <iostream>
#include <iomanip>
#include <random>

#include <thread>
//chrono

//!!!!!!!!! Based off tutorial by Ghost The Engineer on youtube

//using multi-threading to represent a minecraft auto furnace in C++


//FIX run.sh not waiting after execution

int furnaces = 5;
int furnaceCapacity = 64;

int ironOre = 64 * 5; //5 stacks of iron ore
int ironIngots = 0;
int smeltTime = 10; //iron ore takes ten seconds to smelt

int expectedTime = (double)(ironOre * smeltTime) / (double)furnaces; //# of ingots to smelt , * smelt time, evenly distributed over the number of furnaces
//this is the target time^, which has to be achieved with multithreading to simulate multiple furnaces working together to distribute the smelting load
//is likely to be > than because of cout statements 

void smelt(int furnaceID) {
    for (int i = 0; i < furnaceCapacity; ++i) {
        std::cout << "  Furnace " << furnaceID << " smelting ingot: " << (ironIngots + 1) << std::endl;
        ++ironIngots; //this furnace smelted an iron ingot

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

    std::cout << std::endl << "=====Hello, Multithreading!=====" << std::endl << std::endl;


    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread furnace1(smelt, 1); //run the smelt function on a thread
    std::thread furnace2(smelt, 2);
    std::thread furnace3(smelt, 3);
    std::thread furnace4(smelt, 4);
    std::thread furnace5(smelt, 5);

    //join threads to avoid race condition error
    furnace1.join();
    furnace2.join();
    furnace3.join();
    furnace4.join();
    furnace5.join();
    //after joining these threads, execution is already wayy closer to expected
    //however,  we're still getting a race condition on some runs of main
    //all 5 furnaces are trying to access ironIngots at once to ++, so we need to sync threads with mutex


    //sequential execution
    // smelt(1);
    // smelt(2);
    // smelt(3);
    // smelt(4);
    // smelt(5);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    printResults(elapsed.count());
    
    return 0;
}