/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:28:20 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 17:26:26 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	check_file(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if ((file[i] < '0' || file[i] > '9')
			&& (file[i] < 9 || file[i] > 13)
			&& file[i] != ' ' && file[i] != '-')
		{
			ft_putendl("The format of the file is wrong");
			exit(0);
		}
		i++;
	}
}

void	treatment(char *buff)
{
	t_whole		whole;

	check_file(buff);
	whole.height = count_height(buff);
	whole.width = count_width(buff);
	whole.middle.y = 360;
	whole.middle.x = 540;
	whole.zoom = 1;
	whole.buff = buff;
	whole.init = mlx_init();
	whole.win = mlx_new_window(whole.init, 1080, 720, "mlx fdf");
	create_matrix(&whole);
	print_window(&whole);
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
