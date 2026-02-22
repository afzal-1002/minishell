NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

OBJ_DIR = objs

INCLUDES = -Isrc/includes \
		   -Iutils/libft \
		   -Iutils/ft_printf/includes

LDLIBS = -lreadline

LIBFT_DIR = utils/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = utils/ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/ft_printf.a

SRC = \
	src/main.c \
	src/init/init_shell.c \
	src/init/setup.c \
	src/cmd/add_arg.c \
	src/cmd/create_cmd.c \
	src/cmd/free_cmd.c \
	src/parser/parse_token.c \
	src/parser/create_redir.c \
	src/parser/redir_add_back.c \
	src/parser/redir_new.c \
	src/token/add_token_back.c \
	src/token/free_tokens.c \
	src/token/get_operator_type.c \
	src/token/get_type_name.c \
	src/token/handle_operator.c \
	src/token/handle_word.c \
	src/token/is_operator.c \
	src/token/new_token.c \
	src/token/print_tokens.c \
	src/token/skip_spaces.c \
	src/token/tokenizer.c \
	src/parser/handle_redirection.c \
    src/parser/handle_pipe.c \
    src/parser/is_redirection.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# ------------------------------
# Rules
# ------------------------------

all: libs $(NAME)

libs:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) \
	$(LIBFT_LIB) \
	$(FT_PRINTF_LIB) \
	$(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(FT_PRINTF_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libs