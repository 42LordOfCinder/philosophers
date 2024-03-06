/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_sems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:23:10 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/06 02:12:32 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("/msg_sem");
	sem_unlink("/forks");
	data->msg_sem = sem_open("/msg_sem", O_CREAT, 0644, 1);
	data->forks = sem_open("/forks", O_CREAT, 0644,
			data->args.philo_nb);
}

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
		data->philos[i].args = &data->args;
		data->philos[i].start_time = start_time;
		data->philos[i].msg_sem = data->msg_sem;
		data->philos[i].forks = data->forks;
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
	int	status;
	int	j;

	i = 0;
	j = -1;
	while (i < data->args.philo_nb)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			ft_putstr_fd(2, "Error: Failed to wait process\n");
			return (1);
		}
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				while (++j < data->args.philo_nb)
					kill(data->philos[j].pid, SIGTERM);
		i++;
	}
	return (0);
}

void	destroy_and_free(t_data *data)
{
	sem_close(data->msg_sem);
	sem_close(data->forks);
	sem_unlink("/msg_sem");
	sem_unlink("/forks");
	if (data->philos)
		free(data->philos);
}
