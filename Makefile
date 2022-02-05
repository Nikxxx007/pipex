CC		= gcc
NAME	= pipex
SRCS	= src/main.c \
          				src/execution.c \
          				src/get_next_line.c \
          				src/util.c

OBJS		= $(SRCS:.c=.o)

SRCS_BONUS	= src_bonus/main_bonus.c \
				src_bonus/execution_bonus.c \
				src_bonus/get_next_line_bonus.c \
				src_bonus/util_bonus.c

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

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

all:	$(NAME) bonus

bonus:	$(NAME) $(OBJS_BONUS)
	make bonus -C libft
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS_BONUS) -o pipex_bonus

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)
		make clean -C libft

fclean:	clean
		$(RM) $(NAME)
		$(RM) pipex_bonus
		make fclean -C libft

re:		fclean all

.PHONY:	fclean clean re bonus
