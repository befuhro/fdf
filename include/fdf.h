#include <fcntl.h>

# define BUFF_SIZE 16000

typedef struct	s_coord
{
	int x;
	int y;
	int z;
}		t_coord;

typedef  struct	s_whole
{
	void	*init;
	void	*win;
	int latitude;
	int height;
	int width;
	char *buff;
	t_coord **matrix;
}		t_whole;
