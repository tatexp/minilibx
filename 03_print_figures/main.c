#include "figures.h"

void print_circle(void *mlx, void *mlx_win, int w, int h, int color)
{
	int x = 0;
	int y = 0;

	//circle formula is "a^2 + b^2 = r^2"
	// let's take radius as min(w;h) / 2
	// and let draw circle in the center of mlx window
	//  to do that we must use formula
	//  (x - w/2)^2 + (y - h/2)^2 = r^2 
	int r = h < w ? h / 2 : w / 2;

	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			// to draw filled circle we must change '=' sigh to '<'
			if ((x - w/2) * (x - w/2) + (y - h/2) * (y - h/2) < r * r) 
				mlx_pixel_put(mlx, mlx_win, x, y, color);
			y++;
		}
		x++;
	}
}

void print_triangle(void *mlx, void *mlx_win, int w, int h, int color)
{
	int x = 0;
	int y = 0;

	// let's draw by rows: first row will contain one pixel and all pixels of last row will be filled
	// it means we must add "w / h" pixels to each next row
	double offset = (double)w / (double)h; //800/500 = 1.6

	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			// if (x < offset * y) //top of triangle in [0;0] point
			if ((w/2 - offset * y / 2 < x) && (x < w/2 + offset * y / 2)) //top point of triangle in the center of first row 
				mlx_pixel_put(mlx, mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}

void print_square(void *mlx, void *mlx_win, int w, int h, int color)
{
	int x = 0;
	int y = 0;

	//sides of square are equal
	// it means side of square = min(w;h)
	int side = h < w ? h : w;
	
	while (x < side)
	{
		y = 0;
		while (y < side)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, color);
			y++;
		}
		x++;
	}
	//you can improve algorithm by drawing border or drawing at the center of mlx window
}


int main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	char	*hint = "Usage: ./figures [arg]\n\tc - to print a circle\n\tt - to print a triangle\n\ts - to print a square";
	int		height = 500;
	int		width = 800;
	int		color = 0x00FFFFFF; //while color

	if (ac == 2)
	{
		if ((av[1][0] == 'c' || av[1][0] == 't' || av[1][0] == 's') && av[1][1] == '\0')
		{
			if ((void *)0 == (mlx = mlx_init() ))
				exit(1);
			if ((void *)0 == (mlx_win = mlx_new_window(mlx, width, height, "Figures") ))
				exit(1);
			if (av[1][0] == 'c') 
				print_circle(mlx, mlx_win, width, height, color);
			else if (av[1][0] == 't')
				print_triangle(mlx, mlx_win, width, height, color);
			else //(av[1][0] == 's')
				print_square(mlx, mlx_win, width, height, color);
			mlx_loop(mlx);
		}
		else
			printf("%s\n", hint);
	}
	else
		printf("%s\n", hint);
	return (0);
}
