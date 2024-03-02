/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:11:07 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 03:03:16 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->death == false)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (false);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (true)
	{
		philo_eat(philo);
		if (check_death(philo))
			break ;
		philo_sleep(philo);
		if (check_death(philo))
			break ;
		philo_think(philo);
		if (check_death(philo))
			break ;
	}
	return (NULL);
}
