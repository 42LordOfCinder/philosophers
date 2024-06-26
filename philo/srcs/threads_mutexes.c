/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 04:20:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/04/10 08:44:28 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->msg_mutex, NULL);
	i = 0;
	while (i < data->args.philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_philos(t_data *data)
{
	int		i;
	long	start_time;

	i = -1;
	start_time = get_mtime();
	while (++i < data->args.philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].death = &data->death;
		data->philos[i].args = &data->args;
		data->philos[i].death_mutex = &data->death_mutex;
		data->philos[i].msg_mutex = &data->msg_mutex;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		data->philos[i].start_time = start_time;
		if (i == 0)
			data->philos[i].right_fork = &data->forks[data->args.philo_nb - 1];
		if (pthread_create(&data->philos[i].th, NULL, &routine,
				(void *)&data->philos[i]))
		{
			ft_putstr_fd(2, "Error: Failed to create thread\n");
			return (1);
		}
	}
	return (0);
}

int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.philo_nb)
	{
		if (pthread_join(data->philos[i].th, NULL))
		{
			ft_putstr_fd(2, "Error: Failed to join thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_and_free(t_data *data, bool both)
{
	int	i;

	if (both)
	{
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->msg_mutex);
		i = 0;
		while (i < data->args.philo_nb)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
