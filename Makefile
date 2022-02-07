NAME =		philo
SRCS =		./init.c \
			./mutex.c \
			./philo.c \
			./utils.c \

HEADER =	./philo.h	
OBJS =		$(SRCS:.c=.o)

%.o:		%.c $(HEADER)
			${CC}   -c $< -o ${<:.c=.o}

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -pthread
OPTFLAGS =  -O2
RM =		rm -f

all :		${NAME}

$(NAME) :	$(OBJS) 
			$(CC) $(CFLAGS) $(OPTFLAGS) -o ${NAME} $(OBJS) -I$(HEADER)

clean :		
			$(RM) $(OBJS)

fclean 	:	clean
			$(RM) ${NAME}

re :		fclean all

.PHONY :	all clean fclean re 
