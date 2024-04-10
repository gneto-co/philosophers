/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:36 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:25 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av) 
{
	// declarations
	t_global_data	global_d;
	t_data			*data;
	t_wall_e_data	wall_e_data;
	pthread_t		*threads;
	pthread_t		wall_e_thread;
	int i;

	// args protection
	if (ac != 5 && ac != 6)
		return (ft_error(1));

	/* ---------------------------------------- */
	/* ------------ INITIALIZE VARS ----------- */
	/* ---------------------------------------- */

	if (global_declarations(&global_d, ac, av))
		return (1);

	data_allocation(&data, &global_d, &threads);

	mutex_declarations(&global_d);

	// lock mutex to wait for all threads
	pthread_mutex_lock(&(global_d.run1_mutex));

	/* ---------------------------------------- */
	/* ------------- THREADS CODE ------------- */
	/* ---------------------------------------- */
	
	// create philosopher threads
	create_philo(&data, &global_d, &threads);

	// create wall_e thread
	wall_e_data.global_d = &global_d;
	wall_e_data.data = &data;
	pthread_create(&wall_e_thread, NULL, wall_e_process, (void *)&(wall_e_data));
	pthread_detach(wall_e_thread);
	
	// get star time
	global_d.start_time = ft_get_time();
	// unlock mutex to start threads at the same time
	pthread_mutex_unlock(&(global_d.run1_mutex));
	// print conference start
	pthread_mutex_lock(&(global_d.write_mutex));
	ft_color(4);
	ft_printf("\nPhilosophers start their conference\n\n");
	ft_color(0);
	pthread_mutex_unlock(&(global_d.write_mutex));
	

	// wait for threads to end their process
	i = 0;
	while (i < global_d.philo_amount) 
		pthread_join(threads[i++], NULL);

	/* ---------------------------------------- */
	/* ------------------ END ----------------- */
	/* ---------------------------------------- */

	// print conference end
	pthread_mutex_lock(&(global_d.write_mutex));
	ft_color(4);
	printf("\n\nPhilosophers end their conference\n");
	ft_color(0);
	pthread_mutex_unlock(&(global_d.write_mutex));
	
	// destroy mutex
	pthread_mutex_destroy(&(global_d.write_mutex));
	pthread_mutex_destroy(&(global_d.run1_mutex));
	
	// free vars
	free(data);
	free(threads);
	free(global_d.forks_mutex);

	return 0;
}
