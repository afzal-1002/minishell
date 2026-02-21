NAME = minishell
LIBFT = libft.a

RM = rm -f
CC = cc
AR = ar -crs
CFLAGS = -g -Wall -Wextra -Werror  
LDLIBS = -lreadline
OBJS_DIR = objs


LIBFT_SRC = \
	utils/libft/ft_atoi.c \
	utils/libft/ft_bzero.c \
	utils/libft/ft_calloc.c \
	utils/libft/ft_isalnum.c \
	utils/libft/ft_isalpha.c \
	utils/libft/ft_isascii.c \
	utils/libft/ft_isdigit.c \
	utils/libft/ft_isprint.c \
	utils/libft/ft_itoa.c \
	utils/libft/ft_lstadd_back.c \
	utils/libft/ft_lstadd_front.c \
	utils/libft/ft_lstclear.c \
	utils/libft/ft_lstdelone.c \
	utils/libft/ft_lstiter.c \
	utils/libft/ft_lstlast.c \
	utils/libft/ft_lstmap.c \
	utils/libft/ft_lstnew.c \
	utils/libft/ft_lstsize.c \
	utils/libft/ft_memchr.c \
	utils/libft/ft_memcmp.c \
	utils/libft/ft_memcpy.c \
	utils/libft/ft_memmove.c \
	utils/libft/ft_memset.c \
	utils/libft/ft_putchar_fd.c \
	utils/libft/ft_putendl_fd.c \
	utils/libft/ft_putnbr_fd.c \
	utils/libft/ft_putstr_fd.c \
	utils/libft/ft_split.c \
	utils/libft/ft_strchr.c \
	utils/libft/ft_strcmp.c \
	utils/libft/ft_strdup.c \
	utils/libft/ft_striteri.c \
	utils/libft/ft_strjoin.c \
	utils/libft/ft_strlcat.c \
	utils/libft/ft_strlcpy.c \
	utils/libft/ft_strlen.c \
	utils/libft/ft_strmapi.c \
	utils/libft/ft_strncmp.c \
	utils/libft/ft_strnstr.c \
	utils/libft/ft_strrchr.c \
	utils/libft/ft_strtrim.c \
	utils/libft/ft_substr.c \
	utils/libft/ft_tolower.c \
	utils/libft/ft_toupper.c

SRC = main.c \
	src/token/tokenizer.c \
	src/token/new_token.c \
	src/token/add_token_back.c \
	src/token/get_operator_type.c \
	src/token/free_tokens.c \
	src/token/handle_operator.c \
	src/token/handle_word.c \
	src/token/is_operator.c \
	src/token/skip_spaces.c \
	src/token/get_type_name.c \
	src/token/print_tokens.c \
	src/parser/parse_token.c \
	src/parser/create_cmd.c \
	src/parser/free_cmd.c \
	src/parser/add_arg.c

OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
OBJ = $(SRC:.c=.o)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)

$(LIBFT): $(LIBFT_OBJ)
	$(AR) $(LIBFT) $(LIBFT_OBJ)

clean:
	$(RM) $(OBJ) $(LIBFT_OBJ)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

