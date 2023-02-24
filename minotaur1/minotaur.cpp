#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

//Create necessary variables
int finished = 0;
int active_guest = -1;
int is_cupcake = 1;
int epochs = 0;
std::mutex m;

//Function to generate a random number to represent guest chosen.
int generate_random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    return distr(generator);
}

//Function for the thread representing the minotaur.
void minotaur() {
    while(finished == 0) {
        //Chooose a new guest and increase the epochs.
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

//Function for the thread representing the counter thread.
void counter_thread(int thread_num) {
    int counter = 0;
    while (finished == 0) {
        //Check if the current thread represents the guest chosen.
        if(active_guest == thread_num) {
            cout << "Counter active\n";
            //If there is a cupcake in the room, eat it and increase the count.
            if(is_cupcake == 1){
                is_cupcake = 0;
                counter++;
                cout << "Counter incremented to: " << counter << '\n';
                //Finish all threads if counter reaches 10.
                if(counter == 10)
                    finished = 1;
            }
            //Reset the active guest.
            m.lock();
            active_guest = -1;
            m.unlock();
        }
    }
    cout << "Final counter: " << counter << '\n';
}

//Function for the threads representing drone guests.
void drone_thread(int thread_num) {
    int participated = 0;
    while(finished == 0) {
        //Check if the current thread represents the guest chosen.
        if(active_guest == thread_num) {
            cout << "drone active\n";
            //If there is no cupcake in the room, request one and record participation.
            if(is_cupcake == 0  && participated == 0) {
                is_cupcake = 1;
                participated = 1;
            }
            //Reset the active guest.
            m.lock();
            active_guest = -1;
            m.unlock();
        }
    }
}

int main() {

    //Create and join all threads.
    std::thread t1(minotaur);
    
    std::thread t2(counter_thread, 1);

    std::vector<std::thread> drones;

    for(int i = 0; i < 9; i++) {
        std::thread droneThread(drone_thread, i+2);
        drones.push_back(move(droneThread));
    }


    t1.join();
    t2.join();
    for(int i = 0; i < drones.size(); i++) {
        drones.at(i).join();
    }

    cout << "Finished in " << epochs << " minotaur requests." << '\n';


}