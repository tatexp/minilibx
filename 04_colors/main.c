#include "colors.h"

//creates a color
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//take line number and return color for rainbow
//rainbow colors:
//  red 		0x00FF0000
//	orange 		0x00ffa500
//  yellow		0x00ffff00
//  green		0x00008000
//  blue		0x0000aaff
//  dark blue	0x000000ff
//  purple		0x008b00ff

int	choose_color(int y, int height)
{
	double	offset = 256 / ( (double)height / 6); //each line will change color to offset value
	double	part = (double)y / (double)height;

	//1) start with red => r = 255, g = 0, b = 0
	//2) then increase green color to 255 => r = 255, g = 255, b = 0
	//3) then decrease red color to 0 => r = 0, g = 255, b = 0
	//4) then increase blue color to 255 => r = 0, g = 255, b = 255
	//5) then decrease green color to 0 => r = 0, g = 0, b = 255
	//6) then increase red color to 255 => r = 255, g = 0, b = 255
	//7) then decrease blue color to 0 => r = 255, g = 0, b = 0
	if (part * 6 < 1)
		return create_trgb(0, 255, y * offset, 0);
	else if (part * 6 < 2)
		return create_trgb(0, 255 - ((int)(y * offset) % 256), 255, 0);
	else if (part * 6 < 3)
		return create_trgb(0, 0, 255, y * offset);
	else if (part * 6 < 4)
		return create_trgb(0, 0, 255 - ((int)(y * offset) % 256), 255);
	else if (part * 6 < 5)
		return create_trgb(0, y * offset, 0, 255);
	else if (part * 6 < 6)
		return create_trgb(0, 255, 0, 255 - ((int)(y * offset) % 256));
	return 0;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	int		x = 0;
	int		y = 0;

	int 	width = 500;
	int		height = 500;
	int		color;
	
	if ((mlx = mlx_init() ) == (void *)0)
		exit(1);

	if ((mlx_win = mlx_new_window(mlx, width, height, "Rainbow") ) == (void *)0)
		exit(1);

	while (y < height)
	{
		x = 0;
		color = choose_color(y, height);

		while (x < width)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, color);
			x++;
		}
		y++;
	}




	mlx_loop(mlx);

//you can see two pixels (white and red) in our window
	return (0);
}

//compilation: gcc main.c -I../mlx -L../mlx -lmlx -framework OpenGL -framework AppKit