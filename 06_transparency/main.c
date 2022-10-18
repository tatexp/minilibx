#include "transparency.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//creates a color
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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

//add transparency to color
void add_shade(int *color, double distance)
{
	*color = *color + ( (int)(distance * 255) << 24);
}

unsigned int	get_color_from_img(t_data data, int x, int y)
{
	int offset;

	offset = y * data.line_length + x * (data.bits_per_pixel / 8);

	return ( create_trgb(
		data.addr[offset + 3], data.addr[offset + 2], data.addr[offset + 1], data.addr[offset]
		)
	);
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	int		x = 0;
	int		y = 0;

	int 	width = 500;
	int		height = 500;
	int		color;
	int		color_shade;
	unsigned int ucolor;
	
	if ((mlx = mlx_init() ) == (void *)0)
		exit(1);

	if ((mlx_win = mlx_new_window(mlx, width, height, "Rainbow with transparency") ) == (void *)0)
		exit(1);
	
	if ( (img.img = mlx_new_image(mlx, width, height) ) == (void *)0)
		exit(1); //need to free() mlx, mlx_win
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	while (y < height)
	{
		x = 0;
		color = choose_color(y, height);
		color_shade = color;
		add_shade(&color_shade, 0.75);

		while (x < width)
		{
			if (x > 100)
				my_mlx_pixel_put(&img, x, y, color_shade);
			else
				my_mlx_pixel_put(&img, x, y, color);
			x++;
		}
		y++;
	}
	x = 0;
	y = 0;
	while (x < 100)
	{
		ucolor = get_color_from_img(img, x++, 0);
		printf("%d\n", ucolor);
	}
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx);

	return (0);
}
