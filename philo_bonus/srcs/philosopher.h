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
# include <semaphore.h>
# include <signal.h>

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
	int				full_philos;
	sem_t			*print;
	sem_t			*deadcheck;
	sem_t			*forks;
}	t_info;

typedef struct s_philo
{
	int			backnumber;
	int			eatcount;
	int			left_fork;
	int			right_fork;
	int			is_alive;
	long		last_time_i_ate;
	pid_t		pid;
	t_info		*info;
}	t_philo;

typedef enum e_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	FULL
}	t_status;

typedef enum e_failure
{
	SUCCESS,
	FAILURE,
	WRONG_NUM_ARGS,
	NON_NUMERIC_ARGS,
	NON_POSITIVE_NUMERICS,
	MALLOC_FAILURE,
	SEM_FAILURE,
	FORK_FAILURE,
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
int		life_of_philosophers(void *arg);
long	get_current_time(void);
void	kill_time(long time);
void	ft_putendl_fd(char *s, int fd);
void	declare(t_status status, t_philo *philo);
#endif
