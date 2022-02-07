#include "philo.h"

void	ft_sleep(unsigned long time)
{
	unsigned long	current_time;

	current_time = get_time();
	while (get_time() - current_time < time)
		usleep(500);
}

int	init_struct_data(t_data *data, int argc, char **argv)
{
	data->count = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_number = ft_atoi(argv[5]);
	else
		data->eat_number = -1;
	if (data->count <= 0 || data->die <= 0 || data->eat <= 0 \
		|| data->sleep <= 0 || data->eat_number == 0)
		return (0);
	return (1);
}

void	init_struct_ph(t_ph *ph, t_data *data, t_status *status)
{
	int		i;

	i = 0;
	if (i == 0)
		pthread_mutex_init(&ph[0].r_fork, NULL);
	while (i < data->count)
	{
		ph[i].numb = i + 1;
		if (i != 0)
		{
			pthread_mutex_init(&ph[i].r_fork, NULL);
			ph[i].l_fork = &ph[i - 1].r_fork;
		}
		ph[i].data = data;
		ph[i].status = status;
		ph[i].start = get_time();
		ph[i].eat = 0;
		ph[i].last_eat_time = get_time();
		i++;
	}
	ph[0].l_fork = &ph[i - 1].r_fork;
}

void	init_struct_status(t_status *status)
{
	status->death = 0;
	pthread_mutex_init(&status->print, NULL);
	status->eaten_ph = 0;
	pthread_mutex_init(&status->time, NULL);
}
