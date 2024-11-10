# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victor </var/spool/mail/victor>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 09:21:46 by victor            #+#    #+#              #
#    Updated: 2024/11/10 18:12:24 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBDIR := lib
NAME := $(LIBDIR)/libftprintf.a
CC := cc
CFLAGS := -Wall -Werror -Wextra
SRC := ft_fprintf.c ft_printf.c ft_putascii.c ft_puthex.c ft_putptr.c ft_strlen.c ft_putfloat.c
OBJ := $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	ar rsc $@ $(OBJ)

$(OBJ): $(SRC) $(LIBDIR)
	$(CC) $(CFLAGS) -c $(SRC)

$(LIBDIR):
	mkdir $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
