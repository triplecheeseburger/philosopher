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

#include "philosopher_bonus.h"

int	roll_call(t_info *info, t_philo **philos)
{
	int	index;

	index = 0;
	while (index < info->num_of_philos)
	{
		if (get_current_time() - (*philos)[index].last_time_i_ate \
			> info->time_to_die)
		{
			sem_wait(info->deadcheck);
			info->casualty += 1;
			sem_post(info->deadcheck);
			(*philos)[index].is_alive = FALSE;
			declare(DEAD, &(*philos)[index]);
			printf("Sadly, we failed to fed philosophers. One is dead!\n");
			sem_post(info->forks);
			sem_post(info->forks);
			return (DEAD);
		}
		++index;
	}
	return (THINK);
}

void	eye_of_beholder(t_info *info, t_philo **philos)
{
	int	index;
	int	check;

	while (info->full_philos != info->finish_line)
	{
		waitpid(-1, &check, 0);
		if (WIFEXITED(check) && WEXITSTATUS(check) == DEAD)
		{
			info->casualty += 1;
			break ;
		}
		else if (WIFEXITED(check) && WEXITSTATUS(check) == FULL)
			info->full_philos += 1;
	}
	if (info->casualty != 0)
	{
		index = -1;
		while (++index < info->num_of_philos)
			kill((*philos)[index].pid, SIGTERM);
		printf("Sadly, we failed to fed philosophers. One is dead!\n");
	}
	if (info->full_philos == info->finish_line && info->casualty == 0)
		printf("Finally, we fed all philosophers %d meals. Hurray!\n", \
			info->finish_line);
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
		(*philos)[index].pid = fork();
		if ((*philos)[index].pid == 0)
			life_of_philosophers(&(*philos)[index]);
		else if ((*philos)[index].pid < 0)
			return (FORK_FAILURE);
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
	free_all(&info, philos);
	return (0);
}
