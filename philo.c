#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

void	*ph_solution(void *arg)
{
	t_ph		*ph;
	pthread_t	id;

	ph = (t_ph *)arg;
	pthread_create(&id, NULL, check_death, (void *)ph);
	if (ph->numb % 2 == 0)
		usleep(500);
	while (1)
	{
		philosophers_life(ph);
		if (ph->status->death == 1)
		{
			pthread_join(id, NULL);
			return (NULL);
		}
	}
	return (NULL);
}

int	start_stream(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->data->count)
	{
		if (ph->status->death == 1)
			break ;
		pthread_create(&ph[i].id, NULL, ph_solution, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < ph->data->count)
	{
		pthread_join(ph[i].id, NULL);
		i++;
	}
	return (1);
}

void	destroy_mutex(t_ph *ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&ph->status->print);
	while (i < ph->data->count)
	{
		pthread_mutex_destroy(&ph->r_fork);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_status	status;
	t_ph		*ph;
	int			i;

	i = 0;
	if (argc > 6)
		return (ft_putstr_fd("Error: too many arguments!\n", 2));
	if (argc < 5)
		return (ft_putstr_fd("Error: too few arguments!\n", 2));
	if (!check_arguments(argc, argv))
		return (ft_putstr_fd("Error: bad arguments!\n", 2));
	if (!init_struct_data(&data, argc, argv))
		return (ft_putstr_fd("Error: bad arguments!\n", 2));
	init_struct_status(&status);
	ph = (t_ph *)malloc(sizeof(t_ph) * data.count);
	if (!ph)
		return (ft_putstr_fd("Error: malloc\n", 2));
	memset(ph, 0, data.count);
	init_struct_ph(ph, &data, &status);
	start_stream(ph);
	destroy_mutex(ph);
	free(ph);
	ph = NULL;
	return (0);
}
