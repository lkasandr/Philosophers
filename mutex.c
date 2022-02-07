#include "philo.h"

static int	check_time(t_ph *ph, unsigned long time)
{
	if ((time - ph->last_eat_time) >= ph->data->die)
	{
		if (ph->status->death == 0)
			printf("%ld %d died\n", time - ph->start, ph->numb);
		ph->status->death = 1;
		pthread_mutex_unlock(&ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		pthread_mutex_unlock(&ph->status->print);
		return (0);
	}
	return (1);
}

void	*check_death(void *arg)
{
	t_ph	*ph;
	long	time;

	ph = (t_ph *)arg;
	time = 0;
	while (1)
	{	
		pthread_mutex_lock(&ph->status->print);
		time = get_time();
		if (!check_time(ph, time))
			return (NULL);
		pthread_mutex_unlock(&ph->status->print);
		if (ph->status->death == 1)
			return (NULL);
		usleep(100);
	}
}

void	message_print(t_ph *ph, char *str)
{
	unsigned long	time;

	time = get_time();
	pthread_mutex_lock(&ph->status->print);
	if (ph->status->death == 0)
		printf("%ld %d %s\n", time - ph->start, ph->numb, str);
	pthread_mutex_unlock(&ph->status->print);
}

static int	check_eaten_philo(t_ph *ph)
{
	if (ph->data->eat_number != -1)
	{
		if (ph->eat == ph->data->eat_number)
		{
			ph->status->eaten_ph++;
			if (ph->status->eaten_ph == ph->data->count)
			{
				ph->status->death = 1;
				return (0);
			}
		}
	}
	return (1);
}

void	*philosophers_life(t_ph *ph)
{
	if (pthread_mutex_lock(ph->l_fork) == 0)
	{
		message_print(ph, "has taken a fork");
		if (pthread_mutex_lock(&ph->r_fork) == 0)
		{
			message_print(ph, "has taken a fork");
			pthread_mutex_lock(&ph->status->print);
			ph->last_eat_time = get_time();
			pthread_mutex_unlock(&ph->status->print);
			message_print(ph, "is eating");
			ph->eat++;
			if (!check_eaten_philo(ph))
				return (NULL);
			ft_sleep(ph->data->eat);
			pthread_mutex_unlock(ph->l_fork);
			pthread_mutex_unlock(&ph->r_fork);
			message_print(ph, "is sleeping");
			ft_sleep(ph->data->sleep);
			message_print(ph, "is thinking");
		}
		else
			pthread_mutex_unlock(ph->l_fork);
	}
	return (NULL);
}
