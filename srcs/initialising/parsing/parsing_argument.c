/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:42:18 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/23 16:04:14 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philosopher.h"

static bool	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
int	integer_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

bool	is_valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	if(ac < 5 || ac > 6)
		return (exit_philo(NULL, ERROR_ARGUMENT), false);
	while (i < ac)
	{
		if (!contains_only_digits(av[i]))
			return (exit_philo(NULL, ERROR_DIGIT), false);
		nb = integer_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (exit_philo(NULL, ERROR_NUM_PHILOS), false);
		if (i != 1 && nb == -1)
			return (exit_philo(NULL, ERROR_OVERFLOW_INT), false);
		i++;
	}
	return (true);
}
