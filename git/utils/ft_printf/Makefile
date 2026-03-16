CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

NAME = ft_printf.a
SRCS = 	ft_helperf.c  ft_ifelse.c  ft_numbers.c  ft_printf.c\
	ft_hex.c ft_letters.c ft_pointer.c
OBJS = ${SRCS:.c=.o}
HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
