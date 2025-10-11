# **************************************************************************** #
#                                                                              #
#   File:       Makefile                                                       #
#   Purpose:    Main compilation file of the program                           #
#   Author:     barlukh (Boris Gazur)                                          #
#   Updated:    2025/10/10                                                     #
#                                                                              #
# **************************************************************************** #

NAME	=	raycasting

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -O2 -std=c17
LFLAGS	=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
RM		=	rm -rf

DIR_LIB	=	lib
DIR_HDR	=	include
DIR_OBJ	=	objects
DIR_SRC	=	src

HDR		=	$(wildcard $(DIR_HDR)/*.h)
SRC		=	$(shell find $(DIR_SRC) -name "*.c")
OBJ		=	$(subst $(DIR_SRC)/,$(DIR_OBJ)/,$(SRC:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(DIR_LIB) $(LFLAGS)
	@echo "✅ Compilation successful"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for object files"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(DIR_HDR) -c $< -o $@

clean:
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"

fclean:
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"
	@$(RM) $(NAME)
	@echo "🧹 Executable removed"

re: fclean all

.PHONY: all clean fclean re
