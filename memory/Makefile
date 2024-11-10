# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:02:31 by vvobis            #+#    #+#              #
#    Updated: 2024/11/10 15:35:16 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

CFLAGS := -Werror -Wextra -Wall

SRC := memory.c list.c ft_free.c

OBJDIR := obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

LIBDIR := lib
TARGET := $(LIBDIR)/memory.a

all: $(TARGET)

$(TARGET): $(OBJ) | $(LIBDIR)
	ar rcs $@ $(OBJ)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR): $(OBJDIR)
	mkdir $(LIBDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
