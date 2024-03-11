/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:08:33 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/11 15:30:53 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	msleep(long ms, t_philo *philo)
{
	long	start;

	start = get_mtime();
	while (get_mtime() < start + ms)
	{
		usleep(100);
		if (check_condition(philo))
			return (true);
	}
	return (false);
}

bool	is_corr(long n)
{
	if (n <= 0 || n > 2147483647)
		return (false);
	return (true);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->args.philo_nb = ft_atol(argv[1]);
		data->args.time_to_die = ft_atol(argv[2]);
		data->args.time_to_eat = ft_atol(argv[3]);
		data->args.time_to_sleep = ft_atol(argv[4]);
		if (argc == 6)
			data->args.goal = ft_atol(argv[5]);
		else
			data->args.goal = -1;
		if (!is_corr(data->args.philo_nb) || !is_corr(data->args.time_to_die)
			|| !is_corr(data->args.time_to_eat)
			|| !is_corr(data->args.time_to_sleep)
			|| (argc == 6 && (data->args.goal < 0
					|| data->args.goal > 2147483647)))
		{
			ft_putstr_fd(2, "Error: Bad input\n");
			return (1);
		}
		return (0);
	}
	ft_putstr_fd(2, "Error: Expected 4 or 5 arguments\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv, &data))
		return (1);
	data.forks = ft_calloc(data.args.philo_nb, sizeof(pthread_mutex_t));
	data.philos = ft_calloc(data.args.philo_nb, sizeof(t_philo));
	if (!data.forks || !data.philos)
	{
		ft_putstr_fd(2, "Error: Memory allocation failed\n");
		return (1);
	}
	init_mutexes(&data);
	data.death = false;
	if (init_philos(&data) || join_philos(&data))
	{
		destroy_and_free(&data);
		return (1);
	}
	destroy_and_free(&data);
	return (0);
}
