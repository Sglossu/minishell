NAME		=	minishell

DIR			=	./srcs/
DIR_HEAD	=	./includes/
DIR_BUILD	=	./buildins/
DIR_UTILS	=	./utils/
DIR_SRCS	=	./srcs/
DIR_PIPE	=	./pipe/
DIR_PARSE	=	./parse/
DIR_SIGNAL	=	./signal/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I ~/.brew/opt/readline/include/
RM			=	rm -f

SRCS		=	main.c \
				\
				$(DIR_BUILD)ft_pwd.c			$(DIR_BUILD)ft_cd.c				$(DIR_BUILD)ft_echo.c \
				$(DIR_BUILD)ft_env.c			$(DIR_BUILD)ft_unset.c			$(DIR_BUILD)ft_export.c \
				$(DIR_BUILD)ft_exit.c \
				\
				$(DIR_UTILS)ft_sort_params.c	$(DIR_UTILS)about_memory.c		$(DIR_UTILS)find.c\
				$(DIR_UTILS)free.c \
				\
				$(DIR_SRCS)init.c				$(DIR_SRCS)main_work.c			$(DIR_SRCS)command_exist.c \
				$(DIR_SRCS)one_direct.c \
				\
				$(DIR_PIPE)pipe_main.c			$(DIR_PIPE)pipe_for_two.c			$(DIR_PIPE)functions_for_direct.c \
				\
				$(DIR_PARSE)parser.c			$(DIR_PARSE)parser_utils.c		$(DIR_PARSE)lists.c \
				$(DIR_PARSE)cmd_parse.c\
				\
				$(DIR_SIGNAL)signal_for_main.c	$(DIR_SIGNAL)signal_for_child.c

OBJS		=	$(SRCS:.c=.o)
HEAD		=	$(DIR_HEAD)minishell.h

LIB			=	./libft/libft.a
HEAD_LIB	=	./libft/libft.h

LIB_PRINT	=	./printf/libftprintf.a
HEAD_LIB_PRINT	=	./printf/ft_printf.h

RDL_MAC		= 	-lreadline -L ~/.brew/opt/readline/lib

.PHONY		:	all clean fclean re

all			:	$(NAME)

.c.o		:
				$(CC) $(CFLAGS) -c -I$(DIR_HEAD) $< -o $(<:.c=.o)

$(NAME)		:	$(OBJS) $(HEAD) $(HEAD_LIB) $(HEAD_LIB_PRINT)
				$(MAKE) -C libft
				$(MAKE) -C printf
				$(CC) -g $(CFLAGS) -Llibft -Lprintf -lft -I$(DIR_HEAD) $(OBJS) $(LIB) $(LIB_PRINT) -o $(NAME) $(RDL_MAC)

clean		:
				$(MAKE) clean -C ./libft/
				$(MAKE) clean -C ./printf/
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean		:	clean
				$(MAKE) fclean -C ./libft/
				$(MAKE) fclean -C ./printf/
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean all
				@echo "\033[35;1m\nRemake done\n\033[0m"
