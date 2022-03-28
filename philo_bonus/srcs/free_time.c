/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:54:04 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 16:54:05 by hakim            ###   ########.fr       */
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

int	free_all(t_info *info, t_philo **philos)
{
	int	i;

	usleep(1000);
	i = -1;
	while (++i < info->num_of_philos)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->print);
	free(*philos);
	free(info->forks);
	return (SUCCESS);
}
