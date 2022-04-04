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

#include "philosopher_bonus.h"

void	declare(t_status status, t_philo *philo)
{
	long	timestamp;

	sem_wait(philo->info->print);
	sem_wait(philo->info->deadcheck);
	timestamp = get_current_time() - philo->info->time_of_start;
	if (status == FORK && philo->info->casualty == 0)
		printf("%ld %d has taken a fork\n", timestamp, philo->backnumber + 1);
	else if (status == EAT && philo->info->casualty == 0)
		printf("%ld %d is eating\n", timestamp, philo->backnumber + 1);
	else if (status == SLEEP && philo->info->casualty == 0)
		printf("%ld %d is sleeping\n", timestamp, philo->backnumber + 1);
	else if (status == THINK && philo->info->casualty == 0)
		printf("%ld %d is thinking\n", timestamp, philo->backnumber + 1);
	else if (status == DEAD)
		printf("%ld %d is died\n", timestamp, philo->backnumber + 1);
	sem_post(philo->info->deadcheck);
	if (status != DEAD)
		sem_post(philo->info->print);
}

static int	therefore_i_eat(t_philo *philo)
{
	if (get_current_time() - philo->last_time_i_ate \
			> philo->info->time_to_die)
		return (DEAD);
	sem_wait(philo->info->forks);
	declare(FORK, philo);
	sem_wait(philo->info->forks);
	declare(FORK, philo);
	if (get_current_time() - philo->last_time_i_ate \
			> philo->info->time_to_die)
		return (DEAD);
	declare(EAT, philo);
	philo->last_time_i_ate = get_current_time();
	kill_time(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	sem_wait(philo->info->deadcheck);
	philo->eatcount += 1;
	if (philo->eatcount == philo->info->finish_line)
	{
		sem_post(philo->info->deadcheck);
		return (FULL);
	}
	sem_post(philo->info->deadcheck);
	return (THINK);
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

int	life_of_philosophers(void *arg)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)arg;
	if (philo->backnumber % 2 == 0)
		kill_time(philo->info->time_to_sleep - 1);
	while (philo->eatcount != philo->info->finish_line)
	{
		status = therefore_i_eat(philo);
		if (status == FULL)
			exit(FULL);
		else if (status == DEAD)
		{
			declare(DEAD, philo);
			sem_post(philo->info->forks);
			sem_post(philo->info->forks);
			exit(DEAD);
		}
		therefore_i_sleep(philo);
		therefore_i_think(philo);
	}
	exit(FULL);
}
