/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 04:20:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 15:06:42 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->msg_mutex, NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].death = &data->death;
		data->philos[i].tte = data->time_to_eat;
		data->philos[i].tts = data->time_to_sleep;
		data->philos[i].ttd = data->time_to_die;
		data->philos[i].goal = data->goal;
		data->philos[i].start_time = get_mtime();
		data->philos[i].last_meal_time = data->philos[i].start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].death_mutex = &data->death_mutex;
		data->philos[i].msg_mutex = &data->msg_mutex;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].philo_nb = data->philo_nb;
		if (i == 0)
			data->philos[i].right_fork = &data->forks[data->philo_nb - 1];
		else
			data->philos[i].right_fork = &data->forks[i - 1];
		if (pthread_create(&data->philos[i].th, NULL, &routine,
			(void *)&data->philos[i]))
		{
			ft_putstr_fd(2, "Error: Failed to creat thread\n");
			return (1);
		}
	}
	return (0);
}

int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
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

void	destroy_and_free(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->msg_mutex);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
