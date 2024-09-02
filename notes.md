Code assistant: Github Copilot

Testers: (not tried yet)
https://github.com/newlinuxbot/Philosphers-42Project-Tester
https://github.com/nesvoboda/socrates.git

Usage:
./philo num_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

TODO
Update README.md

# Lessons learned
Your structs and functions must be clear to you. Very clear
Build before you write, then build as you write
Modularize
Work focused. For long hours
You do't need to push every commit

Add a time buffer in monitoring
I't all in the timing
The processor has so many cores and will simulate paralelization, but only is it has some slack



Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
#### AT LEAST N TIMES
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
####
x Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.

hardest ./philo 199 190 60 60 199
https://nafuka11.github.io/philosophers-visualizer/