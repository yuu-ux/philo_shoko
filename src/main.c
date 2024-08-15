/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:45:17 by ssoeno            #+#    #+#             */
/*   Updated: 2024/08/12 21:51:13 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ./philo
timestamps > 60 ms
USLEEP function want usec
*/
#include "philo.h"

bool	is_arg_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(const char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (*str == '\0')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		if (ret > LONG_MAX / 10 || (ret == LONG_MAX / 10 && *str > '7'))
			return (LONG_MAX);
		if (ret < LONG_MIN / 10 || (ret == LONG_MIN / 10 && *str > '8'))
			return (LONG_MIN);
		ret = ret * 10 + (*str++ - '0');
	}
	return (ret * sign);
}

/* number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */
int	check_valid_args(char **argv)
{
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_num;

	philo_num = ft_atol(argv[1]);
	time_to_die = ft_atol(argv[2]);
	time_to_eat = ft_atol(argv[3]);
	time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		meals_num = ft_atol(argv[5]);
	if (philo_num > PHILO_MAX || philo_num <= 0 || !is_arg_digit(argv[1]))
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (time_to_die <= 60 || !is_arg_digit(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (time_to_eat <= 60 || !is_arg_digit(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (time_to_sleep <= 60 || !is_arg_digit(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (meals_num < 0 || meals_num == 1)
		return (write(2, "Invalid number of meals\n", 25), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		philos[PHILO_MAX];
	t_mtx		forks[PHILO_MAX];

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments\n", 29), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
