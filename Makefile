# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarama <anarama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 12:24:47 by victor            #+#    #+#              #
#    Updated: 2024/11/11 12:55:00 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILER AND FLAGS
CC          := gcc
CFLAGS      = -Werror -Wall -Wextra -g3

RM			= rm

ifdef release
	CFLAGS -= -g3
endif


MKDIR = mkdir

ifeq ($(OS), Windows_NT)
RM = del /S /Q
else
RM = rm -rf
MKDIR += -p
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
				ft_putstr_fd.c utils.c ft_read.c terminal.c

OBJ         := $(SRC:%.c=$(OBJDIR)/%.o)
SRCS        := $(addprefix $(SRCDIR)/, $(SRC))

# TARGETS
MEMORY      := memory/lib/memory.a
PRINTF		:= printf/lib/libftprintf.a

LIBS := $(MEMORY) $(PRINTF)
LIBDIR := lib
NAME        := $(LIBDIR)/prompt.a

all: $(NAME)

test: $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) $(LIBS)

$(NAME): $(OBJ) prompt.h | $(LIBS)
	ar rcs $@ $(OBJ) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR): $(LIBDIR)
	$(MKDIR) $@

$(LIBDIR):
	$(MKDIR) $@

$(LIBS):
	make -C memory
	make -C printf

clean:
	make fclean -C memory
	make fclean -C printf
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(LIBDIR)

re: fclean all
