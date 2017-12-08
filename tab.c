#include <libft.h>
#include "include/fdf.h"
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

t_coord	**create_tab(int width, int height, char *buff)
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
			matrix[i][j].x = (i * 30) + (j * 30) + 50;
			matrix[i][j].y = ((width - j) * 22) + (i * 22) + 50;
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

void	print_color(t_mlx mlx, t_coord point, t_coord begin, t_coord end)
{
	if (begin.z == 0 && end.z == 0)	
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x002BBF2B);
	if (begin.z > 0 && end.z > 0)	
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x00FEFEFE);
	if (begin.z > 0 && end.z == 0)
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x007D540D);
	if (end.z > 0 && begin.z == 0)
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x007D540D);



	if (begin.z < 0 && end.z < 0)	
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x002B3ABF);
	if (begin.z < 0 && end.z == 0)
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x002BABBF);
	if (end.z < 0 && begin.z == 0)
		mlx_pixel_put(mlx.init, mlx.win, point.x, point.y, 0x002BABBF);
}


void	trace_higher(t_coord begin, t_coord end, t_mlx mlx)
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
			print_color(mlx, line, begin, end);
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
			print_color(mlx, line, begin, end);
		}
	}
}



void	trace_lower(t_coord begin, t_coord end, t_mlx mlx)
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
			print_color(mlx, line, begin, end);
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
			print_color(mlx, line, begin, end);
		}
	}
}






void	trace_line(t_coord begin, t_coord end,  t_mlx mlx)
{
	if (end.y - begin.y < 0)
		trace_higher(begin, end, mlx);
	else	
		trace_lower(begin, end, mlx);

}






void	rely_point(t_coord **matrix, int width, int height, t_mlx mlx)
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
				trace_line(matrix[i][j], matrix[i][j + 1], mlx);
			if (i < height - 1)
				trace_line(matrix[i][j], matrix[i + 1][j], mlx);
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


void	print_window(t_coord **matrix, int height, int width)
{
	t_mlx mlx;

	mlx.init = mlx_init();
	mlx.win = mlx_new_window(mlx.init, 1080, 720, "mlx fdf");


	rely_point(matrix, width, height, mlx);
	mlx_key_hook(mlx.win, my_key_func, mlx.init);
	mlx_loop(mlx.init);
}





void	treatment(char *buff)
{
	int		height;
	int		width;
	t_coord	**matrix;

	height = count_height(buff);
	width = count_width(buff);
	matrix = create_tab(width, height, buff);
	print_matrix(matrix, height, width);
	print_window(matrix, height, width);
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
