/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:42:47 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/19 17:17:07 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi_long(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	while (*str == 43 || (*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + ((*str++) - '0');
	return (sign * result);
}

int	return_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc > 6)
		return_error(ERROR_MANY);
	if (argc < 5)
		return_error(ERROR_FEW);
	while (argv[i++])
	{
		if (ft_atoi_long(argv[i]) < 0)
			return_error(ERROR_INV_ARG);
	}
	return (0);
}
