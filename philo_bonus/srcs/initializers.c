/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:52:50 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 16:52:51 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_info(int ac, char **av, t_info *info)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (can_be_atoied(av[i]) == FALSE)
			return (NON_NUMERIC_ARGS);
		if (ft_atoi(av[i]) < 0)
			return (NON_POSITIVE_NUMERICS);
	}
	info->num_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->finish_line = ft_atoi(av[5]);
	else
		info->finish_line = -1;
	info->time_of_start = get_current_time();
	if (info->time_of_start == GETTIME_FAILURE)
		return (GETTIME_FAILURE);
	info->casualty = 0;
	return (SUCCESS);
}

int	init_philos(t_info *info, t_philo **philos)
{
	int	index;

	*philos = malloc(sizeof(t_philo) * info->num_of_philos);
	if (*philos == NULL)
		return (MALLOC_FAILURE);
	index = 0;
	while (index < info->num_of_philos)
	{
		(*philos)[index].backnumber = index;
		(*philos)[index].eatcount = 0;
		(*philos)[index].left_fork = index;
		(*philos)[index].right_fork = index + 1;
		(*philos)[index].last_time_i_ate = info->time_of_start;
		(*philos)[index].is_alive = TRUE;
		(*philos)[index].info = info;
		(*philos)[index].thread = NULL;
		++index;
	}
	(*philos)[index - 1].right_fork = 0;
	return (SUCCESS);
}

int	init_forks(t_info *info)
{
	int	index;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (info->forks == NULL)
		return (MALLOC_FAILURE);
	index = -1;
	while (++index < info->num_of_philos)
		if (pthread_mutex_init(&info->forks[index], NULL) != 0)
			return (MUTEX_INIT_FAILURE);
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (MUTEX_INIT_FAILURE);
	return (SUCCESS);
}
