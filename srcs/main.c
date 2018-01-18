/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:28:20 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/17 16:46:14 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		my_key_func(int keycode)
{
	if (keycode == 53 || keycode == 65307)
		exit(0);
	return (0);
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
//	print_matrix(whole.matrix, whole.height, whole.width);
	print_window(ptr);
}

int		main(int ac, char **av)
{
	int		fd;
	char	buff[BUFF_SIZE + 1];
	int		ret;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putendl("The file couldn't be open");
			exit(1);
		}
		ret = read(fd, buff, BUFF_SIZE);
		buff[ret] = '\0';
		treatment(buff);
	}
	return (0);
}
