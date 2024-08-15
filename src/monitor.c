/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:59:46 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 23:24:51 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_mtx);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_mtx);
}

bool	is_each_philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_mtx);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->is_eating == false)
		return (pthread_mutex_unlock(philo->meal_mtx), true);
	pthread_mutex_unlock(philo->meal_mtx);
	return (false);
}
/*
meal_mtx: mutex to protect last_meal and is_eating
This function determines whether a specific philosopher has died
by comparing the time since the philosopher last ate
with the maximum time the philosopher can survive without eating (time_to_die) 
to check if the death condition is met.
If philo is eating, he is not dead. 
*/

bool	is_any_philo_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (is_each_philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].death_mtx);
			*philos[i].is_dead = true;
			pthread_mutex_unlock(philos[0].death_mtx);
			return (true);
		}
		i++;
	}
	return (false);
}
/*
checks all the philosophers, and if any philosopher has died, 
it logs that event and initiates the process to end the simulation
*/

bool	is_end_condition_met(t_philo *philos)
{
	int	i;
	int	philo_finished_eating;

	i = 0;
	philo_finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (false);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_mtx);
		if (philos[i].meals_eaten >= philos[0].num_times_to_eat)
			philo_finished_eating++;
		pthread_mutex_unlock(philos[i].meal_mtx);
		i++;
	}
	if (philo_finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].death_mtx);
		*philos->is_dead = true;
		pthread_mutex_unlock(philos[0].death_mtx);
		return (true);
	}
	return (false);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (is_end_condition_met(philos) || is_any_philo_dead(philos))
			break ;
	}
	return (pointer);
}
/*
continuously checks the termination conditions to ensure 
that the simulation ends either 
when all philos have completed their tasks or when any philo has died.
*/
