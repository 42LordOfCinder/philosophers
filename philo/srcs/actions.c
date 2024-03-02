/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:03:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 02:51:26 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *log, t_philo *philo)
{
	long	mtime;

	mtime = get_mtime() - philo->start_time;
	pthread_mutex_lock(philo->msg_mutex);
	printf("%ld %d %s\n", mtime, philo->id, log);
	pthread_mutex_unlock(philo->msg_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_log("has taken a fork", philo);
	pthread_mutex_lock(philo->fork_left);
	print_log("has taken a fork", philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meals_eaten++;
	philo->last_meal_time = get_mtime();
	pthread_mutex_unlock(philo->meal_mutex);
	print_log("is eating", philo);
	usleep(1000 * philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_sleep(t_philo *philo)
{
	print_log("is sleeping", philo);
	usleep(1000 * philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_log("is thinking", philo);
}
