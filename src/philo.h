/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:45:34 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 21:30:36 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define PHILO_MAX 200

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					is_eating;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	bool				*is_dead;
	t_mtx				*r_fork;
	t_mtx				*l_fork;
	t_mtx				*write_mtx;
	t_mtx				*meal_mtx;
	t_mtx				*death_mtx;
}						t_philo;
// num of philoをポインタにして、t_programと共有してもいいかも
// t_philoからnum_of_philosへのアクセス: どの哲学者からでも、
// philo->num_of_philosを介して、正しい哲学者数にアクセス可能
// 値にアクセスする際はデリファレンスする
// int num = *(philo->num_of_philos);
/*
thread: philo is a thread
id: philo's id
is_eating: 1 if philo is eating, 0 otherwise
meals_eaten: number of meals eaten by philo
last_meal: time of last meal(miliseconds)
time_to_die: time in miliseconds after which philo dies
time_to_eat: time in miliseconds for philo to finish eating
time_to_sleep: time in miliseconds for philo to finish sleeping
start_time: time in miliseconds when the program started
num_of_philos: number of philosophers
num_times_to_eat: number of times each philosopher must eat (optional)
is_dead: flag to check if a philosopher died
r_fork: pointer to a mutex of right fork
l_fork: pointer to a mutex of left fork
write_mtx: pointer to a mutex for writing messages
meal_mtx: pointer to a mutex for meals_eaten
*/

typedef struct s_program
{
	bool				is_dead;
	// int				num_of_philos;
	t_mtx				write_mtx;
	t_mtx				meal_mtx;
	t_mtx				death_mtx;
	t_philo				*philos;
}						t_program;

// main.c
bool					is_arg_digit(char *arg);
int						check_valid_args(char **argv);
void					destroy_all(char *str, t_program *program,
							t_mtx *forks);

// init.c
void					init_program(t_program *program, t_philo *philos);
void					init_forks(t_mtx *forks, int philo_num);
void					init_philos(t_philo *philos, t_program *program,
							t_mtx *forks, char **argv);
void					init_input(t_philo *philo, char **argv);

// threads.c
int						thread_create(t_program *program, t_mtx *forks);
void					*monitor(void *pointer);
void					*philo_routine(void *pointer);

// actions.c
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);

// monitor.c
int						dead_loop(t_philo *philo);
bool					is_end_condition_met(t_philo *philo);
// bool					check_if_all_ate(t_philo *philo);
// bool					check_if_dead(t_philo *philos);
bool					is_each_philo_dead(t_philo *philo, size_t time_to_die);
bool					is_any_philo_dead(t_philo *philos);

// utils.c
// int					ft_atoi(char *str);
long					ft_atol(const char *str);
int						ft_usleep(size_t microseconds);
int						ft_strlen(char *str);
void					print_message(char *str, t_philo *philo, int id);
size_t					get_current_time(void);

#endif