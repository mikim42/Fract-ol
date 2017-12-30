# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/03 20:55:24 by mikim             #+#    #+#              #
#    Updated: 2017/12/29 18:19:04 by mikim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  fractol.c \
	  parse_handler.c \
	  color_handler.c \
	  mandelbrot.c \
	  hook_handler.c \
	  key_handler.c \
	  exit_handler.c

OBJ = $(SRC:.c=.o)
MLX = -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit

SRCDIR = srcs
OBJDIR = objs
LIBDIR = libs/libft
MLXDIR = libs/mlx

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
LIBS = -L $(LIBDIR) -lft $(MLX)
HEADER = -I includes -I $(LIBDIR)/includes -I $(MLXDIR)

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

NAME = fractol

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS) $(LIBS) -o $@
	@echo "\x1b[32;1m[fractol - 모래반지 빵야빵야!]\x1b[0m"

clean:
	@/bin/rm -rf $(OBJDIR)
	@make -C $(MLXDIR) clean
	@make -C $(LIBDIR) clean
	@echo "\x1b[35;1m[fractol - clean]\x1b[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@rm -f $(LIBDIR)/libft.a
	@echo "\x1b[31m[fractol - fclean]\x1b[0m"

re: fclean all
