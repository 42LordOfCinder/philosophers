/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:16:47 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 02:13:49 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tmp_join(t_data *data)
{
	for (int i = 0; i < data->philo_nb; i++)
		pthread_join(data->philos[i].t, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv, &data) || init_mutex(&data))
		return (1);
	data.death = false;
	if (init_philos(&data))
	{
		destroy(&data);
		return (1);
	}
	check_end(&data);
	tmp_join(&data);
	if (destroy(&data))
		return (1);
	return (0);
}
