/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:12:55 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 02:18:47 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_error(t_data *data, int nb)
{
	int	i;

	if (nb <= 1)
	{
		if (pthread_mutex_destroy(&data->msg_mutex))
			ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
	}
	if (nb <= 2)
	{
		if (pthread_mutex_destroy(&data->death_mutex))
			ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
	}
	if (nb <= 3)
	{
		if (pthread_mutex_destroy(&data->meal_mutex))
			ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
	}
	if (nb <= 4)
	{
		i = -1;
		while (++i < nb)
			if (pthread_mutex_destroy(&data->forks[i - 4]))
				ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
	}
	ft_putstr_fd(2, "Error: Failed to create mutex\n");
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->msg_mutex, NULL))
		return (mutex_error(data, 0));
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (mutex_error(data, 1));
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (mutex_error(data, 2));
	i = -1;
	data->forks = ft_calloc(data->philo_nb, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (mutex_error(data, 3));
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (mutex_error(data, 3 + i));
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = ft_calloc(data->philo_nb, sizeof(t_philo));
	if (!data->philos)
	{
		ft_putstr_fd(2, "Error: Failed memory allocation\n");
		return (1);
	}
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].meals_eaten = 0;
		data->philos[i].death = &data->death;
		data->philos[i].start_time = get_mtime();
		data->philos[i].last_meal_time = data->philos[i].start_time;
		data->philos[i].msg_mutex = &data->msg_mutex;
		data->philos[i].death_mutex = &data->death_mutex;
		data->philos[i].meal_mutex = &data->meal_mutex;
		data->philos[i].fork_left = &data->forks[i];
		if (i == 0)
			data->philos[i].fork_right = &data->forks[data->philo_nb - 1];
		else
			data->philos[i].fork_right = &data->forks[i - 1];
		if (pthread_create(&data->philos[i].t, NULL, &routine, (void *)&data->philos[i]))
		{
			ft_putstr_fd(2, "Error: Error while creating thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}
