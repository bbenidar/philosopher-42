# Dining Philosophers Problem

This project implements a solution to the Dining Philosophers Problem using semaphores and threads.

## Problem Description

The Dining Philosophers Problem is a classic synchronization problem in computer science. It involves a group of philosophers sitting around a table, each with a plate of spaghetti. The philosophers alternate between thinking and eating. However, there are only a limited number of forks available for the philosophers to use. A philosopher needs two forks to eat (one fork on the left and one on the right). The challenge is to design a solution that avoids deadlock and starvation, ensuring that each philosopher can eat their spaghetti without any conflicts.

## Implementation Details

The program creates a separate thread for each philosopher and uses semaphores to represent the forks and the waiter. Each philosopher thread executes the same logic:

1. Think: The philosopher thinks for a random amount of time.
2. Acquire Forks: The philosopher tries to acquire the left and right forks by decrementing the corresponding semaphores.
3. Eat: If the philosopher successfully acquires both forks, they eat for a random amount of time.
4. Release Forks: After eating, the philosopher releases the forks by incrementing the corresponding semaphores.
5. Repeat: The philosopher repeats the above steps for a specified number of iterations.

## Usage

1. Clone the repository: `git clone https://github.com/bbenidar/philosopher-42`
2. Navigate to the project directory: `cd philosopher-project`
3. Compile the source code: `gcc -pthread philosopher.c -o philosopher`
4. Run the program: `./philosopher`

## Customization

You can customize the behavior of the program by modifying the constants defined in the source code. For example, you can change the number of philosophers, the number of spaghetti portions, or the simulation duration.


## Contributing

Contributions are welcome! If you have any improvements or suggestions, please open an issue or submit a pull request.

