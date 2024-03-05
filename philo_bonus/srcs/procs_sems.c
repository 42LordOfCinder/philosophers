/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_sems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:23:10 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/05 16:45:48 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_data *data)
{
	int		i;
	long	start_time;
	pid_t	pid;

	start_time = get_mtime();
	i = -1;
	while (++i < data->args.philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].death = &data->death;
		data->philos[i].args = &data->args;
		data->philos[i].start_time = start_time;
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd(2, "Error: Failed to fork\n");
			return (1);
		}
		if (pid != 0)
			data->philos[i].pid = pid;
		else
			routine(&data->philos[i]);
	}
	return (0);
}

int	wait_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.philo_nb)
	{
		if (waitpid(data->philos[i].pid, NULL, 0) == -1)
		{
			ft_putstr_fd(2, "Error: Failed to wait process\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_and_free(t_data *data)
{
	if (data->philos)
		free(data->philos);
}
