
NAME		:= cub3D

RED 		:=	\033[1;31m
GRN 		:=	\033[1;32m
BLUE		:=	\033[1;36m
YEL 		:=	\033[0;33m
DEF 		:=	\033[0m

# CFLAGS		:= -Wextra -Wall -Wunreachable-code -Ofast -g3 #-Werror
CFLAGS		:= -g3 
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
MLXFLAGS	:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

LIBMLX		:= ./libs/MLX42
LIBFT		:= ./libs/libft
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a

HEADERS		:= $(addprefix -I , \
			  ./libs/libft \
			  ./libs/MLX42/include/MLX42 \
			  ./includes)

OBJ_DIR		:= objs
SRC_DIR		:= srcs

SRCS		:= $(shell find srcs -iname "*.c")
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# DB_MAP		:= scenes/moore.cub
DB_MAP		:= scenes/minimalist.cub
TEST_MAP	:= scenes/minimalist.cub

all: libmlx libft $(NAME)

libmlx:
	@echo "$(GRN)================ MLX42 ================$(DEF)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@echo "\n$(GRN)================ LIBFT ================$(DEF)"
	@$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $< $(HEADERS)
	@printf "$(YEL)Compiling: $(notdir $<)$(DEF)\n\t"

$(NAME): $(OBJS)
	@echo "\n$(GRN)================ CUB3D ================$(DEF)"
	$(CC) $(OBJS) $(LIBS) $(MLXFLAGS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBMLX)/build clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a

fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

db: $(NAME)
	lldb cub3D -- $(DB_MAP)

run: re
	./cub3D $(TEST_MAP)

rebug: fclean
	$(MAKE) debug

re: clean all

.PHONY: all clean fclean re libmlx libft
