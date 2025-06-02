NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/builtins/builtins.c \
		$(SRCS_DIR)/builtins/echo.c \
		$(SRCS_DIR)/builtins/cd.c \
		$(SRCS_DIR)/builtins/pwd.c \
		$(SRCS_DIR)/builtins/get_fd.c \
		$(SRCS_DIR)/builtins/exit.c \
		$(SRCS_DIR)/builtins/env.c \
		$(SRCS_DIR)/builtins/export.c \
		$(SRCS_DIR)/builtins/export_utils.c \
		$(SRCS_DIR)/builtins/unset.c \
		$(SRCS_DIR)/printr/ft_conversions.c \
		$(SRCS_DIR)/printr/ft_itoa.c \
		$(SRCS_DIR)/printr/printr.c \
		$(SRCS_DIR)/printr/ft_puthex.c \
		$(SRCS_DIR)/parsing/ft_syntax.c \
		$(SRCS_DIR)/parsing/parsing_bis.c \
		$(SRCS_DIR)/parsing/parsing_bibis.c \
		$(SRCS_DIR)/parsing/parsing.c \
		$(SRCS_DIR)/parsing/utils.c \
		$(SRCS_DIR)/parsing/utils_bis.c \
		$(SRCS_DIR)/parsing/open_fd.c \
		$(SRCS_DIR)/exec/fork.c \
		$(SRCS_DIR)/exec/exec.c \
		$(SRCS_DIR)/exec/exec_args.c \
		$(SRCS_DIR)/utils/clean.c \
		$(SRCS_DIR)/utils/is_utils.c \
		$(SRCS_DIR)/utils/itoa.c \
		$(SRCS_DIR)/utils/utils_bis.c \
		$(SRCS_DIR)/utils/utils_lst.c \
		$(SRCS_DIR)/utils/utils_lst_bis.c \
		$(SRCS_DIR)/utils/utils_str.c \
		$(SRCS_DIR)/utils/utils.c \
		$(SRCS_DIR)/env/env_utils.c \
		$(SRCS_DIR)/heredoc.c \
		$(SRCS_DIR)/pipes.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/utils_bis.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/printr
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/parsing
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/exec
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/env

	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re