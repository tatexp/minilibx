#include "opposite.h"

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

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int make_opposite(int color)
{
	return (create_trgb( get_t(color),	//same transparency
		255 - get_r(color),				//opposite red color
		255 - get_g(color),				//opposite green color
		255 - get_b(color) )			//opposite blue color
	);
}

void print_circle(t_data *img, int w, int h, int color)
{
	int x = 0;
	int y = 0;

	int r = h < w ? h / 2 : w / 2;

	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			if ((x - w/2) * (x - w/2) + (y - h/2) * (y - h/2) < r * r) 
				my_mlx_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	int 	width = 1000;
	int		height = 500;
	int 	color;
	int		opposite_color;
	
	if ((mlx = mlx_init() ) == (void *)0)
		exit(1);

	if ((mlx_win = mlx_new_window(mlx, width, height, "Opposite color") ) == (void *)0)
		exit(1);
	
	if ( (img.img = mlx_new_image(mlx, width, height) ) == (void *)0)
		exit(1); //need to free() mlx, mlx_win
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	color = 0x0045cea2; //random color named "Трилистник Крайола" by yandex.ru
	// color = 0x00252850; //random color https://get-color.ru/random/#Nightblue
	// color = 0x00FF0000; //red color
	
	print_circle(&img, width / 2, height, color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); //put image with no offset

	bzero(img.addr, height * img.line_length); //to erase image use bzero 

	opposite_color = make_opposite(color);
	print_circle(&img, width / 2, height, opposite_color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 500, 0); //put image with offset 500 pixels by x and 0 pixels by y


	mlx_loop(mlx);

	return (0);
}
