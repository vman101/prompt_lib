# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarama <anarama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 12:24:47 by victor            #+#    #+#              #
#    Updated: 2024/11/10 19:26:39 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# COMPILER AND FLAGS
CC          := cc
CFLAGS      := -Werror -Wall -Wextra

ifdef DEBUG
	CFLAGS += -g3
endif

# DIRECTORIES
SRCDIR      := src
OBJDIR      := obj

# SOURCES AND OBJECTS
SRC         :=	prompt_input.c prompt_string_management.c \
              	prompt_utils.c tab_completion.c \
              	escape_sequences.c arrowkeys.c \
              	prompt_print.c tab_get_word.c \
              	non_blocking_mode.c prompt_handle_chars.c \
				ft_putstr_fd.c utils.c ft_read.c

OBJ         := $(SRC:%.c=$(OBJDIR)/%.o)
SRCS        := $(addprefix $(SRCDIR)/, $(SRC))

# TARGETS
MEMORY      := memory/lib/memory.a
PRINTF		:= printf/lib/libftprintf.a

LIBS := $(MEMORY) $(PRINTF)
LIBDIR := lib
NAME        := $(LIBDIR)/prompt.a

all: $(NAME)

$(NAME): $(OBJ) | $(LIBS)
	ar rcs $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR): $(LIBDIR)
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

$(LIBS):
	make -C memory
	make -C printf

clean:
	make fclean -C memory
	make fclean -C printf
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
