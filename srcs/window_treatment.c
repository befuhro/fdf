/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   window_treatment.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 18:09:16 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 14:53:05 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		my_key_func(int keycode, t_whole *whole)
{
	if (keycode == 53 || keycode == 65307)
	{
		free_matrix(whole->matrix, whole->height);
		exit(0);
	}
	if (keycode == 69 || keycode == 78 || (keycode >= 123 && keycode <= 126))
		treat_keycode(keycode, whole);
	return (0);
}

void	treat_keycode(int keycode, t_whole *whole)
{
	mlx_clear_window(whole->init, whole->win);
	if (keycode == 69)
		whole->zoom++;
	if (keycode == 78)
	{
		if (whole->zoom > 0)
			whole->zoom--;
	}
	if (keycode == 124)
		whole->middle.x += 5;
	if (keycode == 123)
		whole->middle.x -= 5;
	if (keycode == 126)
		whole->middle.y -= 5;
	if (keycode == 125)
		whole->middle.y += 5;
	modify_matrix(whole);
	rely_point(whole->matrix, whole->width, whole->height, whole);
}

void	free_matrix(t_coord **matrix, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	zoom(t_coord **matrix, int height, int width, int value)
{
	int		i;
	int		j;
	t_coord middle;

	j = -1;
	i = -1;
	middle.y = height / 2;
	middle.x = width / 2;
	while (++i < height)
	{
		while (++j < width)
		{
			matrix[i][j].x += value * (middle.x - j);
			matrix[i][j].y += value * (middle.y - i);
		}
		j = -1;
	}
}
