/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/08 18:05:17 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if is thinking go to the (fork_mutex) line
static void	thinking(t_data *data, t_global_data *global_d)
{
	if (is_dead(data, global_d))
		return ;
	ft_print_msg(data, 't');
	pthread_mutex_lock(&(global_d->forks_mutex[data->left]));
	ft_print_msg(data, 'f');
	pthread_mutex_lock(&(global_d->forks_mutex[data->right]));
	ft_print_msg(data, 'f');
	data->state = 'e';
}

// if is eating just need to eat and then release the forks
static void	eating(t_data *data, t_global_data *global_d)
{
	if (!is_dead(data, global_d))
	{
		pthread_mutex_lock(&(global_d->dead_mutex));
		data->time_of_last_meal = ft_get_time();
		pthread_mutex_unlock(&(global_d->dead_mutex));
	}
	ft_print_msg(data, 'e');
	ft_wait_for(data, ft_get_time(), global_d->time_to_eat);
	pthread_mutex_unlock(&(global_d->forks_mutex[data->left]));
	pthread_mutex_unlock(&(global_d->forks_mutex[data->right]));
	data->state = 's';
}

// if is sleeping just need to wait
static void	sleeping(t_data *data, t_global_data *global_d)
{
	if (is_dead(data, global_d))
		return ;
	ft_print_msg(data, 's');
	ft_wait_for(data, ft_get_time(), global_d->time_to_sleep);
	data->state = 't';
}

static int	action(t_data *data, t_global_data *global_d)
{
	if (data->state == 't')
		thinking(data, global_d);
	if (data->state == 'e')
		eating(data, global_d);
	if (data->state == 's')
		sleeping(data, global_d);
	is_dead(data, global_d);
	return (stop_check(global_d));
}

void	*philo_process(void *original_data)
{
	t_data			*data;
	t_global_data	*global_d;

	data = (t_data *)original_data;
	global_d = data->global_d;
	pthread_mutex_lock(&(global_d->run_mutex));
	pthread_mutex_unlock(&(global_d->run_mutex));
	// ft_print_msg(data, 'a');
	data->time_of_last_meal = global_d->start_time;
	if (data->id % 2)
	{
		// ft_print_msg(data ,'w');
		usleep(400);
	}
	// ft_wait_for(data, ft_get_time(), 300);
	while (1)
	{
		usleep(10);
		if (action(data, global_d))
			break ;
	}
	(void)action;
	pthread_exit(NULL);
}
