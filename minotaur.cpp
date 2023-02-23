#include <iostream>
#include <random>
#include <thread>
#include <mutex>
using namespace std;

int finished = 0;
int active_guest = -1;
int is_cupcake = 1;
int epochs = 0;
std::mutex m;

int generate_random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    return distr(generator);
}

void minotaur() {
    while(finished == 0) {
        m.lock();
        if(active_guest == -1) {
            int guest_chosen = generate_random(1, 10);
            cout << "Guest chosen: " << guest_chosen << '\n';
            active_guest = guest_chosen;
            epochs++;
        }
        m.unlock();
    }
}

void counter_thread(int thread_num) {
    int counter = 0;
    while (finished == 0) {
        if(active_guest == thread_num) {
            cout << "counter active\n";
            if(is_cupcake == 1){
                is_cupcake == 0;
                counter++;
                if(counter == 10)
                    finished = 1;
            }
            m.lock();
            active_guest = -1;
            m.unlock();
        }
    }
    cout << counter << '\n';
}

void drone_thread(int thread_num) {
    int participated = 0;
    while(finished == 0) {
        if(active_guest == thread_num) {
            cout << "drone active\n";
            if(is_cupcake == 0  && participated == 0) {
                is_cupcake = 1;
                participated = 1;
            }
            m.lock();
            active_guest = -1;
            m.unlock();
        }
    }
}

int main() {

    std::thread t1(minotaur);
    
    std::thread t2(counter_thread, 1);
    
    std::thread t3(drone_thread, 2);
    std::thread t4(drone_thread, 3);
    std::thread t5(drone_thread, 4);
    std::thread t6(drone_thread, 5);
    std::thread t7(drone_thread, 6);
    std::thread t8(drone_thread, 7);
    std::thread t9(drone_thread, 8);
    std::thread t10(drone_thread, 9);
    std::thread t11(drone_thread, 10);

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
    t11.join();

    cout << epochs << '\n';


}