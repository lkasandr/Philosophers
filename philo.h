#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	count;
	int	die;
	int	eat;
	int	sleep;
	int	eat_number;
}				t_data;

typedef struct s_status
{
	int				death;
	int				eaten_ph;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
}				t_status;

typedef struct s_ph
{
	int				numb;
	int				eat;
	unsigned long	last_eat_time;
	unsigned long	start;
	pthread_t		id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	t_data			*data;
	t_status		*status;
}				t_ph;

int				ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *str);
int				check_arguments(int argc, char **argv);
int				init_struct_data(t_data *data, int argc, char **argv);
void			init_struct_ph(t_ph *ph, t_data *data, t_status *status);
void			init_struct_status(t_status *status);
unsigned long	get_time(void);
void			*check_death(void *arg);
void			message_print(t_ph *ph, char *str);
void			*philosophers_life(t_ph *ph);
void			destroy_mutex(t_ph *ph);
void			ft_sleep(unsigned long time);

#endif