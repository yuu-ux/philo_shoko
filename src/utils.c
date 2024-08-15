/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:32:48 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 21:41:04 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	destroy_all(char *str, t_program *program, t_mtx *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_mtx);
	pthread_mutex_destroy(&program->death_mtx);
	pthread_mutex_destroy(&program->meal_mtx);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t milliseconds)
{
	size_t	initial_time;

	initial_time = get_current_time();
	while (get_current_time() - initial_time < milliseconds)
		usleep(100);
	return (0);
}
/*
High-precision waiting
By repeatedly calling usleep, it allows for accurate sleep in milliseconds.

Efficient CPU usage
The function waits in short intervals (100 microseconds) within the loop, 
allowing other processes to interrupt 
while still ensuring the specified time has elapsed.

milliseconds(ms): 1e-3 seconds
microseconds(us): 1e-6 seconds 
*/

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday error\n", 20);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
