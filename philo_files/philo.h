/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:58:50 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/23 10:19:06 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../side_functions/side.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DELAY 10

// ------------------------------
// ---------- structs -----------
// ------------------------------

typedef struct s_global_data
{
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	run1_mutex;
	pthread_mutex_t	stop_mutex;
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

// main funtions
int					global_declarations(t_global_data *global_d, int ac,
						char **av);
void				data_allocation(t_data **data, t_global_data *global_d,
						pthread_t **threads);
void				mutex_declarations(t_global_data *global_d);
int					ft_error(int nb);
void				create_philo(t_data **data, t_global_data *global_d,
						pthread_t **threads);

// process functions
void				*philo_process(void *original_data);
void				*wall_e_process(void *original_data);

// time functions
unsigned long		ft_get_time(void);
void				ft_wait_for(t_global_data *global_declarations,
						unsigned long start_time, unsigned long wait_time);

// fluid funtions 1
int					is_dead(t_data *data, t_global_data *global_d);
int					are_all_fat(t_data **data, t_global_data *global_d);
int					stop_set(t_global_data *global_d);
int					stop_check(t_global_data *global_d);
void				print_msg(t_data *data, char action);
// fluid functions 2
void				thinking_even(t_data *data, t_global_data *global_d);
void				thinking_odd(t_data *data, t_global_data *global_d);
void				eating(t_data *data, t_global_data *global_d);
void				sleeping(t_data *data, t_global_data *global_d);
void				ft_wait_for_all(t_global_data *global_d);
