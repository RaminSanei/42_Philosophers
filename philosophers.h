/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/02 19:10:03 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_MANY "Too many arguments.\n"
# define ERROR_FEW "Too few arguments.\n"
# define ERROR_INV_ARG "Invalid arguments.\n"
# define ERROR_JOIN "Error in joining thread.\n"
# define ERROR_CREATE "Error in creating thread.\n"
# define TAKE_FORK "has taken a fork\n"
# define IS_EATING "is eating\n"
# define DIED "died\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define ERROR_MALLOC "Error: malloc failed\n"

typedef pthread_mutex_t	t_mutex;

typedef enum e_operation
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_operation;

typedef struct s_philos
{
	int					id;
	pthread_t			thread_id;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	struct s_data		*data;
	time_t				last_meal;
	bool				alive;
	int					ate_count;
}						t_philos;

typedef struct s_data
{
	int					num_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	long				num_must_eat;
	int					philos_full;
	t_mutex				*forks;
	t_mutex				print;
	time_t				start_time;
	int					dead_philos;
}						t_data;

int						check_input(int argc, char *argv[]);
long					ft_atoi_long(const char *str);
void					init_program_data(t_data *data, char *argv[]);
void					init_philos(t_data *data, t_philos *philos);
void					*philo_check_status(void *philo);
void					*safe_malloc(size_t size);
void					handle_safe_mutex(t_mutex *mutex, t_operation opcode);
void					error_exit(char *str);
void					handle_safe_thread(pthread_t *thread,
							void *(*foo)(void *), void *data,
							t_operation opcode);
time_t					get_precise_time(void);
void					free_allocated_memory(t_data *data, t_philos *philos);
long					get_precise_time(void);
void					precise_sleep(time_t time);

#endif