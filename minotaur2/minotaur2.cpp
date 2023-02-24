#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
using namespace std;

std::mutex m;
int available = 1;
int visited_count = 0;

void guest_thread(int thread_num) {
    int visited = 0;
    int running = 1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(1, 10);

    while(running) {
        int random = distr(generator);
        if(random == 1) {
            m.lock();
            if(visited_count == 10) {
                running = 0;
                m.unlock();
                break;
            }
            if(available == 1) {
                available = 0;
                m.unlock();
                cout << "Thread visiting: " << thread_num << '\n';
                this_thread::sleep_for(chrono::milliseconds(10));
                if(visited == 0) {
                    visited_count++;
                }
                visited = 1;
                cout << "Number of unique visits: " << visited_count << '\n';
                m.lock();
                available = 1;
                m.unlock();

            } else {
                m.unlock();
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {

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