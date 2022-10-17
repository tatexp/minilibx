#include "performance.h"
 
/*	//man gettimeofday =>
	struct timeval {
             time_t       tv_sec;   // seconds since Jan. 1, 1970 
             suseconds_t  tv_usec;  // and microseconds 1/1 000 000 of a second
     };
*/

long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	/*if (n == -2147483648)
		ft_putstr("-2147483648");
	else */if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_directly_in_window(void *mlx, void *mlx_win, int width, int height, int color)
{
	int		x = 0;
	int		y = 0;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}

void	fill_image_n_put_in_window(void *mlx, void *mlx_win, t_data *img, int width, int height, int color)
{
	int		x = 0;
	int		y = 0;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	int		width;
	int		height;
	long	start_time;
	
	int		c = 1;

	mlx_get_screen_size(&width, &height);
	//printf("width = %d, height = %d\n", width, height);
	
	start_time = get_time();
	
	if ((mlx = mlx_init() ) == (void *)0)
		exit(1);

	if ((mlx_win = mlx_new_window(mlx, width, height, "Performance Test") ) == (void *)0)
		exit(1);

	if ( (img.img = mlx_new_image(mlx, width, height) ) == (void *)0)
		exit(1); //need to free() mlx, mlx_win
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	while (c < 256)
	{
		// put_directly_in_window(mlx, mlx_win, width, height, create_trgb(0, c, c, c) ); //uncomment to test
		//statistics for put_directly_in_window (screen size 2560*1440):
			// 2179
			// 4039
			// 5913
			// 7773
			// 9648
			// 11508
			// 13382
			// 15244
			// 15244 - 2179 = 13065 ms between first and last frames
			// 13065 / 7 = 1870 ms per frame
		
		fill_image_n_put_in_window(mlx, mlx_win, &img, width, height, create_trgb(0, c, c, c) ); //uncomment to test
		//statistics for put_directly_in_window (screen size 2560*1440):
			// 331
			// 370
			// 407
			// 463
			// 519
			// 574
			// 630
			// 686
			// 20 times faster! (total time)
			// 686 - 331 = 355 ms between first and last frames
			// 355 / 7 = 50 ms per frame (37 times faster!)
		ft_putnbr( (int)(get_time() - start_time) / 1000 );
		write(1, "\n", 1);
		c *= 2;
	}
	mlx_loop(mlx);

	return (0);
}
