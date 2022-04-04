/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:31:36 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 14:31:37 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static t_bool	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (TRUE);
	return (FALSE);
}

int	can_be_atoied(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]) == TRUE)
		++i;
	if (str[i] == '-')
		++i;
	while (str[i] != '\0' && is_white_space(str[i]) == FALSE)
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (FALSE);
		++i;
	}
	while (is_white_space(str[i]) == TRUE && str[i] != '\0')
		++i;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					plma;
	int					index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 9223372036854775807 && plma == 1)
		return (-1);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (0);
	return ((int)result * plma);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (fd < 0 || s == 0)
		return ;
	i = 0;
	while (s[i] != '\0')
		++i;
	write(fd, s, i);
	write(fd, "\n", 1);
}

int	err_msg(t_failure failure)
{
	if (failure == WRONG_NUM_ARGS)
		ft_putendl_fd("Hello??? You've put wrong number of Arguments!", 2);
	else if (failure == NON_NUMERIC_ARGS)
		ft_putendl_fd("NUMERICS! PLEASE", 2);
	else if (failure == NON_POSITIVE_NUMERICS)
		ft_putendl_fd("Only positive numbers are available", 2);
	else if (failure == MALLOC_FAILURE)
		ft_putendl_fd("Malloc seems to be failed on some point", 2);
	else
	{
		if (failure == SEM_FAILURE)
			write(2, "sem_open", 8);
		else if (failure == FORK_FAILURE)
			write(2, "fork", 4);
		else if (failure == GETTIME_FAILURE)
			write(2, "gettimeofday", 12);
		ft_putendl_fd(" function have been failed", 2);
	}
	return (1);
}
