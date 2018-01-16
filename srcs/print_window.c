/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:35:47 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/16 16:55:23 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	print_matrix(t_coord **matrix, int height, int width)
{
	int i;
	int j;

	i = 0;
	j = 0;
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
