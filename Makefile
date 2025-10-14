# **************************************************************************** #
#                                                                              #
#   File:       Makefile                                                       #
#   Purpose:    Main compilation file of the program                           #
#   Author:     barlukh (Boris Gazur)                                          #
#   Updated:    2025/10/13                                                     #
#                                                                              #
# **************************************************************************** #

NAME	=	raycasting

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -O2 -std=c17
LFLAGS	=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
RM		=	rm -rf
FLAGS	=	--show-leak-kinds=all \
			--show-reachable=yes \
			--leak-check=full \
			--track-origins=yes \
			--undef-value-errors=yes \
			--track-fds=yes \
			--suppressions=vg.supp

DIR_LIB	=	lib
DIR_HDR	=	include
DIR_OBJ	=	objects
DIR_SRC	=	src

HDR		=	$(wildcard $(DIR_HDR)/*.h)
OBJ		=	$(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o,$(SRC))
SRC		=	$(shell find $(DIR_SRC) -name "*.c")

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(DIR_LIB) $(LFLAGS)
	@echo "✅ Compilation successful"

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	@echo "📁 Created directory for object files"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR) | prepare_dirs
	$(CC) $(CFLAGS) -I $(DIR_HDR) -c $< -o $@

clean:
	$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"

fclean:
	$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"
	$(RM) $(NAME)
	@echo "🧹 Executable removed"

prepare_dirs:
	mkdir -p $(sort $(dir $(OBJ)))

re: fclean all

run: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	valgrind $(FLAGS) ./$(NAME)

.PHONY: all clean fclean prepare_dirs re run valgrind
