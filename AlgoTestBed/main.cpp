#include <cstdio>
#include <iostream>
#include <Algorithms.h>
#include <ostream>
int main() {
    FTBDLL<int> dll = FTBDLL<int>(5);
    int m = 10; 
    int n = 10;
    // SensorReading<int, int> sensorReading = SensorReading<int, int>(m,n);

    std::cout << "Hello, World!" << std::endl;

    while (!dll.isFull()){

        // sensorReading.update_reading(m, n);
        dll.display();
        // std::cout << sensorReading << dll.getSize() << "\n";
        dll.push_back(m);
        m++;
    }       
    dll.display();
    dll.emptyList();
    dll.display();
    while (!dll.isFull()){

        // sensorReading.update_reading(m, n);
        dll.display();
        // std::cout << sensorReading << dll.getSize() << "\n";
        dll.push_front(m);
        m--;
        
    }  


    return 0;
}
