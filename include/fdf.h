/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 12:55:10 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 14:54:29 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <fcntl.h>
# include "mlx.h"
# include <stdlib.h>
# include "libft.h"
# include <math.h>
# define BUFF_SIZE 64000

typedef struct	s_coord
{
	float x;
	float y;
	float z;
}				t_coord;

typedef struct	s_whole
{
	void	*init;
	void	*win;
	int		zoom;
	int		z_min;
	int		z_max;
	t_coord	middle;
	int		height;
	int		width;
	char	*buff;
	t_coord	**matrix;
}				t_whole;

void			create_matrix(t_whole *whole);
void			modify_matrix(t_whole *whole);
void			rely_point(t_coord **matrix, int width, int height,\
				t_whole *whole);
void			clear_window(t_whole *whole);
int				my_key_func(int keycode, t_whole *whole);
int				count_height(char *buff);
int				count_width(char *buff);
void			print_color(t_whole *whole, t_coord point);
void			trace_higher(t_coord begin, t_coord end, t_whole *whole);
void			trace_lower(t_coord begin, t_coord end, t_whole *whole);
void			trace_line(t_coord begin, t_coord end, t_whole *whole);
void			rely_point(t_coord **matrix, int width, int height,\
				t_whole *whole);
void			print_matrix(t_coord **matrix, int height, int width);
void			print_window(t_whole *whole);
void			treatment(char *buff);
void			zoom(t_coord **matrix, int height, int width, int value);
void			clear_window(t_whole *whole);
void			free_matrix(t_coord **matrix, int height);
void			treat_keycode(int keycode, t_whole *whole);

#endif
