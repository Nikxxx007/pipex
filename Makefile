CC		= gcc
NAME	= libftprintf.a
SRCS	= src/ft_printf.c \
          src/print/print_string.c \
          src/print/print_int.c \
          src/print/print_unsigned.c \
          src/utils/ft_putnbr_long_fd.c \
          src/print/print_hex.c \
          src/print/print_pointer.c \
          src/apply/apply_procent.c \
          src/parser/parse_procent.c \
          src/print/print_char.c \
          src/utils/parse_utils.c \
          src/utils/struct_init.c \

OBJS		= $(SRCS:.c=.o)

FLAGS	= -Wall -Wextra -Werror
LIBC	= ar rc
LIBR	= ranlib
RM		= rm -f
INCL	= ./

.c.o:
	$(CC) $(FLAGS) -I includes -c $< -o $(<:.c=.o)

$(NAME): 	$(OBJS)
	make bonus -C libft
	cp libft/libft.a ./$(NAME)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)
		make clean -C libft
fclean:	clean
		$(RM) $(NAME)
		make fclean -C libft

re:		fclean all

.PHONY:	fclean clean re bonus
