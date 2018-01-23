/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rely_point.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 16:31:23 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 20:26:52 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int n)
{
	if (n < 0)
		return (-1);
	return (n);
}

void	print_color(t_whole *whole, t_coord point)
{
	int color;
	int hex1;
	int hex2;

	color = 16777215;
	hex1 = 0;
	hex2 = 0;
	if (whole->z_max != 0 || whole->z_min != 0)
		point.z *= 255 / (whole->z_max - ft_abs(whole->z_min));
	if (point.z >= -25 && point.z < 0)
		point.z = 0;

	while (point.z >= 16 || point.z <= -16)
	{
		if (point.z >= 16)
		{
			point.z -= 16;
			hex2++;
		}
		else
		{
			point.z += 16;
			hex2--;
		}
	}
	while (point.z >= 1 || point.z < 0)
	{
		if (point.z > 0)
		{
			point.z--;
			hex1++;
		}
		else
		{
			point.z++;
			hex1--;
		}
	}
	if (hex1 >= 0 || hex2 >= 0)
		color -= (hex2 * pow(16, 3)) + (hex1 * pow(16, 2)) + (hex2 * 16) + hex1;
	else
		color += hex2 * pow(16, 5) + hex1 * pow(16, 4);
	mlx_pixel_put(whole->init, whole->win, point.x, point.y, color);
}

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
