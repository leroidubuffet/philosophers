#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "philo.h"

// compile with gcc -I./inc tests/test_init_program.c inc/philo.h src/init_program.c src/time_utils.c 

t_program program;
t_philo *philos;
t_config config;
pthread_mutex_t *forks;

void setUp(void) {
    config.num_of_philos = 5;
    config.time_to_die = 800;
    config.time_to_eat = 200;
    config.time_to_sleep = 200;
    config.num_times_to_eat = 7;

    philos = malloc(sizeof(t_philo) * config.num_of_philos);
    forks = malloc(sizeof(pthread_mutex_t) * config.num_of_philos);
}

void tearDown(void) {
    free(philos);
    free(forks);
}

void test_init_forks(void) {
    printf("Testing init_forks...\n");
    init_forks(forks, config.num_of_philos);
    assert(forks != NULL);
    printf("init_forks test passed.\n");
}

void test_init_philos(void) {
    printf("Testing init_philos...\n");
    init_program(&program, philos, &config);
    init_forks(forks, config.num_of_philos);
    init_philos(philos, &program, forks);

    for (int i = 0; i < config.num_of_philos; i++) {
        assert(philos[i].id == i + 1);
        assert(philos[i].write_lock == &program.write_lock);
        assert(philos[i].dead_lock == &program.dead_lock);
        assert(philos[i].meal_lock == &program.meal_lock);
        assert(philos[i].time_to_die == &config.time_to_die);
        assert(philos[i].time_to_eat == &config.time_to_eat);
        assert(philos[i].time_to_sleep == &config.time_to_sleep);
        assert(philos[i].num_times_to_eat == &config.num_times_to_eat);
        assert(philos[i].meals_eaten == 0);
        assert(philos[i].eating == 0);
        assert(philos[i].dead == &program.dead_flag);
        assert(philos[i].config == &config);
    }

    assert(philos[0].r_fork == &forks[config.num_of_philos - 1]);
    assert(philos[0].l_fork == &forks[0]);
    for (int i = 1; i < config.num_of_philos; i++) {
        assert(philos[i].r_fork == &forks[i - 1]);
        assert(philos[i].l_fork == &forks[i]);
    }
    printf("init_philos test passed.\n");
}

void test_init_program(void) {
    printf("Testing init_program...\n");
    init_program(&program, philos, &config);

    assert(program.dead_flag == 0);
    assert(program.philos == philos);
    assert(program.config == &config);
    assert(&program.write_lock != NULL);
    assert(&program.dead_lock != NULL);
    assert(&program.meal_lock != NULL);
    printf("init_program test passed.\n");
}

int main(void) {
    setUp();
    test_init_forks();
    test_init_philos();
    test_init_program();
    tearDown();
    printf("All tests passed successfully!\n");
    return 0;
}