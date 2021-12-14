NAME = libftprintf.a

SRCS =  ft_printf.c				parsing.c			init_struct.c \
		functions_strlen.c		for_char.c			functions_for_write.c \
		for_string.c			for_pointer.c		for_digit.c \
		for_unsigned.c			add_functions.c		functions_strlen.c \
		functions_atoi.c		for_hexadecimal.c	add_functions_2.c \
		add_functions_3.c

CC = gcc

FLAGS = -c -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

RM = rm -rf

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	${RM} $(SURPL_O) 
	${RM} $(OBJS)

fclean : clean
	${RM} $(NAME)

re : fclean all