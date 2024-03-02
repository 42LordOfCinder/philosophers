/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:22:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/02 16:44:16 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Structs
typedef struct s_args
{
	int		philo_nb;
	int		goal;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_args;

typedef struct s_data
{
	t_args	args;
}	t_data;

// Main
int		main(int argc, char **argv);

// Utils
int		parsing(int argc, char **argv, t_data *data);
void	ft_putstr_fd(int fd, char *str);
long	ft_atol(char *str);
#endif
