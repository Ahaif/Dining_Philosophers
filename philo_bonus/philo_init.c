/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:52:07 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/13 09:48:53 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_for_each_philo(t_simulation *simulation, t_philo *philo, int i)
{
	philo[i].index = i;
	philo[i].is_dead = NO;
	philo[i].data = simulation;
	philo[i].pid = -1;
	if (simulation->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = simulation->eat_counter;
}

t_philo	*philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->philo_numbers);
	simulation->death = NULL;
	simulation->stop = NULL;
	simulation->message = NULL;
	simulation->forks = NULL;
	while (++i < simulation->philo_numbers)
		data_for_each_philo(simulation, philo, i);
	return (philo);
}

void	ft_create_semaphores(t_simulation *simulation)
{
	sem_unlink("death");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("forks");
	sem_unlink("eat");
	simulation->death = sem_open("death", O_CREAT, 0600, 1);
	simulation->eat = sem_open("eat", O_CREAT, 0600, 1);
	simulation->message = sem_open("message", O_CREAT, 0600, 1);
	simulation->stop = sem_open("stop", O_CREAT, 0600, 1);
	simulation->forks = sem_open("forks", O_CREAT, 0600,
			simulation->philo_numbers);
}
