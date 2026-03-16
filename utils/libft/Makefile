# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 18:00:16 by mafzal            #+#    #+#              #
#    Updated: 2025/01/10 14:50:21 by mafzal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = \
        ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
        ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
        ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
        ft_memchr.c ft_memcmp.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_split.c \
        ft_strtrim.c ft_strdup.c ft_calloc.c ft_itoa.c ft_strmapi.c ft_putstr_fd.c \
        ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c

SRC_BONUS = \
        ft_lstnew.c \
        ft_lstadd_front.c \
        ft_lstlast.c \
        ft_lstsize.c \
        ft_lstadd_back.c \
        ft_lstdelone.c \
        ft_lstclear.c \
        ft_lstiter.c \
        ft_lstmap.c

OBJ        = $(SRC:.c=.o)
BONUS_OBJ  = $(SRC_BONUS:.c=.o)
NAME        = libft.a
RM          = rm -f
CC          = cc
AR          = ar -crs
CFLAGS      = -Wall -Wextra -Werror

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

bonus: $(OBJ) $(BONUS_OBJ)
	$(AR) $(NAME) $(OBJ) $(BONUS_OBJ)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus