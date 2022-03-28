/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:31:49 by hakim             #+#    #+#             */
/*   Updated: 2022/03/27 14:31:51 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 0
# define FALSE 1

typedef char	t_bool;

typedef struct s_info
{
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				finish_line;
	long			time_of_start;
	int				casualty;
	pthread_mutex_t	print;
	pthread_mutex_t	deadcheck;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_philo
{
	int			backnumber;
	int			eatcount;
	int			left_fork;
	int			right_fork;
	int			is_alive;
	long		last_time_i_ate;
	t_info		*info;
	pthread_t	thread;
}	t_philo;

typedef enum e_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_status;

typedef enum e_failure
{
	SUCCESS,
	FAILURE,
	WRONG_NUM_ARGS,
	NON_NUMERIC_ARGS,
	NON_POSITIVE_NUMERICS,
	MALLOC_FAILURE,
	MUTEX_INIT_FAILURE,
	PTHREAD_CREATE_FAILURE,
	PTHREAD_DETACH_FAILURE,
	GETTIME_FAILURE = -42
}	t_failure;

int		init_info(int ac, char **av, t_info *info);
int		init_philos(t_info *info, t_philo **philos);
int		init_forks(t_info *info);
int		ft_atoi(const char *str);
int		can_be_atoied(char *str);
int		err_msg(t_failure failure);
int		free_all(t_info *info, t_philo *philos);
int		anyone_dead(t_info *info);
long	get_current_time(void);
void	kill_time(long time);
void	ft_putendl_fd(char *s, int fd);
void	declare(t_status status, t_philo *philo);
void	*life_of_philosophers(void *arg);
#endif
