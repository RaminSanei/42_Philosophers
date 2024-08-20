/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:21:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/20 19:37:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

static void	handle_mutex_error(int status, t_operation opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid\n");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid\n");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the \
         thread blocked waiting for the mutex\n");
	else if (status == EPERM)
		error_exit("The current thread does not hold the mutex lock\n");
	else if (status == ENOMEM)
		error_exit("Insufficient memory exists to initialize the mutex\n");
	else if (status == EBUSY)
		error_exit("Mutex is already locked\n");
}

void	handle_safe_mutex(t_mutex *mutex, t_operation opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
	{
		printf("Error: Invalid operation\n");
		exit(EXIT_FAILURE);
	}
}

static void	handle_thread_error(int status, t_operation opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create thread\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The target thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to \
         that specified by the given thread ID\n");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of \
         thread specifies the calling thread\n");
}

void	handle_safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
		t_operation opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode thread handle: use CREATE, JOIN or DETACH");
}
