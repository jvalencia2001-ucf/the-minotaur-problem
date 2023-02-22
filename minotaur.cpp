#include <iostream>
#include <random>
using namespace std;

int finished = 0;
int active_prisoner = -1;
int is_cupcake = 1;
int epochs = 0;

void minotaur() {
    while(finished == 0) {
        if(active_prisoner == -1) {
            active_prisoner = generate_random(1, 10);
            epochs++;
        }
    }
}

void counter_thread() {
    int counter = 0;
    while (finished == 0) {
        if(active_prisoner == 1) {
            if(is_cupcake == 1){
                is_cupcake == 0;
                counter++;
                if(counter == 10)
                    finished = 1;
            }
        }
    }
}

void drone_thread() {
    while(finished == 0) {
        if(active_prisoner == 1) {
            if(is_cupcake == 0)
                is_cupcake == 1;
        }
    }
}

int generate_random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    return distr(generator);
}

int main() {

}