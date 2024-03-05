/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:22:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/05 17:07:45 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

// Structs
typedef struct s_args
{
	int		philo_nb;
	int		goal;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_args;

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	t_args	*args;
	bool	*death;
	long	start_time;
	long	last_meal_time;
	long	meals_eaten;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_args	args;
	bool	death;
}	t_data;

// Main
int		main(int argc, char **argv);

// Utils
bool	msleep(long ms, t_philo *philo);
bool	is_corr(long n);
int		parsing(int argc, char **argv, t_data *data);
void	ft_putstr_fd(int fd, char *str);
long	ft_atol(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
long	get_mtime(void);
void	print_log(char *log, t_philo *philo);

// Processes and semaphores
int		init_philos(t_data *data);
int		wait_philos(t_data *data);
void	destroy_and_free(t_data *data);

// Routine
void	philo_thinks(t_philo *philo);
bool	philo_sleeps(t_philo *philo);
bool	philo_eats(t_philo *philo);
int		check_condition(t_philo *philo);
void	routine(t_philo *philo);
#endif
