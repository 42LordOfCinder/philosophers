/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:26:02 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/05 17:00:00 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	// lock right fork
	print_log("has taken a fork", philo);
	if (philo->args->philo_nb == 1)
		// unlock right fork
		return (msleep(philo->args->time_to_die, philo));
	// lock left fork
	print_log("has taken a fork", philo);
	philo->meals_eaten++;
	philo->last_meal_time = get_mtime();
	print_log("is eating", philo);
	res = msleep(philo->args->time_to_eat, philo);
	// unlock left fork
	// unlock right fork
	if (res)
		return (true);
	return (false);
}

int	check_condition(t_philo *philo)
{
	if (*philo->death == true)
		return (true);
	if (get_mtime() - philo->last_meal_time >= philo->args->time_to_die)
	{
		print_log("died", philo);
		*philo->death = true;
		return (1);
	}
	if (philo->meals_eaten == philo->args->goal)
		return (1);
	return (0);
}

void	routine(t_philo *philo)
{
	philo->last_meal_time = philo->start_time;
	philo->meals_eaten = 0;
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
	exit(0);
}
