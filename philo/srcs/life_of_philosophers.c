/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:14:31 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 22:14:36 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	declare(t_status status, t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->info->print);
	timestamp = get_current_time() - philo->info->time_of_start;
	if (status == FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->backnumber);
	else if (status == EAT)
		printf("%ld %d is eating\n", timestamp, philo->backnumber);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, philo->backnumber);
	else if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, philo->backnumber);
	else
	{
		printf("%ld %d is died\n", timestamp, philo->backnumber);
		return ;
	}
	pthread_mutex_unlock(&philo->info->print);
}

static void	therefore_i_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	declare(FORK, philo);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	declare(FORK, philo);
	declare(EAT, philo);
	philo->last_time_i_ate = get_current_time();
	philo->eatcount += 1;
	kill_time(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
}

static void	therefore_i_sleep(t_philo *philo)
{
	declare(SLEEP, philo);
	kill_time(philo->info->time_to_sleep);
}

static void	therefore_i_think(t_philo *philo)
{
	declare(THINK, philo);
}

void	*life_of_philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->backnumber % 2 == 0)
		kill_time(philo->info->time_to_sleep - 1);
	while (philo->eatcount != philo->info->finish_line)
	{
		if (philo->info->casualty > 0)
			return (NULL);
		therefore_i_eat(philo);
		if (philo->info->casualty > 0 || philo->is_alive == FALSE)
			return (NULL);
		therefore_i_think(philo);
		therefore_i_sleep(philo);
	}
	return (NULL);
}
