/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rely_point.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:31:23 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/16 16:56:42 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	print_color(t_whole *whole, t_coord point)
{
	mlx_pixel_put(whole->init, whole->win, point.x, point.y, 0x00FEFFFF);
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
			if (y1 - begin.y >= ratio)
			{
				begin.x++;
				ratio += (begin.y - end.y) / (end.x - begin.x);
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
		while (j < width)
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
