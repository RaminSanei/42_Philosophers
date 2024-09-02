/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:42:47 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/02 14:32:10 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi_long(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == 43 || (*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str > 47 && *str < 58)
			result = (result * 10) + ((*str++) - '0');
		else
			return (INT_MIN);
	}
	return (sign * result);
}

// int	return_error(char *str)
// {
// 	printf("%s\n", str);
// 	return (EXIT_FAILURE);
// }

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc > 6)
		error_exit(ERROR_MANY);
	if (argc < 5)
		error_exit(ERROR_FEW);
	while (argv[++i])
	{
		if (ft_atoi_long(argv[i]) < 0)
			error_exit(ERROR_INV_ARG);
	}
	return (0);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf(ERROR_MALLOC);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
