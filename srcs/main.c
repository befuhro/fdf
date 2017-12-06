#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int		my_key_function(int keycode, void *param)
{
	printf("key event %i\n", keycode);
	if (keycode == 53)
		exit(0);
	(void)param;
	return (0);
}


int		main(void)
{
	void *mlx;
	void *win;
	int x;
	int y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	x = 150;
	y = 150;
	while (y <= 250)
	{
		while (x <= 250)
		{
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			x++;
		}
		x = 150;
		y++;
	}
	mlx_key_hook(win, my_key_function, mlx);
	mlx_loop(mlx);
	return (0);
}
