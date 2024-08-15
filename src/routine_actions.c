/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:59:54 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 23:26:30 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	philo->is_eating = true;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mtx);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
//dead lock対策が必要？pthread_mutex_trylock
/*
if philo is one: sleep for time_to_die and unlock the fork

Eating:
The philosopher picks up the left fork and displays the status.
The eating flag is set to 1, and a message "eating."
The meal_lock mutex is locked, 
after which the philosopher's last meal time (last_meal) is updated and 
the meal count (meals_eaten) is incremented. 
Once this is done, the mutex is unlocked.
The philosopher waits for the duration of time_to_eat.

Releasing the forks:
The locks on the left and right forks are released
allowing the next philosopher to use them.
*/
