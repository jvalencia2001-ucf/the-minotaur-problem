#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
using namespace std;

//Create necessary variables.
std::mutex m;
int available = 1;
int visited_count = 0;

//Function to be passed to threads representing guests.
void guest_thread(int thread_num) {
    int visited = 0;
    int running = 1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(1, 10);

    while(running) {
        //Generate a random number to simulate a guest's chance of deciding to enter the room with the base.
        int random = distr(generator);
        //The guests wishes to go in the room if the random number is 1.
        if(random == 1) {
            m.lock();
            //Exit if all guests have visited the base.
            if(visited_count == 10) {
                running = 0;
                m.unlock();
                break;
            }
            //Check if room with the base is available.
            if(available == 1) {
                /*If its available occupy the room and unlock the mutex so other threads
                can check for availability. */
                available = 0;
                m.unlock();
                //Anything here is linear even without the mutex being locked.
                cout << "Thread visiting: " << thread_num << '\n';
                //Increase visited count only if its the threads first time visiting.
                if(visited == 0) {
                    visited_count++;
                }
                visited = 1;
                cout << "Number of unique visits: " << visited_count << '\n';
                //Make room available
                m.lock();
                available = 1;
                m.unlock();

            } else {
                //If the room isn't available the guest stops checking for availability.
                m.unlock();
            }
        } else {
            //If the guest isn't interested, other work can be done.
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
}

int main() {

    //Create and join threads.
    std::thread t1(guest_thread, 1);
    std::thread t2(guest_thread, 2);
    std::thread t3(guest_thread, 3);
    std::thread t4(guest_thread, 4);
    std::thread t5(guest_thread, 5);
    std::thread t6(guest_thread, 6);
    std::thread t7(guest_thread, 7);
    std::thread t8(guest_thread, 8);
    std::thread t9(guest_thread, 9);
    std::thread t10(guest_thread, 10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    
}