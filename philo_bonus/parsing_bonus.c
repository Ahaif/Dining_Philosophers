/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:32:41 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/13 09:52:31 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	put_error(t_simulation *simulation, char *message, int ret)
{
	if (simulation)
	{
		if (simulation->forks)
			free(simulation->forks);
	}
	printf("%s\n", message);
	return (ret);
}

int	get_number(char *av)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			num = num * 10 + (av[i] - '0');
		else
			return (put_error(NULL, "Error: Arguments are not only numbers",
					-1));
		i++;
	}
	return (num);
}

int	assign_rest(t_simulation *simulation, int num, int i)
{
	if (i == 4)
	{
		if (num < 60)
			return (put_error(simulation,
					"Error: time to sleep can't be less than 60 ms", 1));
		simulation->time_to_sleep = num;
	}
	else if (i == 5)
	{
		if (num == 0)
		{
			simulation->eat_counter = -1;
			simulation->current_eat = -1;
			simulation->max_eat = -1;
		}
		else
		{
			simulation->eat_counter = num;
			simulation->current_eat = 0;
			simulation->max_eat = num * simulation->philo_numbers;
		}
	}
	return (0);
}

int	assign_data(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (put_error(NULL, "Error: No philo is defined", 1));
		simulation->philo_numbers = num;
	}
	else if (i == 2)
	{
		if (num < 60)
			return (put_error(simulation,
					"Error: the time to die can't be less than 60 ms", 1));
		simulation->time_to_die = num;
	}
	else if (i == 3)
	{
		if (num < 60)
			return (put_error(simulation,
					"Error; the time to eat can't be less than 60 ms", 1));
		simulation->time_to_eat = num;
	}
	else
		assign_rest(simulation, num, i);
	return (0);
}

int	parsing(char **av, t_simulation *simulation)
{
	int	i;
	int	num;

	i = 1;
	while (av[i])
	{
		num = get_number(av[i]);
		if (num == -1)
			return (1);
		if (assign_data(simulation, num, i))
			return (1);
		i++;
	}
	if (i == 5)
	{
		simulation->eat_counter = -1;
		simulation->current_eat = -1;
		simulation->max_eat = -1;
	}
	return (0);
}
