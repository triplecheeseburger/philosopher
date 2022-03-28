/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:31:44 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 14:31:45 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	roll_call(t_info *info, t_philo **philos)
{
	int	index;

	index = 0;
	while (index < info->num_of_philos)
	{
		if (get_current_time() - (*philos)[index].last_time_i_ate \
			> info->time_to_die)
		{
			pthread_mutex_lock(&info->deadcheck);
			info->casualty += 1;
			pthread_mutex_unlock(&info->deadcheck);
			(*philos)[index].is_alive = FALSE;
			declare(DEAD, &(*philos)[index]);
			pthread_mutex_unlock(&info->forks[(*philos)[index].left_fork]);
			pthread_mutex_unlock(&info->forks[(*philos)[index].right_fork]);
			return ;
		}
		++index;
	}
}

void	eye_of_beholder(t_info *info, t_philo **philos)
{
	int	index;
	int	count;

	while (1)
	{
		roll_call(info, philos);
		if (anyone_dead(info) == DEAD)
		{
			printf("Sadly, we failed to fed philosophers. One is dead!\n");
			return ;
		}
		index = 0;
		count = 0;
		while (index < info->num_of_philos)
		{
			if (anyone_satisfied((*philos)[index++].eatcount, info) == TRUE)
				++count;
			if (count == info->num_of_philos)
			{
				pthread_mutex_lock(&info->satisfied_swine);
				info->everyone_satisfied += 1;
				pthread_mutex_unlock(&info->satisfied_swine);
				printf("Finally, we fed all philosophers %d meals. Hurray!\n", \
				info->finish_line);
				return ;
			}
		}
	}
}

int	lets_feed_philos(t_info *info, t_philo **philos)
{
	int				status;
	int				index;

	index = -1;
	status = init_philos(info, philos);
	if (status != SUCCESS)
		return (status);
	status = init_forks(info);
	if (status != SUCCESS)
		return (status);
	while (++index < info->num_of_philos)
	{
		status = pthread_create(&(*philos)[index].thread, NULL, \
			life_of_philosophers, &(*philos)[index]);
		if (status != SUCCESS)
			return (PTHREAD_CREATE_FAILURE);
		status = pthread_detach((*philos)[index].thread);
		if (status != SUCCESS)
			return (PTHREAD_DETACH_FAILURE);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philos;
	int		status;

	if (ac != 5 && ac != 6)
		return (err_msg(WRONG_NUM_ARGS));
	status = init_info(ac, av, &info);
	if (status != SUCCESS)
		return (err_msg(status));
	status = lets_feed_philos(&info, &philos);
	if (status != SUCCESS)
		return (err_msg(status));
	eye_of_beholder(&info, &philos);
	free_all(&info, &philos);
	system("leaks philo");
	return (0);
}
