/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:44:28 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 00:12:43 by gmassoni         ###   ########.fr       */
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
		if (data->philo_nb <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
			|| data->time_to_sleep <= 0 || (argc == 6 && data->goal < 0))
		{
			ft_putstr_fd(2, "Philo: Bad input\n");
			return (1);
		}
		return (0);
	}
	ft_putstr_fd(2, "Philo: Expected 5 or 6 arguments\n");
	return (1);
}
