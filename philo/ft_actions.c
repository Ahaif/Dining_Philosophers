/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:57:21 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/12 10:08:41 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_hand]);
	ft_print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_hand]);
	ft_print_message(FORK, philo);
}

int	check_eat(t_philo *philo)
{
	if ((philo->data->eat_counter != -1)
		&& (philo->data->current_eat >= philo->data->max_eat))
	{
		philo->data->is_dead = YES;
		pthread_mutex_lock(philo->eat);
		ft_print_message(DONE, philo);
		pthread_mutex_unlock(philo->data->stop);
		return (0);
	}
	return (1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	ft_print_message(EATING, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	philo->eating_time = get_time();
	philo->next_meal = philo->eating_time
		+ (unsigned int)philo->data->time_to_die;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_hand]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_hand]);
	pthread_mutex_unlock(philo->eat);
}

void	ft_sleep(t_philo *philo)
{
	usleep(10);
	ft_print_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_print_message(int id, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->data->message);
	time = get_time() - philo->data->start;
	if (id == FORK)
		printf("%u\t%d has taken a fork\n", time, philo->index + 1);
	else if (id == EATING)
		printf("%u\t%d is eating\n", time, philo->index + 1);
	else if (id == SLEEPING)
		printf("%u\t%d is sleeping\n", time, philo->index + 1);
	else if (id == THINKING)
		printf("%u\t%d is thinking\n", time, philo->index + 1);
	else if (id == DIED)
		printf("%u\t%d died\n", time, philo->index + 1);
	else if (id == DONE)
		printf("Simulation is Done :)\n");
	if (id != DIED && id != DONE)
		pthread_mutex_unlock(philo->data->message);
}
