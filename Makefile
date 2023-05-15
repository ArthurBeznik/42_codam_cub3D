
NAME		:= cub3D

RED 		:=	\033[1;31m
GRN 		:=	\033[1;32m
BLUE		:=	\033[1;36m
YEL 		:=	\033[0;33m
DEF 		:=	\033[0m

CFLAGS		:= -Wextra -Wall -Werror -g3 -Wunreachable-code -Ofast
# CFLAGS		:= -g3
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
USERNAME	:= $(shell whoami)
MLXFLAGS	:= 
ifeq ($(USERNAME), "abeznik")
	MLXFLAGS := -Iinclude -lglfw -L"/Users/abeznik/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit
else
	MLXFLAGS	:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

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

SCENE_DIR	:= scenes
SUBJ_MAP	:= $(SCENE_DIR)/valid/minimalist.cub
SIMPLE_MAP	:= $(SCENE_DIR)/valid/simple_valid.cub
SQUARE_MAP	:= $(SCENE_DIR)/valid/square_8.cub
DB_MAP		:= $(SCENE_DIR)/valid/square_8.cub
INVAL_MAP	:= $(SCENE_DIR)/invalid/invalid_colors.cub

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
	@printf "$(YEL)Compiling: $(notdir $<)$(DEF)\n"

$(NAME): $(OBJS)
	@echo "\n$(GRN)================ CUB3D ================$(DEF)"
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) $(MLXFLAGS) $(HEADERS) -o $(NAME)

#
# Subject rules
#
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBMLX)/build clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a

re: clean all

.PHONY: all clean fclean re libmlx libft

#
# Norm rule
#
norm:
	norminette srcs includes

#
# Debug rules
#
fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug

db: $(NAME)
	lldb cub3D -- $(DB_MAP)

#
# Testing rules
#
subject: all
	./$(NAME) $(SUBJ_MAP)

simple: all
	./$(NAME) $(SIMPLE_MAP)

square:	all
	./$(NAME) $(SQUARE_MAP)

test:
	./testing.sh
