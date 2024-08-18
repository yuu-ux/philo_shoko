/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:32:48 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 21:47:40 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialize the input from user
void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->num_of_philos = ft_atol(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atol(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

//initialize the philosophers
void	init_philos(t_philo *philos, t_program *program,
		t_mtx *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].meals_eaten = 0;
		init_input(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_mtx = &program->write_mtx;
		philos[i].death_mtx = &program->death_mtx;
		philos[i].meal_mtx = &program->meal_mtx;
		philos[i].is_dead = &program->is_dead;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

/*
for the first philosopher (philos[0]), 
r_fork is the left fork of the last philosopher 
(forks[num_of_philos - 1])
Otherwise it is the i-1th element of the fork array.
*/
void	init_forks(t_mtx *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

//initialize the program structure
void	init_program(t_program *program, t_philo *philos)
{
	program->is_dead = false;
	program->philos = philos;
	pthread_mutex_init(&program->write_mtx, NULL);
	pthread_mutex_init(&program->meal_mtx, NULL);
	pthread_mutex_init(&program->death_mtx, NULL);
}
