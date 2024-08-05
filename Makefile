NAME	= cub3d

RM		= rm -f

SRC		= cub3d.c get_next_line.c\

CFLAGS	= -fsanitize=address -g3 #-Wall -Wextra -Werror

OBJ		= $(SRC:.c=.o)

CC		= cc

all		: $(NAME)
			
%.o		: %.c cub3d.h Makefile
			cc $(CFLAGS) -c $<  -o $@
$(NAME)	: $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) -o $@
clean	: 
			$(RM) $(OBJ)

fclean	: clean
			$(RM) $(NAME)


