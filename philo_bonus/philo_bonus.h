/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:19:25 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/13 09:26:31 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define YES 1
# define NO 0
# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_simulation
{
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*stop;
	sem_t			*eat;
	unsigned int	start;
	int				philo_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_counter;
	int				max_eat;
	int				current_eat;
}		t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	pid_t			pid;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				index;
	int				is_dead;
	int				eat_counter;
}				t_philo;

unsigned int	get_time(void);
void			*check_death(void *arg);
void			ft_process(t_philo *philo);
void			ft_create_process(t_simulation *simulation, t_philo *philo);
int				main(int ac, char **av);
int				put_error(t_simulation *simulation, char *message, int ret);
int				get_number(char *av);
int				assign_rest(t_simulation *simulation, int num, int i);
int				assign_data(t_simulation *simulation, int num, int i);
int				parsing(char **av, t_simulation *simulation);
void			take_fork(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_print_message(int id, t_philo *philo);
void			destroy_and_free(t_simulation *simulation, t_philo *philo);
t_philo			*philo_init(t_simulation *simulation);
void			ft_create_semaphores(t_simulation *simulation);

#endif
