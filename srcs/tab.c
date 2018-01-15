#include <libft.h>
#include "fdf.h"
#include <mlx.h>
#include <stdio.h>

int		my_key_func(int keycode)
{
	if (keycode == 53 || keycode == 65307)
		exit(0);
	printf("keycode = %i\n", keycode);
	return (0);
}

int		count_height(char *buff)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int		count_width(char *buff)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (buff[i] && buff[i] != '\n')
	{
		if (buff[i] == ' ')
		{
			j++;
			while (buff[i] == ' ')
				i++;
		}
		i++;
	}
	return (j);
}

void	create_matrix(t_whole *whole)
{
	int i;
	int j;
	int k;

	j = -1;
	i = -1;
	k = 0;
	whole->matrix = (t_coord**)malloc(sizeof(t_coord*) * whole->height);
	while (++i < whole->height)
		whole->matrix[i] = (t_coord*)malloc(sizeof(t_coord) * whole->width);
	i = -1;
	while (++i < whole->height)
	{
		while (++j < whole->width)
		{
			whole->matrix[i][j].x = (i * 25) + (j * 25) + 50;
			whole->matrix[i][j].y = (whole->middle.y - j) * 13 + i * 13 + 300;
			whole->matrix[i][j].z = ft_atoi(whole->buff + k);
			whole->matrix[i][j].y -= (whole->matrix[i][j].z * 3);
			while (whole->buff[k] && ((whole->buff[k] >= '0' && whole->buff[k] <= '9') || whole->buff[k] == '-'))
				k++;
			while (whole->buff[k] && (whole->buff[k] == ' ' || whole->buff[k] == '\n'))
				k++;
		}
		j = -1;
	}
}

void	rotate_matrix(t_whole *whole)
{

	(void)whole;




}

void	clear_window(t_whole *whole)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 720)
	{
		while (j < 1080)
		{
			mlx_pixel_put(whole->init, whole->win, j, i, 0x00000000);
			j++;
		}
		j = 0;
		i++;
	}
}


void	print_color(t_whole *whole, t_coord point)
{
		mlx_pixel_put(whole->init, whole->win, (int)point.x, (int)point.y, 0x00FEFFFF);
}


void	trace_higher(t_coord begin, t_coord end, t_whole *whole)
{
	float ratio;
	float y1;

	ratio = (begin.y - end.y) / (end.x - begin.x);
	y1 = begin.y;
	while (begin.x != end.x && begin.y != end.y)
	{
		if (ratio < 1)
		{
			begin.x++;
			begin.y -= ratio;
		}
		else
		{
			begin.y--;
			if (y1 - begin.y > ratio)
			{
				begin.x++;
				ratio += (end.y - begin.y) / (end.x - begin.x);
			
			}
		
		
		
		
		
		
		}
		
		
		
		
		
		
		
		
		
		
		
		print_color(whole, begin);
	}
}

void	trace_lower(t_coord begin, t_coord end, t_whole *whole)
{
	float ratio;
	float y1;

	ratio = (end.y - begin.y) / (end.x - begin.x);
	y1 = begin.y;
	while (begin.x != end.x && begin.y != end.y)
	{
		if (ratio < 1)
		{
			begin.x++;
			begin.y += ratio;
		}
		else
		{
			begin.y++;
			if (begin.y - y1 >= ratio)
			{
				begin.x++;
				ratio += (end.y - begin.y) / (end.x - begin.x);
			}
		}
		print_color(whole, begin);
	}
}






void	trace_line(t_coord begin, t_coord end, t_whole *whole)
{
	if (end.y - begin.y < 0)
		trace_higher(begin, end, whole);
	else	
		trace_lower(begin, end, whole);
}






void	rely_point(t_coord **matrix, int width, int height, t_whole *whole)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		while(j < width)
		{
			if (j < width - 1)
				trace_line(matrix[i][j], matrix[i][j + 1], whole);
			if (i < height - 1)
				trace_line(matrix[i][j], matrix[i + 1][j], whole);
			j++;
		}
		i++;
		j = 0;
	}
}



void	print_matrix(t_coord **matrix, int height, int width)
{
	int i = 0;
	int j = 0;


	while (i < height)
	{
		while (j < width)
		{
			if (matrix[i][j].z == 10)
				printf(" %f", matrix[i][j].z);
			else
				printf("  %f", matrix[i][j].z);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}


void	print_window(t_whole *whole)
{

	mlx_key_hook(whole->win, my_key_func, whole);
	rely_point(whole->matrix, whole->width, whole->height, whole);
	mlx_loop(whole->init);
}





void	treatment(char *buff)
{
	t_whole		*ptr;
	t_whole		whole;

	ptr = &whole;
	whole.height = count_height(buff);
	whole.width = count_width(buff);
	whole.middle.y = whole.height / 2;
	whole.middle.x = whole.width / 2; 
	whole.buff = buff;

	whole.init = mlx_init();
	whole.win = mlx_new_window(whole.init, 1080, 720, "mlx fdf");
	create_matrix(ptr);
	print_matrix(whole.matrix, whole.height, whole.width);


	print_window(ptr);
}



int		main(int ac, char **av)
{
	int fd;
	char buff[BUFF_SIZE];

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr("The file couldn't be open\n");
			exit(1);
		}
		read(fd, buff, BUFF_SIZE);
		treatment(buff);
	}	
	return (0);
}
