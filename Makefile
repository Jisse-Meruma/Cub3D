### VAR #######################################################
NAME		:=	cub3d

DEBUGGING	?=

LIBS		:=	./libft/libft.a
MLX			?=	./MLX42
MLXLIB		:= $(MLX)/build/libmlx42.a
HEADER		:=	-Ilibft -Iinclude -I$(MLX)/include/MLX42

HEADERS		:=	libft/libft.h include/cub3d.h include/struct.h $(MLX)/include/MLX42/MLX42.h
OBJ_DIR		:=	obj
SRC_DIR 	:=	src

### UTILS #####################################################
CFLAGS	:=	-Wall -Wextra 
RM		:=	rm -rf

SRC 	:=	main.c \
			parser/parser.c \
			parser/map_validate.c

OBJ		:=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
SRC		:=	$(addprefix $(SRC_DIR)/,$(SRC))

## BON_SRC :=

## BON_OBJ :=  $(BON_SRC:_bonus.c=_bonus.o)

## Regular Colors ##############################################
Color_Off	=	"\033[0m"			# Text Reset
Black		=	"\033[0;30m"		# Black
Red			=	"\033[0;31m"		# Red
Green		=	"\033[0;32m"		# Green
Yellow		=	"\033[0;33m"		# Yellow
Blue		=	"\033[0;34m"		# Blue
Purple		=	"\033[0;35m"		# Purple
Cyan		=	"\033[0;36m"		# Cyan
White		=	"\033[0;37m"		# White

### EXEC #######################################################

ifdef DEBUG
	MLXLIB += -fsanitize=address -g
	DEBUGGING += DEBUG=1
endif

ifdef LINUX
	MLXLIB += -lglfw -ldl -pthread -lm
endif

ifndef LINUX 
	MLXLIB += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit 
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@echo -----------------------
	@$(CC) $^ $(LIBS) $(MLXLIB) -o $(NAME) 
	@echo $(Green) Complete ✅ $(Color_Off)
	@echo -----------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@echo -----------------------
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(LIBS):
	@$(MAKE) -C libft bonus

mlx:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build

clean:
	@echo $(Cyan) Sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft clean
	@$(RM) $(OBJ) $(BON_OBJ)

fclean:
	@echo $(Red) Thorough sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(RM) $(NAME) $(OBJ_DIR) $(BON_OBJ)

re: fclean all

rere: depclean fclean mlx all
	
depclean:
	@$(MAKE) -C libft fclean
	@$(RM) $(MLX)/build

cc:
	@make -n | compiledb

clean_cc:
	@$(RM) compile_commands.json

debug:
	@make DEBUG=1

.PHONY: clean all fclean re libmlx depclean rere cc clean_cc debug
