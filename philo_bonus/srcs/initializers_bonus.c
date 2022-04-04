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

#include "philosopher_bonus.h"

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
	info->full_philos = 0;
	return (SUCCESS);
}

sem_t	*init_semaphore(char *label, int num)
{
	sem_t	*semaphore;

	semaphore = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	if (semaphore == SEM_FAILED)
	{
		sem_unlink(label);
		semaphore = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	}
	return (semaphore);
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
		(*philos)[index].last_time_i_ate = info->time_of_start;
		(*philos)[index].info = info;
		++index;
	}
	return (SUCCESS);
}

int	init_forks(t_info *info)
{
	info->forks = init_semaphore("forks", info->num_of_philos);
	if (info->forks == SEM_FAILED)
		return (SEM_FAILURE);
	info->print = init_semaphore("print", 1);
	if (info->print == SEM_FAILED)
		return (SEM_FAILURE);
	info->deadcheck = init_semaphore("deadcheck", 1);
	if (info->deadcheck == SEM_FAILED)
		return (SEM_FAILURE);
	return (SUCCESS);
}
