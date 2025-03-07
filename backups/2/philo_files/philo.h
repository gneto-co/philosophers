/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:58:50 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:25 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../side_functions/side.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// ------------------------------
// ---------- structs -----------
// ------------------------------

typedef struct s_global_data
{
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	run1_mutex;
	pthread_mutex_t	*forks_mutex;
	long			start_time;
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_get_fat;
	int				stop_signal;
}					t_global_data;

typedef struct s_data
{
	t_global_data	*global_d;
	int				id;
	int				dead;
	char			state;
	int				meals_eaten;
	int				time_of_last_meal;
	int				left;
	int				right;
}					t_data;

typedef struct s_wall_e_data
{
	t_global_data	*global_d;
	t_data			**data;
}					t_wall_e_data;

// ------------------------------
// ---------- functions ---------
// ------------------------------

// philo functions
void				*philo_process(void *original_data);
void				*wall_e_process(void *original_data);
unsigned long		ft_get_time(void);
void				ft_wait_for(t_data *data, unsigned long start_time,
						unsigned long wait_time);
// main
int					global_declarations(t_global_data *global_d, int ac,
						char **av);
void				data_allocation(t_data **data, t_global_data *global_d,
						pthread_t **threads);
void				mutex_declarations(t_global_data *global_d);
int					ft_error(int nb);
void				create_philo(t_data **data, t_global_data *global_d,
						pthread_t **threads);
void				print_msg(t_data *data, char action);
int					is_dead(t_data *data, t_global_data *global_d);
int					stop_check(t_global_data *global_d);