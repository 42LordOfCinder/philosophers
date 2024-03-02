/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:47:09 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 03:01:15 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_died(t_data *data)
{
	int		i;
	int		inter;
	long	mtime;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->meal_mutex);
		inter = get_mtime() - data->philos[i].last_meal_time;
		if (inter > data->time_to_die)
		{
			pthread_mutex_lock(&data->msg_mutex);
			mtime = get_mtime() - data->philos[i].start_time;
			printf("%ld %d died\n", mtime, i + 1);
			pthread_mutex_unlock(&data->msg_mutex);
			data->death = true;
			pthread_mutex_unlock(&data->meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (false);
}

bool	end_condition(t_data *data)
{
	int	i;
	int	goals;

	pthread_mutex_lock(&data->death_mutex);
	if (has_died(data))
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->death_mutex);
	i = 0;
	goals = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->philo_nb)
	{
		if (data->philos[i].meals_eaten >= data->goal)
			goals++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (goals == data->philo_nb)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	return (false);
}

void	check_end(t_data *data)
{
	while (1)
	{
		if (end_condition(data))
			break ;
	}
}
