/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:22:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/16 10:33:37 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	action(t_global_data *global_d, t_data **data)
{
	int	i;

	if (stop_check(global_d))
		return (1);
	i = 0;
	// loop all philo to see if they are dead
	while (i < global_d->philo_amount)
	{
		if (is_dead(&(*data)[i], global_d))
		{
			return (stop_set(global_d));
		}
		i++;
	}
	// see if are philo are fat
	if (are_all_fat(data, global_d))
		return (stop_set(global_d));	
	return (0);
}

void	*wall_e_process(void *original_data)
{
	t_wall_e_data	*wall_e_data;
	t_global_data	*global_d;
	t_data			**data;

	// declarations
	wall_e_data = (t_wall_e_data *)original_data;
	global_d = wall_e_data->global_d;
	data = wall_e_data->data;
	// wait for all
	ft_wait_for_all(global_d);
	// loop until break
	while (1)
	{
		usleep(DELAY);
		if (action(global_d, data))
			break ;
	}
	// end process
	pthread_exit(NULL);
}
