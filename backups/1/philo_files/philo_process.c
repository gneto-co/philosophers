/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/03 12:48:11 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if philo starve:
//  change the state to death
//  turn on the stop_signal
//  put death message
//  return 1
// else if stop_signal already on
//  return 1
// else
//  return 0
int	is_dead(t_data *data, t_global_data *global_d)
{
	if (stop_check(global_d))
		return (1);
	// !! early death, not forget to remove !!
	if ((data->left == data->right) || ((int)ft_get_time()
			- data->time_of_last_meal >= global_d->time_to_die))
	{
		ft_print_msg(data, 'd');
		data->state = 'd';
		pthread_mutex_lock(&(global_d->write_mutex));
		data->dead = 1;
		global_d->stop_signal = 1;
		pthread_mutex_unlock(&(global_d->write_mutex));
		return (1);
	}
	return (0);
}

// if stop_signal is on return 1
// else return 0
int	stop_check(t_global_data *global_d)
{
	int	r;

	r = 0;
	pthread_mutex_lock(&(global_d->write_mutex));
	// if there is a signal to stop, return 1
	if (global_d->stop_signal)
	{
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->write_mutex));
	return (r);
}

// if is thinking go to the (fork_mutex) line
static void	thinking(t_data *data, t_global_data *global_d)
{
	if (is_dead(data, global_d))
		return ;
	ft_print_msg(data, 't');
	ft_print_msg(data, 'j');
	pthread_mutex_lock(&(global_d->forks_mutex[data->left]));
	ft_print_msg(data, 'l');
	ft_print_msg(data, 'k');
	pthread_mutex_lock(&(global_d->forks_mutex[data->right]));
	ft_print_msg(data, 'r');
	data->state = 'e';
}

// if is eating just need to eat and then release the forks
static void	eating(t_data *data, t_global_data *global_d)
{
	data->meals_eaten++;
	data->time_of_last_meal = ft_get_time();
	ft_print_msg(data, 'e');
	ft_wait_for(data, ft_get_time(), global_d->time_to_eat);
	pthread_mutex_unlock(&(global_d->forks_mutex[data->left]));
	ft_print_msg(data, 'i');
	pthread_mutex_unlock(&(global_d->forks_mutex[data->right]));
	ft_print_msg(data, 'o');
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
	// wait for other processes to start
	pthread_mutex_lock(&(global_d->run_mutex));
	pthread_mutex_unlock(&(global_d->run_mutex));
	// set last meal to start time
	data->time_of_last_meal = global_d->start_time;
	// delay even number philos
	if (data->id % 2)
		usleep(30);
	// loop
	while (1)
	{
		usleep(10);
		if (action(data, global_d))
			break ;
	}
	(void)action;
	pthread_exit(NULL);
}
