#include <cstdio>
#include <iostream>
#include <Algorithms.h>
#include <ostream>
#include <chrono>
#include <thread>
#include <typeinfo>

int main() {
    FTBDLL<int> dll = FTBDLL<int>(5);
    int m = 10; 
    int n = 10;
    // SensorReading<int, int> sensorReading = SensorReading<int, int>(m,n);

    std::cout << "Front to Back Doubly Linked Lists!" << std::endl;
    std::cout << "Inserting by updating the Present:" << std::endl;

    dll.display();
    
    auto t0 = std::chrono::high_resolution_clock::now();
    while (!dll.isFull()){
        

        dll.insertPresent(m);
        dll.display();

        m++;
    }       
    auto t = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t-t0).count() * 1e-9;
    std::cout << std::fixed << "\n\nList Filled - " << dll.getSize() << " elements in " << elapsed << "s	  " << dll.getSize()/elapsed << typeid(m).name() << " Nodes/s" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "\nClearing from the Present:" << std::endl;

    while (dll.getSize() != 0){

        dll.clearPresent();
        dll.display();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "\n\nInserting by updating the Past:" << std::endl;
     

    t0 = std::chrono::high_resolution_clock::now();

    while (!dll.isFull()){

        dll.insertPast(m);
        dll.display();
        m--;
    }  
    // dll.emptyList();

    t = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t-t0).count() * 1e-9;
    std::cout << std::fixed << "\n\nList Filled - " << dll.getSize() << " elements in " << elapsed << "s    " << dll.getSize()/elapsed << typeid(m).name() << " Nodes/s" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "\nClearing from the Past:" << std::endl;

    while (dll.getSize() != 0){

        dll.clearPast();
        dll.display();
    }  
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    

    dll.display();
            std::cout << "\n\nInserting 1000 Nodes:" << std::endl;
    t0 = std::chrono::high_resolution_clock::now();

    while (dll.getSize() <= 10000){
        dll.insertPresent(m, 5000);
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        m++;
    }

     t = std::chrono::high_resolution_clock::now();
     elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t-t0).count() * 1e-9;
    std::cout << std::fixed << "\nList Filled - " << dll.getSize() << " elements in " << elapsed << "s    " << dll.getSize()/elapsed << typeid(m).name() << " Nodes/s" << std::endl;

    // dll.display();
    // dll.emptyList();
    // dll.display();

    return 0;
}
