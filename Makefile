NAME		:= cub3d
CFLAGS		:= -Wextra -Wall -Werror
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
LIBMLX		:= ./lib/MLX
LIBFT		:= ./lib/libft
MLXFLAGS:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -g

HEADERS	:= $(addprefix -I , \
			  libft \
			  MLX/include/MLX42)
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/libmlx42.a
SRCS	:= $(shell find ./srcs -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

FUNCTIONS_OBJ=$(OBJS:.c=.o)

all: libmlx libft $(NAME)

libmlx:
	@echo ======== MLX42 ========
	@$(MAKE) -C $(LIBMLX)

libft:
	@echo ======== LIBFT ========
	@$(MAKE) -C $(LIBFT)


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(FUNCTIONS_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) $(MLXFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f ./lib/libft/libft.a

fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug


re: clean all

.PHONY: all, clean, fclean, re, libmlx
