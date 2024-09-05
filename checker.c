/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:42:47 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/04 21:02:35 by ssanei           ###   ########.fr       */
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

int	error_exit(char *message)
{
	printf("%s", message);
	return (EXIT_FAILURE);
}

int	check_input(int argc, char **argv)
{
	if (ft_atoi_long(argv[1]) < 1)
		return (error_exit(NO_PHILO));
	if (argc > 6)
		return (error_exit(ERROR_MANY));
	if (argc < 5)
		return (error_exit(ERROR_FEW));
	if (ft_atoi_long(argv[2]) < 0 || ft_atoi_long(argv[3]) < 0
		|| ft_atoi_long(argv[4]) < 0)
		return (error_exit(ERROR_NEG));
	if (argv[5])
	{
		if (ft_atoi_long(argv[5]) < 0)
			return (error_exit(ERROR_NEG));
	}
	return (EXIT_SUCCESS);
}
