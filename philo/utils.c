/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:48:49 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/12 10:09:52 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_all(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(simulation->death);
	pthread_mutex_destroy(simulation->message);
	pthread_mutex_destroy(simulation->stop);
	while (i < simulation->philo_numbers)
	{
		pthread_mutex_destroy(simulation->forks + i);
		pthread_mutex_destroy(philo[i].eat);
		free(philo[i].eat);
		i++;
	}
	free(philo);
	free(simulation->forks);
	free(simulation->threads);
	free(simulation->death);
	free(simulation->message);
	free(simulation->stop);
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_error_put(t_simulation *simulation, char *message, int ret)
{
	if (simulation)
	{
		if (simulation->threads)
			free (simulation->threads);
		if (simulation->forks)
			free (simulation->forks);
	}
	printf("%s\n", message);
	return (ret);
}

t_philo	*philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->philo_numbers);
	simulation->stop = malloc(sizeof(pthread_mutex_t));
	simulation->death = malloc(sizeof(pthread_mutex_t));
	simulation->message = malloc(sizeof(pthread_mutex_t));
	while (++i < simulation->philo_numbers)
		data_for_each_philo(simulation, philo, i);
	return (philo);
}
