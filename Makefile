CC		= gcc
NAME	= pipex
SRCS	= src/main_utils.c \
          src/main.c

OBJS		= $(SRCS:.c=.o)

FLAGS	= -Wall -Wextra -Werror
LIBC	= ar rc
LIBR	= ranlib
RM		= rm -f
INCL	= ./

LIBFT	= libft/libft.a

.c.o:
	$(CC) $(FLAGS) -I includes -c $< -o $(<:.c=.o)


$(NAME): 	$(OBJS)
	make bonus -C libft
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)
		make clean -C libft
fclean:	clean
		$(RM) $(NAME)
		make fclean -C libft

re:		fclean all

.PHONY:	fclean clean re bonus
