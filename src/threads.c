/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:00:02 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 22:01:53 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if the value of dead_flag changed
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mtx);
	if (*philo->is_dead == true)
		return (pthread_mutex_unlock(philo->death_mtx), 1);
	pthread_mutex_unlock(philo->death_mtx);
	return (0);
}

//Thread routine
void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (pointer);
}

//creates all threads
int	thread_create(t_program *program, t_mtx *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_all("Error: pthread_create failed", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destroy_all("Error: pthread_create failed", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Error: pthread_join failed", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Error: pthread_join failed", program, forks);
		i++;
	}
	return (0);
}
/*
Create a monitoring thread (observer) 
	oversee the state of the philosophers.
Create a thread for each philosopher
	run the simulation where they perform actions（eat, sleep, and think).
Wait for the monitoring thread and all philosopher threads to finish.
Once all threads have successfully completed, the simulation concludes.
*/
