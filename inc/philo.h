// File: inc/philo.h

#ifndef PHILO_H
#define PHILO_H

// Structures

typedef struct {
    int id;
    // Add any additional fields here
} Philosopher;

// Function Declarations

void initialize_philosophers(Philosopher* philosophers, int num_philosophers);
void cleanup_philosophers(Philosopher* philosophers, int num_philosophers);

#endif // PHILO_H