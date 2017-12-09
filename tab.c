#include <libft.h>
#include "include/fdf.h"
#include <mlx.h>
#include <stdio.h>

t_coord **create_matrix(int latitude, int width, int height, char *buff);
void	rely_point(t_coord **matrix, int width, int height, t_whole *whole);
void	clear_window(t_whole *whole);

int		my_key_func(int keycode, t_whole *whole)
{
	if (keycode == 53 || keycode == 65307)
		exit(0);
	if (keycode == 65362)
	{
		whole->latitude += 1;
		whole->matrix = create_matrix(whole->latitude, whole->width, whole->height, whole->buff);
		clear_window(whole);	
		rely_point(whole->matrix, whole->width, whole->height, whole);
	}

	if (keycode == 65364)
	{
		whole->latitude -= 1;
		whole->matrix = create_matrix(whole->latitude, whole->width, whole->height, whole->buff);
		clear_window(whole);	
		rely_point(whole->matrix, whole->width, whole->height, whole);
	}




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

t_coord	**create_matrix(int latitude, int width, int height, char *buff)
{
	t_coord **matrix;
	int i;
	int j;
	int k;

	j = -1;
	i = -1;
	k = 0;
	matrix = (t_coord**)malloc(sizeof(t_coord*) * height);
	while (++i < height)
		matrix[i] = (t_coord*)malloc(sizeof(t_coord) * width);
	i = -1;
	while (++i < height)
	{
		while (++j < width)
		{
			matrix[i][j].x = (i * 25) + (j * 25) + 50;
			matrix[i][j].y = ((width - j) * latitude) + (i * latitude) + 300;
			matrix[i][j].z = ft_atoi(buff + k);
			if (matrix[i][j].z != 0)
				matrix[i][j].y -= (matrix[i][j].z * 6);
			while (buff[k] && ((buff[k] >= '0' && buff[k] <= '9') || buff[k] == '-'))
				k++;
			while (buff[k] && (buff[k] == ' ' || buff[k] == '\t' || buff[k] == '\n'))
				k++;
		}
		j = -1;
	}
	return (matrix);
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


void	print_color(t_whole *whole, t_coord point, t_coord begin, t_coord end)
{
	if (begin.z == 0 && end.z == 0)	
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x002BBF2B);
	if (begin.z > 0 && end.z > 0)	
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x00FEFEFE);
	if (begin.z > 0 && end.z == 0)
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x007D540D);
	if (end.z > 0 && begin.z == 0)
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x007D540D);



	if (begin.z < 0 && end.z < 0)	
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x002B3ABF);
	if (begin.z < 0 && end.z == 0)
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x002BABBF);
	if (end.z < 0 && begin.z == 0)
		mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x002BABBF);
}


void	trace_higher(t_coord begin, t_coord end, t_whole *whole)
{
	t_coord line;
	float base;
	float count;
	float count_base;

	count = 1;
	base = ((float)begin.y - (float)end.y) / ((float)end.x - (float)begin.x);
	count_base = base;
	line.x = begin.x;
	line.y = begin.y;
	if (base < 1)
	{
		while (line.x != end.x && line.y != end.y)
		{
			if (base < count)
				line.x += 1;
			else
			{	
				line.y -= 1;
				line.x += 1;
				count ++;
			}
			base += count_base;
			print_color(whole, line, begin, end);
		}
	}
	else
	{
		while (line.x != end.x && line.y != end.y)
		{
			if (base > count)
				line.y -=1;
			else
			{
				line.y -= 1;
				line.x += 1;
				base += count_base;
			}
			count++;
			print_color(whole, line, begin, end);
		}
	}
}



void	trace_lower(t_coord begin, t_coord end, t_whole *whole)
{
	t_coord line;
	float base;
	float count;
	float count_base;

	count = 1;
	base = ((float)end.y - begin.y) / ((float)end.x - begin.x);
	count_base = base;
	line.x = begin.x;
	line.y = begin.y;
	if (base < 1)
	{
		while (line.x != end.x && line.y != end.y)
		{
			if (base < count)
				line.x += 1;
			else
			{	
				line.y += 1;
				line.x += 1;
				count ++;
			}
			base += count_base;
			print_color(whole, line, begin, end);
		}
	}
	else
	{
		while (line.x != end.x && line.y != end.y)
		{
			if (base > count)
				line.y += 1;
			else
			{
				line.y += 1;
				line.x += 1;
				base += count_base;
			}
			count++;
			print_color(whole, line, begin, end);
		}
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
				printf(" %i", matrix[i][j].z);
			else
				printf("  %i", matrix[i][j].z);
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
	whole.latitude = 10;
	whole.height = count_height(buff);
	whole.width = count_width(buff);
	whole.buff = buff;
	
	whole.init = mlx_init();
	whole.win = mlx_new_window(whole.init, 1080, 720, "mlx fdf");
	whole.matrix = create_matrix(whole.latitude, whole.width, whole.height, buff);
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
