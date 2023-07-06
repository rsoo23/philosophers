# philosophers

This project tackles the dining philosophers problem, where each philosopher can either eat, sleep, think or die. The main goal is to make sure that the dying philosopher dies within 10ms of the death time.

## Mandatory
This project taught me how to implement multithreading in C while learning the ins and outs of communication and resource sharing between threads and the main thread with mutex locks to prevent data races.

## Bonus
This bonus part taught me how to use semaphores instead of mutexes and child processes instead of threads to run the same dining philosophers' problem.

Resources:
- concurrent programming: https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
- unix threads in c: https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
- visualiser: https://nafuka11.github.io/philosophers-visualizer/

Checklist:
- [x] Mandatory Error Checking
- [x] Tests for Mandatory up to 200
- [x] Tests for Mandatory with fsanitize up to 200 
- [x] Mandatory Norm

- [x] Bonus Error Checking
- [x] Tests for Bonus up to 200
- [x] Tests for Bonus with fsanitize up to 200
- [x] Bonus Norm
