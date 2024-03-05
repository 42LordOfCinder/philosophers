/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:42:40 by gmassoni          #+#    #+#             */
/*   Updated: 2024/03/05 23:28:12 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(int fd, char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

long	ft_atol(char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = (res * 10) + (str[i] - 48);
			i++;
		}
		else
			return (-1);
	}
	if (str[i - 1] >= '0' && str[i - 1] <= '9')
		return (res * sign);
	return (-1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((nmemb * size) / nmemb != size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}

long	get_mtime(void)
{
	struct timeval	time;
	long			mtime;

	gettimeofday(&time, NULL);
	mtime = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (mtime);
}

void	print_log(char *log, t_philo *philo)
{
	long	mtime;

	sem_wait(philo->msg_sem);
	mtime = get_mtime() - philo->start_time;
	if (*philo->death == false)
		printf("%ld %d %s\n", mtime, philo->id, log);
	sem_post(philo->msg_sem);
}
