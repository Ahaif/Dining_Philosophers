/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:17:52 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/13 09:52:33 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < get_time())
		{
			sem_wait(philo->data->eat);
			ft_print_message(DIED, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if ((philo->data->eat_counter != -1)
			&& (philo->data->current_eat >= philo->data->max_eat))
		{
			ft_print_message(DONE, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

void	ft_process(t_philo *philo)
{
	pthread_t	death;

	philo->next_meal = get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, check_death, philo);
	pthread_detach(death);
	while (1)
	{
		take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_print_message(THINKING, philo);
	}
}

void	ft_create_process(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulation->philo_numbers)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			ft_process(philo + i);
			exit(0);
		}
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int				i;
	t_simulation	simulation;
	t_philo			*philo;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (parsing(av, &simulation))
			return (1);
		philo = philo_init(&simulation);
		simulation.start = get_time();
		ft_create_semaphores(&simulation);
		sem_wait(simulation.stop);
		ft_create_process(&simulation, philo);
		sem_wait(simulation.stop);
		destroy_and_free(&simulation, philo);
	}
	else
		printf("Error: number of arg is incorrect\n");
	return (0);
}		
