# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasson <marvin@42.ft>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:16:04 by lomasson          #+#    #+#              #
#    Updated: 2022/06/28 12:30:59 by lomasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_lib = libcustom.a

CC = gcc
AR = ar -rcs


CFLAGS_lib = -Wall -Werror -Wextra -I -c
CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = $(NAME_lib)


SRCS = srcs/main.c \
				srcs/pipe/pipe_utils.c \
				srcs/pipe/pipe.c

SRCS_libft = libft/ft_isdigit.c \
				libft/ft_isalnum.c \
				libft/ft_isascii.c \
				libft/ft_isprint.c \
				libft/ft_isalpha.c \
				libft/ft_strlen.c \
				libft/ft_memset.c \
				libft/ft_bzero.c \
				libft/ft_memcpy.c \
				libft/ft_memmove.c \
				libft/ft_strlcpy.c \
				libft/ft_strlcat.c \
				libft/ft_toupper.c \
				libft/ft_tolower.c \
				libft/ft_strchr.c \
				libft/ft_strrchr.c \
				libft/ft_strncmp.c \
				libft/ft_memchr.c \
				libft/ft_memcmp.c \
				libft/ft_strnstr.c \
				libft/ft_atoi.c \
				libft/ft_calloc.c \
				libft/ft_strdup.c \
				libft/ft_substr.c \
				libft/ft_strjoin.c \
				libft/ft_strtrim.c \
				libft/ft_split.c \
				libft/ft_itoa.c \
				libft/ft_putchar_fd.c \
				libft/ft_putstr_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_striteri.c \
				libft/ft_strmapi.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_putstr_fd.c \
				libft/get_next_line.c \
				libft/ft_printf_utils.c \
				libft/ft_printf.c



OBJS = $(SRCS:%.c=%.o)

OBJS_libft = $(SRCS_libft:%.c=%.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(CFLAGS)

libft: $(OBJS_libft)
	$(AR) $(NAME_lib) $(OBJS_libft)

lib_clean:
	rm -f $(OBJS_libft) && rm $(NAME_lib)

clean: lib_clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
