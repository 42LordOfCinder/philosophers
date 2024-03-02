/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:23:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 16:40:45 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (data->args.philo_nb <= 0 || data->args.time_to_die <= 0
			|| data->args.time_to_eat <= 0 || data->args.time_to_sleep <= 0
			|| (argc == 6 && data->args.goal < 0))
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
	return (0);
}
