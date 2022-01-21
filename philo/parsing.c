/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:56:22 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/12 10:04:27 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	get_number(char *av)
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
			return (ft_error_put(NULL, "Error: Number Only", -1));
		i++;
	}
	return (num);
}

static int	check_last(t_simulation *simulation, int num, int i)
{
	if (i == 5)
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

static int	assign_rest(t_simulation *simulation, int num, int i)
{
	if (i == 3)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_eat CAN'T BE LESS THAN 60 ms", 1));
		simulation->time_to_eat = num;
	}
	else if (i == 4)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_sleep CAN'T BE LESS THAN 60 ms", 1));
		simulation->time_to_sleep = num;
	}
	else
		check_last(simulation, num, i);
	return (0);
}

static int	assign_data(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		simulation->philo_numbers = num;
		simulation->threads = malloc(sizeof(pthread_t) * num);
		simulation->forks = malloc(sizeof(pthread_mutex_t) * num);
	}
	else if (i == 2)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_die CAN'T BE LESS THAN 60 ms", 1));
		simulation->time_to_die = num;
	}
	else
		assign_rest(simulation, num, i);
	return (0);
}

int	ft_parsing(char **av, t_simulation *simulation)
{
	int	num;
	int	i;

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
	simulation->is_dead = NO;
	return (0);
}
