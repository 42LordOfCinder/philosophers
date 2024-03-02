/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:20:02 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 01:42:06 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

// Structs

typedef struct s_philo
{
	int				id;
	pthread_t		t;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_eaten;
	long			last_meal_time;
	bool			*death;
	long			start_time;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

typedef struct s_data
{
	long			philo_nb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			goal;
	t_philo			*philos;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	*forks;
	bool			death;
}	t_data;

// Main
int		main(int argc, char **argv);

// Utils
void	ft_putstr_fd(int fd, char *str);
void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atol(char *str);
long	get_mtime(void);

// Parsing
int		parsing(int argc, char **argv, t_data *data);

// Init
int		mutex_error(t_data *data, int nb);
int		init_mutex(t_data *data);
int		init_philos(t_data *data);

// Destroy
int		destroy(t_data *data);

// Checking
void	check_end(t_data *data);

// Routine
void	*routine(void *param);

// Actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
#endif
