
NAME	= cub3D

CC		= cc

RM		= rm -f

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BSRC:.c=.o)

SRC		= mandatory/cub3d.c mandatory/get_next_line.c mandatory/utils.c \
			mandatory/parse/map.c mandatory/parse/store_instructions.c mandatory/parse/store_map.c mandatory/parse/check_walls.c\


CFLAGS	= -Wall -Werror -Wextra

BNAME	= cub3D_bonus

LIBFT	= libft/libft.a

all: $(NAME)

bonus: $(BNAME)

mandatory/%.o: mandatory/%.c mandatory/cub3d.h libft/libft.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

bonus/%.o: bonus/%.c bonus/cub3d_b.h Makefile 
			$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -o $(NAME)


$(BNAME): $(BOBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -o $(BNAME)

$(LIBFT):
			make -C libft

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ) $(BOBJ)
	make -C libft/ clean

fclean: clean
	$(RM) $(NAME) $(BNAME)
	make -C libft/ fclean

re: fclean all
