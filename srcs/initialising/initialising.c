/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:13:17 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/22 20:31:31 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"
/*
int checking_integer_valid(float number)
{
	if(number_philosopher < INT_MIN_NUMBER || number > INT_MAX_NUMBER)
}
*/

int checking_number_philosopher(char *str_philosopher)
{
    double number_philosopher;
    
    number_philosopher = ft_atod(str_philosopher);
    if (number_philosopher <= 0 || number_philosopher > 200)
        return (0);
    return ((int)number_philosopher);
}

t_philo *initialising_philosopher(int argc, char **argv)
{
    t_philo *philosopher;

    if (argc != 5 && argc != 6)
		exit_philo(NULL);
    philosopher = (t_philo *)malloc(sizeof(t_philo));
    if (!philosopher)
		exit_philo(NULL);
    philosopher->num_of_philos = checking_number_philosopher(argv[1]);
    if (!philosopher->num_of_philos)
		exit_philo(philosopher);
    return (philosopher);
}
