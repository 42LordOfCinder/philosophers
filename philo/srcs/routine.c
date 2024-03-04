/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 04:26:08 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/04 17:16:52 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thinks(t_philo *philo)
{
	print_log("is thinking", philo);
}

bool	philo_sleeps(t_philo *philo)
{
	print_log("is sleeping", philo);
	if (msleep(philo->args->time_to_sleep, philo))
		return (true);
	return (false);
}

bool	philo_eats(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->right_fork);
	print_log("has taken a fork", philo);
	if (philo->args->philo_nb == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (msleep(philo->args->time_to_die, philo));
	}
	pthread_mutex_lock(philo->left_fork);
	print_log("has taken a fork", philo);
	philo->meals_eaten++;
	philo->last_meal_time = get_mtime();
	print_log("is eating", philo);
	res = msleep(philo->args->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (res)
		return (true);
	return (false);
}

int	check_condition(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->death == true)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (true);
	}
	if (get_mtime() - philo->last_meal_time >= philo->args->time_to_die)
	{
		print_log("died", philo);
		*philo->death = true;
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	if (philo->meals_eaten == philo->args->goal)
		return (1);
	return (0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->start_time = get_mtime();
	philo->last_meal_time = philo->start_time;
	philo->meals_eaten = 0;
	if (philo->id % 2 == 0)
		msleep(philo->args->time_to_eat / 10, philo);
	while (true)
	{
		if (philo_eats(philo))
			break ;
		if (philo_sleeps(philo))
			break ;
		philo_thinks(philo);
		if (check_condition(philo))
			break ;
	}
	return (NULL);
}
