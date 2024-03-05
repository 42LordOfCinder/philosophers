/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:06:31 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/05 23:22:36 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

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
	pthread_t		th;
	int				id;
	bool			*death;
	t_args			*args;
	long			start_time;
	long			last_meal_time;
	long			meals_eaten;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	t_args			args;
	bool			death;
	t_philo			*philos;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	*forks;
}	t_data;

// Main
int		main(int argc, char **argv);

// Utils
bool	is_corr(long n);
int		parsing(int argc, char **argv, t_data *data);
bool	msleep(long ms, t_philo *philo);
void	ft_putstr_fd(int fd, char *str);
long	ft_atol(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
long	get_mtime(void);
void	print_log(char *log, t_philo *philo);

// Threads and mutexes
void	init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		join_philos(t_data *data);
void	destroy_and_free(t_data *data);

// Routine
void	philo_thinks(t_philo *philo);
bool	philo_sleeps(t_philo *philo);
bool	philo_eats(t_philo *philo);
int		check_condition(t_philo *philo);
void	*routine(void *param);
#endif
