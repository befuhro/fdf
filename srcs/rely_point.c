/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rely_point.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:31:23 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 21:49:39 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	manage_z(t_coord begin, t_coord end, t_coord *line)
{
	float ratio;

	if (begin.z != end.z)
	{
		if (begin.y > end.y)
		{
			ratio = (begin.y - end.y) / (end.x - begin.x);
			if (ratio > 1)
				line->z += (end.z - begin.z) / (begin.y - end.y);
			else
				line->z += (end.z - begin.z) / (end.x - begin.x);
		}
		else
		{
			ratio = (end.y - begin.y) / (end.x - begin.x);
			if (ratio > 1)
				line->z -= (begin.z - end.z) / (end.y - begin.y);
			else
				line->z -= (begin.z - end.z) / (end.x - begin.x);
		}
	}
}

void	trace_higher(t_coord begin, t_coord end, t_whole *whole)
{
	float	ratio;
	t_coord	line;

	ratio = (begin.y - end.y) / (end.x - begin.x);
	line = begin;
	print_color(whole, line);
	while (line.x != end.x && line.y != end.y)
	{
		if (ratio < 1)
		{
			line.x++;
			line.y -= ratio;
		}
		else
		{
			line.y--;
			if (begin.y - line.y >= ratio)
			{
				line.x++;
				ratio += (begin.y - end.y) / (end.x - begin.x);
			}
		}
		manage_z(begin, end, &line);
		print_color(whole, line);
	}
}

void	trace_lower(t_coord begin, t_coord end, t_whole *whole)
{
	float	ratio;
	t_coord	line;

	ratio = (end.y - begin.y) / (end.x - begin.x);
	line = begin;
	while (line.x != end.x)
	{
		if (ratio < 1)
		{
			line.x++;
			line.y += ratio;
		}
		else
		{
			line.y++;
			if (line.y - begin.y >= ratio)
			{
				line.x++;
				ratio += (end.y - begin.y) / (end.x - begin.x);
			}
		}
		manage_z(begin, end, &line);
		print_color(whole, line);
	}
}

void	rely_point(t_coord **matrix, int width, int height, t_whole *whole)
{
	int i;
	int j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (j < width - 1)
			{
				if (matrix[i][j + 1].y - matrix[i][j].y < 0)
					trace_higher(matrix[i][j], matrix[i][j + 1], whole);
				else
					trace_lower(matrix[i][j], matrix[i][j + 1], whole);
			}
			if (i < height - 1)
			{
				if (matrix[i + 1][j].y - matrix[i][j].y < 0)
					trace_higher(matrix[i][j], matrix[i + 1][j], whole);
				else
					trace_lower(matrix[i][j], matrix[i + 1][j], whole);
			}
		}
	}
}
