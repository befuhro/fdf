/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix_treatment.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:27:21 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/27 13:37:35 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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
	j = 0;
	while (buff[i] && buff[i] != '\n')
	{
		if ((buff[i] >= '0' && buff[i] <= '9') || buff[i] == '-')
			j++;
		while ((buff[i] >= '0' && buff[i] <= '9') || buff[i] == '-')
			i++;
		while (buff[i] == ' ')
			i++;
	}
	return (j);
}

void	manage_coord(t_whole *whole, int i, int j, int k)
{
	whole->matrix[i][j].x = 540 - (((whole->height / 2 - i) * 2) * \
			whole->zoom) - (((whole->width / 2 - j) * 2) * whole->zoom);
	whole->matrix[i][j].y = 360 - ((whole->height / 2 - i) * whole->zoom) \
			+ ((whole->width / 2 - j) * whole->zoom);
	whole->matrix[i][j].z = ft_atoi(whole->buff + k);
	whole->matrix[i][j].y -= whole->matrix[i][j].z * (3 * whole->zoom);
	if (whole->matrix[i][j].z < whole->z_min)
		whole->z_min = whole->matrix[i][j].z;
	if (whole->matrix[i][j].z > whole->z_max)
		whole->z_max = whole->matrix[i][j].z;
}

void	modify_matrix(t_whole *whole)
{
	int i;
	int j;
	int k;

	j = -1;
	i = -1;
	k = 0;
	while (++i < whole->height)
	{
		while (whole->buff[k] == ' ')
			k++;
		while (++j < whole->width)
		{
			manage_coord(whole, i, j, k);
			while (whole->buff[k] && ((whole->buff[k] >= '0' &&
							whole->buff[k] <= '9') || whole->buff[k] == '-'))
				k++;
			while (whole->buff[k] == ' ')
				k++;
		}
		k++;
		j = -1;
	}
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
		while (whole->buff[k] == ' ')
			k++;
		while (++j < whole->width)
		{
			manage_coord(whole, i, j, k);
			while (whole->buff[k] && ((whole->buff[k] >= '0' &&
							whole->buff[k] <= '9') || whole->buff[k] == '-'))
				k++;
			while (whole->buff[k] == ' ')
				k++;
		}
		k++;
		j = -1;
	}
}
