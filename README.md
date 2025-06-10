# Philosophers

## Project Overview

This project is an implementation of the classic Dining Philosophers problem using C and POSIX threads. The goal is to simulate philosophers sitting at a table, alternating between thinking, eating, and sleeping, while sharing forks (resources) and avoiding deadlocks and starvation. This project is part of the 42 curriculum and aims to deepen understanding of concurrency, synchronization, and thread safety.

## What I Learned

- **Multithreading with pthreads:** Creating, joining, and managing threads in C.
- **Mutexes and synchronization:** Using `pthread_mutex_t` to protect shared resources and prevent race conditions.
- **Deadlock avoidance:** Implementing strategies to avoid deadlocks by controlling the order of fork acquisition.
- **Precise timing:** Using `gettimeofday` and custom sleep functions for accurate simulation timing.
- **Resource cleanup:** Properly destroying mutexes and freeing memory to avoid leaks.
- **Error handling:** Validating input and handling errors gracefully.
- **Code analysis tools:** Using Valgrind and AddressSanitizer (`-fsanitize=address`) to check for memory leaks, undefined behavior, and potential deadlocks (including pthread deadlocks).

## How to Use

### Compilation

In the [`Philosophers`](Philosophers) directory, run:

```sh
make
```

This will produce the `philo` executable.

#### Code Analysis

To check for memory leaks and undefined behavior, use:

- **Valgrind:**
    ```sh
    valgrind --leak-check=full ./philo 5 800 200 200
    ```
- **AddressSanitizer (fsanitize):**
    Add `-fsanitize=address -g` to your `CFLAGS` in the Makefile, or run:
    ```sh
    make SANITIZE=1
    ./philo 5 800 200 200
    ```
    *(You may need to modify your Makefile to support the `SANITIZE` variable.)*

### Usage

Run the program with the following arguments:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` (int): Number of philosophers (1-200)
- `time_to_die` (ms): Time a philosopher can go without eating before dying
- `time_to_eat` (ms): Time a philosopher spends eating
- `time_to_sleep` (ms): Time a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional, int): If specified, simulation ends when each philosopher has eaten at least this many times

**Example:**

```sh
./philo 5 800 200 200
```

## Project Structure

```
Philosophers/
├── Makefile
├── philo
├── include/
│   └── philo.h
└── srcs/
    ├── action.c
    ├── ft_atoi.c
    ├── ft_isdigit.c
    ├── init.c
    ├── monitor.c
    ├── philo.c
    └── utils.c
```

- [`philo.h`](Philosophers/include/philo.h): Main header file with all structures and function prototypes.
- [`action.c`](Philosophers/srcs/action.c): Philosopher actions (eat, sleep, think).
- [`monitor.c`](Philosophers/srcs/monitor.c): Monitoring thread for death and meal count.
- [`init.c`](Philosophers/srcs/init.c): Initialization of data structures and mutexes.
- [`utils.c`](Philosophers/srcs/utils.c): Utility functions (timing, printing, cleanup).
- [`philo.c`](Philosophers/srcs/philo.c): Main function, argument parsing, thread creation.

## Why This Design

- **Mutex per fork:** Each fork is a mutex, ensuring only one philosopher can hold it at a time.
- **Consistent fork acquisition order:** Philosophers always pick up the lower-numbered fork first to avoid deadlocks.
- **Monitor thread:** A separate thread checks for philosopher death and meal completion, ensuring timely detection.
- **Thread-safe printing:** Output is protected by a mutex to avoid garbled logs.
- **Custom sleep:** Accurate timing is achieved with a custom sleep function to avoid timing drift.

## Error Handling

- Checks for correct number and validity of arguments.
- Handles memory allocation and mutex initialization failures.
- Prints clear error messages for invalid input.

## How It Works

1. **Initialization:** Parses arguments, initializes philosophers, forks (mutexes), and shared data.
2. **Thread Creation:** Each philosopher runs in its own thread, performing actions in a loop.
3. **Fork Handling:** Philosophers pick up forks (mutexes) in a specific order to avoid deadlocks.
4. **Monitoring:** A separate thread monitors for death (time since last meal exceeds `time_to_die`) and for all philosophers eating enough times.
5. **Cleanup:** All resources (threads, mutexes, memory) are properly released at the end.

## References

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- 42 PDF subject (project requirements)

---

For more details, see the source code in the [`Philosophers`](Philosophers) directory.