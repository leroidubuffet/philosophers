Code assistant: Github Copilot

Testers: (not tried yet)
https://github.com/newlinuxbot/Philosphers-42Project-Tester
https://github.com/nesvoboda/socrates.git

Diferencia entre clean y fclean?

Las posiciones de los philos son fijas? Puede haber huecos entre ellos?

Usage:
./philo num_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

TODO
Fix algorithm
Update README.md
Comment functions
Improve structs:
	typedef struct s_philo
{
    pthread_t		thread;
    pthread_mutex_t	*r_fork;
    pthread_mutex_t	*l_fork;
    size_t			last_meal;
    size_t			start_time;
    int				meals_eaten;
    bool			eating;
    bool			*dead;
    int				id;
    t_config		*config;
    t_program		*program; // Added program pointer
}					t_philo;

typedef struct s_program
{
    t_config		*config;
    t_philo			*philos;
    pthread_mutex_t	dead_lock;
    pthread_mutex_t	meal_lock;
    pthread_mutex_t	write_lock;
    bool			dead_flag;
}					t_program;
Name folder to philo/

Lessons learned
Your structs must be clear to you
Build before you write, then build as you write
Modularize
Work focused. For long hours
