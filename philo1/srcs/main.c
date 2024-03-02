/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:08:33 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 04:32:13 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->philo_nb = ft_atol(argv[1]);
		data->time_to_die = ft_atol(argv[2]);
		data->time_to_eat = ft_atol(argv[3]);
		data->time_to_sleep = ft_atol(argv[4]);
		if (argc == 6)
			data->goal = ft_atol(argv[5]);
		else
			data->goal = -1;
		if (data->philo_nb <= 0 || data->time_to_die <= 0
			|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
			|| (argc == 6 && data->goal < 0))
		{
			ft_putstr_fd(2, "Error: Bad input\n");
			return (1);
		}
		return (0);
	}
	ft_putstr_fd(2, "Error: Expected 5 or 6 arguments\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv, &data))
		return (1);
	data.forks = ft_calloc(data.philo_nb, sizeof(pthread_mutex_t));
	data.philos = ft_calloc(data.philo_nb, sizeof(t_philo));
	if (!data.forks || !data.philos)
	{
		ft_putstr_fd(2, "Error: Memory allocation failure\n");
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
