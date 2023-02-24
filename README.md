# The Minotaur Puzzles


## __Statments__

This repository contains two different programs, minotaur and minotaur2.

To run each program please clone the repository and follow the following instructions.

- To run minotaur.cpp:
  - Navigate to the minotaur folder on a console.
  - Use the following commands to compile and run minotaur.cpp.
    
    ```
    g++ minotaur.cpp
    ./a.out
    ```
- To run minotaur2.cpp:
  - Navigate to the minotaur2 folder on a console.
  - Use the following commands to compile and run minotaur2.cpp.
    
    ```
    g++ minotaur2.cpp
    ./a.out
    ```

Note that to compile this programs, you'll need a modern, up to date c++ compiler. The example above uses the most recent version of gcc.

The minotaur program simulates the first problem in the homework using ten threads to represent ten guests. The program will print to the console data about how the run is going to simplify verifying the correctned of the program. This data includes the order of the guests chosen, when the counter is incremented and also how many requests from the minotaur it took for everyone to visit the cupcake room.

As for the minotaur2 program, this program simulates the second strategy given as an option in the homework for the second problem. I'll describe more about why I chose this strategy on the efficiency section. The minotaur2 program also prints data to the console with the same purpose as the minotaur program. This data includes the order in which the threads visited the room and how many unique visits are recorded at the time of each visit.

## __Efficiency__

The effiency for the minotaur program is admitedly pretty low when talking about the algorithm using to solve the riddle. A single counter is tasked with being the only one who eats cupcakes and keeps count of each cupcake eaten. Every other guests simply requests a cupcake if it's their first time visiting and they find no cupcake. This allows the counter to keep an accurate count of how many people have visited the room by keeping count of how many cupcakes it's eaten.

Altough this algorithm isn't the fastest in terms of counting the guests who have visted the cupcake room, it is nicely adapted to a parallel enviroment. The threads that aren't selected by the minotaur aren't locked until they are selected, but they instead wait for a flag from the minotaur to tell them its their turn. This allows the threads to be able to do other jobs if they aren't currently in the room.


For the second program, let me just explain why I chose the second option. I think that strategy 1 and strategy 3 are at the extremes of how organized the guests have to be. The first strategy is not organized at all and it would probably cause the guests to bottlneck in the entrance of the room. In addition the guests are doing nothin but waiting, because they don't know when they can go. The third strategy on the other hand is a queue, which is really organized, but simalarly to option one, having guests in a queue doesn't allow them to do anything else but wait. The second option has a nice balance. Having a public sign that represents thata availability of the room allows guests to decide how much they want to commit to going in the room. If the guets really wants to go in, it may wait till the sign turns available continously, but if the guests isn't that interested it is free to do something else and check wether the room is free from time to time. I think that this also applies to enbling threads to other work while they wait.

I was also able to adapt this strategy to a parallel enviroment pretty nicely. Although a lock was necessary to ensure that no more than one thread checked the availability of the room at the same time, once availability is checked a thread does not have to remain blocked until the room is available, but it us able to do other work before checking again. Also, being in the room does not lock other threads out from checking availability, so one guest can be inside the room and others checking if its available.

### Is there any more speed-ups that could be implmented?

I can suggests speed ups for the minotaur program, since the algorithm used to solve the riddle was not given to us like in the minotaur2 program.

There are many known ways to speed up the method of only having one counter among all guests.

The most obvious one and the one I'm going to suggest here is having multiple counters. For this strategy to work you need to assume that guests know how many guests have been called before them. The strategy then creates sets a main counter and several helper counters. Before a certain amount of guests have been called the helper counters attempt to each count a certain amount of guests who have visited with a method similar to the one counter strategy, but after that certain amount of guests have been called, the main counter will now count up the helper counters who counted up the the amount they decided to. Then go back to the first stage, in case any helper counters didn't finish counting.

This basically allows so that we can count more often that when only a single counter gets chosen, since we have multiple. It also allows the main counter to count in bigger steps.

## __Proof of Correctness__

The proof of correctness in these programs are reflected in the data they print to the console.

To use the data printed by the minotaur program to verify its correctess, simple verify that the counter is only incrementing when the counter thread is chosen, and furthermore, that the counter thread is only incrementing the counter whenever a drone thread that has not visited the cupcake room yet has been to the room since the last time the counter thread went in the cupcake room itself.

To verify correctness for the minotaur2 program, simply verify that the counter only increases each time a thread that hasn't visited the vase room yet visits for the first time.

 ## __Experimental Evaluation__

As for the minotaur program, I did evaluation in multiple number of guests. The program worked correctly as long as the number of guest chosen was a positive integer greater than 0. The strategy even worked whenever there were no drone guests created and the only guest is the counter itself. I tested the program with a max number of guests of 100, and it worked correctly, but it did take its time to execute due to depending on an rng.

The strategy on the minotaur2 program is simple and I also tested it with 1 to 100 threads. The program worked for any number of threads and this one was quite speedy too.