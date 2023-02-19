# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/14 10:25:24 by abeznik       #+#    #+#                  #
#    Updated: 2023/02/19 13:15:54 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

RED 		:=	\033[1;31m
GRN 		:=	\033[1;32m
BLUE		:=	\033[1;36m
YEL 		:=	\033[0;33m
DEF 		:=	\033[0m

CFLAGS		:= -Wextra -Wall -Wunreachable-code -Ofast -g3 #-Werror
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
MLXFLAGS	:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -g

LIBMLX		:= ./libs/MLX42
LIBFT		:= ./libs/libft
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a

HEADERS		:= $(addprefix -I , \
			  ./libs/libft \
			  ./libs/MLX42/include/MLX42 \
			  ./includes)

SRCS		:= $(shell find ./srcs -iname "*.c")
OBJS		:= ${SRCS:.c=.o}

DB_MAP		:= scenes/minimalist.cub
TEST_MAP	:= scenes/minimalist.cub

all: libmlx libft $(NAME)

libmlx:
	@echo "\n$(GRN)================ MLX42 ================$(DEF)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@echo "\n$(GRN)================ LIBFT ================$(DEF)"
	@$(MAKE) -C $(LIBFT)

%.o: %.c
	@echo "\n$(GRN)================ CUB3D ================$(DEF)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(MLXFLAGS) && printf "$(YEL)Compiling: $(notdir $<)$(DEF)\n\t"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX)/build clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f ./libs/libft/libft.a

fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

db: $(NAME)
	lldb cub3D -- $(DB_MAP)

run: $(NAME)
	./cub3D $(TEST_MAP)

rebug: fclean
	$(MAKE) debug

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
