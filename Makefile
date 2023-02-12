NAME		:= cub3D
CFLAGS		:= -Wextra -Wall -Werror
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
LIBMLX		:= ./libs/MLX42/build/
LIBFT		:= ./libs/libft
MLXFLAGS	:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -g
INCLUDES	:= includes

HEADERS	:= $(addprefix -I , \
			  libft \
			  MLX42/include/MLX42 \
			  includes)
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

$(NAME): $(FUNCTIONS_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) $(MLXFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
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

rebug: fclean
	$(MAKE) debug


re: clean all

.PHONY: all, clean, fclean, re, libmlx
