/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix_treatment.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:27:21 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 16:48:47 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

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
	{
		whole->matrix[i] = (t_coord*)malloc(sizeof(t_coord) * whole->width);
		while (++j < whole->width)
		{
			whole->matrix[i][j].x = (i * (2 * whole->zoom)) + (j * (2 * whole->zoom)) + 25;
			whole->matrix[i][j].y = (whole->middle.y - j) * whole->zoom + i * whole->zoom + 300;
			whole->matrix[i][j].z = ft_atoi(whole->buff + k);
			whole->matrix[i][j].y -= (whole->matrix[i][j].z * 2);
			while (whole->buff[k] && ((whole->buff[k] >= '0' &&
					whole->buff[k] <= '9') || whole->buff[k] == '-'))
				k++;
			while ((whole->buff[k] == ' ' || whole->buff[k] == '\n'))
				k++;
		}
		j = -1;
	}
}
