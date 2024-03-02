/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:30:42 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 01:45:00 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy(t_data *data)
{
	int	i;
	int ret;

	ret = 0;
	if (pthread_mutex_destroy(&data->msg_mutex)
		|| pthread_mutex_destroy(&data->death_mutex)
		|| pthread_mutex_destroy(&data->meal_mutex))
	{
		ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
		ret = 1;
	}
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
		{
			ft_putstr_fd(2, "Error: Failed to destroy mutex\n");
			ret = 1;
		}
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	return (ret);
}
