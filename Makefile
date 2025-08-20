CC := cc
CFLAGS := -Wextra -Wall -Werror
RLFLAG := -lreadline

# Directories

SRCS  := minishell.c \
		 parsing/tokenizers.c \
		 parsing/tokenizers2.c \
		 parsing/check_syntax.c \
		 parsing/signals.c \
		 parsing/expand_envv.c \
		 parsing/expend_help.c \
		 parsing/env.c \
		 parsing/parsing.c \
		 parsing/parsing_utils.c \
		 parsing/args_inserter.c \
		 parsing/free_memory.c \
		 builtins/export.c \
		 builtins/export_helpers.c \
		 builtins/export_helpers1.c \
		 builtins/builtins_utils.c \
		 builtins/export_helpers2.c \
		 builtins/cd_and_pwd.c \
		 builtins/unset.c \
		 builtins/echo.c \
		 builtins/exit.c \
		 utils/ft_lstadd_back.c \
		 utils/ft_lstclear.c \
		 utils/ft_lstlast.c \
		 utils/ft_lstnew.c \
		 utils/ft_strlen.c \
		 utils/ft_strdup.c \
		 utils/ft_strchr.c \
		 utils/ft_strcmp.c \
		 utils/ft_split.c \
		 utils/ft_substr.c \
		 utils/ft_strjoin.c \
		 utils/ft_dprintf.c \
		 utils/ft_print_format.c \
		 utils/ft_putaddr.c \
		 utils/ft_putchar.c \
		 utils/ft_puthexa.c \
		 utils/ft_putnbr.c \
		 utils/ft_putnbr_u.c \
		 utils/ft_putstr.c \
		 utils/ft_itoa.c \
		 utils/ft_atoi.c \
		 utils/ft_lstsize.c \
		 utils/ft_swap_export.c \
		 utils/ft_check_space.c \
		 utils/ft_strncmp.c \
		 utils/ft_strnstr.c \
		 utils/ft_strtrim.c \
		 utils/ft_calloc.c \
		 execute/execution.c \
		 execute/execution2.c \
		 execute/dup_helper.c \
		 execute/handel_env.c \
		 execute/heredoc.c \
		 execute/multi_cmd.c \
		 execute/retrieve_path.c \
		 execute/retrive_path_help.c \
		 execute/exe_utils.c \
		 execute/wild_card.c \
		 execute/wild_card2.c \
		 execute/norm_help.c \


OBJS	:=	${SRCS:.c=.o}

NAME	:= minishell

RM		:= rm -f

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJS} ${UTILS}
	$(CC) $(CFLAGS) $^ -o ${NAME} ${RLFLAG}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all