# ifndef CUB3D_H
# define CUB3D_H

// #include <minilibx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# define BUFFER_SIZE 1024

char	*get_next_line(int fd);
size_t	ft_strlen(const char *theString);

typedef struct s_data
{
	char **map;
	char *R;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	char *F;
	char *C;
}   t_data;
#endif