/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:54:04 by hakim             #+#    #+#             */
/*   Updated: 2022/03/28 20:01:19 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		return (GETTIME_FAILURE);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	kill_time(long time)
{
	long	target_time;

	target_time = time + get_current_time();
	if (time > 10)
		usleep((time - 10) * 1000);
	while (target_time > get_current_time())
		usleep(50);
}

static void	check_and_destroy_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

int	free_all(t_info *info, t_philo **philos)
{
	int	i;

	usleep(1000);
	i = -1;
	while (++i < info->num_of_philos)
		check_and_destroy_mutex(&info->forks[i]);
	check_and_destroy_mutex(&info->print);
	check_and_destroy_mutex(&info->deadcheck);
	check_and_destroy_mutex(&info->satisfied_swine);
	free(*philos);
	free(info->forks);
	return (SUCCESS);
}

