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
			(*philos)[index].is_alive = FALSE;
			declare(DEAD, &(*philos)[index]);
			pthread_mutex_lock(&info->deadcheck);
			info->casualty += 1;
			pthread_mutex_unlock(&info->deadcheck);
			pthread_mutex_unlock(&info->forks[(*philos)[index].left_fork]);
			pthread_mutex_unlock(&info->forks[(*philos)[index].right_fork]);
			return ;
		}
		++index;
	}
}

void	*eye_of_beholder(void *arg)
{
	t_philo	**philos;
	int	index;
	int	count;

	philos = (t_philo **)arg;
	while (1)
	{
		roll_call(philos[0]->info, philos);
		if (anyone_dead(philos[0]->info) == DEAD)
		{
			printf("Sadly, we failed to fed philosophers. One is dead!\n");
			return (NULL);
		}
		index = 0;
		count = 0;
		while (index < philos[0]->info->num_of_philos)
		{
			if ((*philos)[index++].eatcount == philos[0]->info->finish_line)
				++count;
			if (count == philos[0]->info->num_of_philos)
			{
				printf("Finally, we fed all philosophers %d meals. Hurray!\n", \
				philos[0]->info->finish_line);
				return (NULL);
			}
		}
	}
}

int	lets_feed_philos(t_info *info, t_philo **philos)
{
	int				status;
	int				index;
	pthread_t 		beholder;

	index = -1;
	status = init_philos(info, philos);
	if (status != SUCCESS)
		return (status);
	status = init_forks(info);
	if (status != SUCCESS)
		return (status);
	pthread_create(&beholder, NULL, eye_of_beholder, philos);
	while (++index < info->num_of_philos)
	{
		status = pthread_create(&(*philos)[index].thread, NULL, \
			life_of_philosophers, &(*philos)[index]);
		if (status != SUCCESS)
			return (PTHREAD_CREATE_FAILURE);
	}
	index = -1;
	pthread_join(beholder, NULL);
	while (++index < info->num_of_philos)
	{
		status = pthread_join((*philos)[index].thread, NULL);
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
//	eye_of_beholder(&philos);
	free_all(&info, &philos);
	return (0);
}
