# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2021/05/16 03:27:59 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

CC = gcc

HEADERS_PATH = ./includes/

INCLUDES = -I$(HEADERS_PATH) 

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

DIR = $(shell pwd)

DIRSRC = src

MLX_OPENGL_PATH = ./minilibx_opengl
MLX_LINUX_PATH = ./minilibx_linux
MLX_WINDOWS_PATH = ./minilibx_windows

MLX_PATH = 

FRAMEWORKS = 

LINKS = 

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	MLX_PATH = $(MLX_OPENGL_PATH)
	MLX_NAME = libmlx.dylib
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L$(MLX_PATH)/
	FRAMEWORKS += -framework OpenGL -framework Appkit
	INCLUDES += -I$(MLX_OPENGL_PATH)
	LOAD_DYLIB = install_name_tool -change $(MLX_NAME) $(DIR)/$(MLX_LIB) $(NAME)
endif

ifeq ($(UNAME),Linux)
	MLX_PATH = $(MLX_LINUX_PATH)
	MLX_NAME = libmlx.a
	INCLUDES += -I$(MLX_LINUX_PATH)
	LINKS += -L$(MLX_PATH) -lXext -lX11 -lxcb -lXau -lXdmcp -lm
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
endif

ifeq ($(OS),Windows_NT)
	MLX_PATH = $(MLX_WINDOWS_PATH)
	MLX_NAME = libmlx.a
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L"$(MLX_PATH)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image \
	-lSDL2_mixer -lSDL2_ttf  -lmingw32 -lSDL2main -luser32 -lgdi32 -lwinmm -ldxguid
	INCLUDES += -I$(MLX_WINDOWS_PATH)/includes
	LOAD_DYLIB = cp $(MLX_PATH)/*.dll ../
endif

SRC = $(addprefix $(DIRSRC)/, \
			main.c events.c graphic_utils.c math.c\
)

OBJDIR = obj

OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)

OBJ_PATHS = $(OBJDIR) $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

HEADERS = $(addprefix $(HEADERS_PATH), \
minirt.h )

OBJBONUS = $(SRCBONUS:.c=.o)

all: $(NAME) $(HEADERS)

$(NAME): $(MLX_LIB) $(OBJ)
	@echo COMPILING $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ)  $(MLX_LIB) -o $(NAME) $(LINKS) $(FRAMEWORKS)
	$(LOAD_DYLIB)


$(MLX_LIB):
	@echo "COMPILING MLX"
	$(MAKE) -C $(MLX_PATH)/

$(OBJDIR)/%.o: $(DIRSRC)/%.c $(HEADERS) $(MLX_LIB)
	@mkdir -p $(OBJ_PATHS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	$(MAKE) -C $(MLX_PATH) clean
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) ./*.dll

fclean: clean
	$(RM) $(NAME)

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME)

re: fclean all	

.PHONY: clean fclean

opti:
	$(eval CFLAGS += -O3)
	$(eval LIB_ARG += opti)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += debug)

QWERTY:
	$(eval CFLAGS += -D QWERTY=1)
