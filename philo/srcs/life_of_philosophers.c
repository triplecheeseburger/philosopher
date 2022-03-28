/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:14:31 by hakim             #+#    #+#             */
/*   Updated: 2022/03/28 20:02:06 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	declare(t_status status, t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->info->print);
	pthread_mutex_lock(&philo->info->deadcheck);
	pthread_mutex_lock(&philo->info->satisfied_swine);
	timestamp = get_current_time() - philo->info->time_of_start;
	if (status == FORK && philo->info->casualty == 0 && philo->info->everyone_satisfied == 0)
		printf("%ld %d has taken a fork\n", timestamp, philo->backnumber);
	else if (status == EAT && philo->info->casualty == 0 && philo->info->everyone_satisfied == 0)
		printf("%ld %d is eating\n", timestamp, philo->backnumber);
	else if (status == SLEEP && philo->info->casualty == 0 && philo->info->everyone_satisfied == 0)
		printf("%ld %d is sleeping\n", timestamp, philo->backnumber);
	else if (status == THINK && philo->info->casualty == 0 && philo->info->everyone_satisfied == 0)
		printf("%ld %d is thinking\n", timestamp, philo->backnumber);
	else if (status == DEAD)
		printf("%ld %d is died\n", timestamp, philo->backnumber);
	pthread_mutex_unlock(&philo->info->satisfied_swine);
	pthread_mutex_unlock(&philo->info->deadcheck);
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
	pthread_mutex_lock(&philo->info->deadcheck);
	philo->eatcount += 1;
	pthread_mutex_unlock(&philo->info->deadcheck);
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
		if (anyone_dead(philo->info) == DEAD
			|| everyone_satisfied(philo->info) == TRUE)
			return (NULL);
		therefore_i_eat(philo);
		if (anyone_dead(philo->info) == DEAD || philo->is_alive == FALSE
			|| everyone_satisfied(philo->info) == TRUE)
			return (NULL);
		therefore_i_think(philo);
		therefore_i_sleep(philo);
	}
	return (NULL);
}
