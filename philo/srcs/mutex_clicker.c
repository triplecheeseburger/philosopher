/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_clicker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:36:23 by hakim             #+#    #+#             */
/*   Updated: 2022/03/28 21:36:26 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	anyone_dead(t_info *info)
{
	pthread_mutex_lock(&info->deadcheck);
	if (info->casualty > 0)
	{
		pthread_mutex_unlock(&info->deadcheck);
		return (DEAD);
	}
	pthread_mutex_unlock(&info->deadcheck);
	return (THINK);
}

int	anyone_satisfied(int eatcount, t_info *info)
{
	pthread_mutex_lock(&info->satisfied_swine);
	if (eatcount == info->finish_line)
	{
		pthread_mutex_unlock(&info->satisfied_swine);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->satisfied_swine);
	return (FALSE);
}

int everyone_satisfied(t_info *info)
{
	pthread_mutex_lock(&info->satisfied_swine);
	if (info->everyone_satisfied != 0)
	{
		pthread_mutex_unlock(&info->satisfied_swine);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->satisfied_swine);
	return (FALSE);
}
