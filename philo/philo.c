/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:55:03 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/12 10:10:46 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_for_each_philo(t_simulation *simulation, t_philo *philo, int i)
{
	philo[i].index = i;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % simulation->philo_numbers;
	philo[i].is_dead = NO;
	philo[i].data = simulation;
	philo[i].eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[i].eat, NULL);
	if (simulation ->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = simulation->eat_counter;
}

void	create_mutex(t_simulation *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_init(simulation->message, NULL);
	pthread_mutex_init(simulation->death, NULL);
	pthread_mutex_init(simulation->stop, NULL);
	while (i < simulation->philo_numbers)
		pthread_mutex_init(simulation->forks + i++, NULL);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < get_time())
		{
			philo->data->is_dead = YES;
			pthread_mutex_lock(philo->eat);
			ft_print_message(DIED, philo);
			pthread_mutex_unlock(philo->data->stop);
			break ;
		}
	}
	return (NULL);
}

void	*ft_process(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	philo->next_meal = get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, check_death, philo);
	pthread_detach(death);
	while (1)
	{
		if (philo->data->is_dead)
			break ;
		take_fork(philo);
		ft_eat(philo);
		if (!check_eat(philo))
			break ;
		ft_sleep(philo);
		ft_print_message(THINKING, philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	t_simulation	simulation;
	t_philo			*philo;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(av, &simulation))
			return (0);
		philo = philo_init(&simulation);
		simulation.start = get_time();
		create_mutex(&simulation);
		pthread_mutex_lock(simulation.stop);
		while (i < simulation.philo_numbers)
		{
			pthread_create(simulation.threads + i, NULL, ft_process, philo + i);
			pthread_detach(simulation.threads[i++]);
			usleep(100);
		}
		pthread_mutex_lock(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	else
		printf("Error: Number of arguments\n");
	return (0);
}
