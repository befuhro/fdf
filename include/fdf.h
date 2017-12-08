#include <fcntl.h>

# define BUFF_SIZE 16000

typedef struct	s_coord
{
	int x;
	int y;
	int z;
}		t_coord;

typedef struct	s_mlx
{
	void	*init;
	void	*win;
}		t_mlx;

typedef  struct	s_whole
{
	int latitude;
	t_coord **matrix;
}		t_whole;
