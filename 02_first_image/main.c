#include "first_image.h"
#include <stdio.h>

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

//void	*mlx_init(); - prototype
	mlx = mlx_init(); //mlx_init() return void *0 if failed
	if (mlx == (void *)0)
		exit(1);

//create mlx window with 1000 pixel width, 500 pixel height and "First Image!" title
	mlx_win = mlx_new_window(mlx, 1000, 500, "First Image!"); //return void *0 if failed
	if (mlx_win == (void *)0)
		exit(1);

/*
** we can put the pixels directly into the window OR 
** create image, fill it with pixels and put image in the window
*/

//putting pixels directly into the window 
//		int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color); - prototype
	mlx_pixel_put(mlx, //pointer to mlx structure 
		mlx_win, //pointer to mlx window structure
		21, //x-position of pixel (start from left side)
		42, //y-position of pixel (start from top)
		0x00FFFFFF //white color (in "0x00RRGGBB" format) also you can use 0xFFFFFF or (256*256*256 - 1) or 16777215 
		);


//		creating image: void	*mlx_new_image(void *mlx_ptr,int width,int height) - prototype
	img.img = mlx_new_image( //return void *0 if failed
		mlx, //pointer to mlx structure 
		100, //width of image
		50 //height of image
	);

	if (img.img == (void *)0)
		exit(1); //need to free() mlx, mlx_win

//char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian) - prototype
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

/* //you can check values of t_data img structure
printf("'img.img' address is %p, \
	'bits_per_pixel' value is %d, \
	'line_length' value is %d, \
	'endian' value is %d\n",
	&img.img, img.bits_per_pixel, img.line_length, img.endian);
printf("%p\n", &mlx_win);
*/

// I can't find function in minilibX to put pixels in image (not in window). So we will do next:
	img.addr[0] = 0; 	//Blue
	img.addr[1] = 0;	//Green
	img.addr[2] = 0xFF;	//Red
	img.addr[3] = 0;	//Transparency
// by this we put red pixel to the first pixel of image (with [0;0] coordinates)

// NOTICE: that way of filling images are not convenient.
//	Later we will write our own function to fill pixels in the image

//int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y); - prototype
	mlx_put_image_to_window(mlx, //pointer to mlx structure 
		mlx_win, //pointer to mlx window structure
		img.img, //pointer to image
		42, //offset by x
		21 //offset by y
	);
//NOTICE: if you put pixels directly into the window, they will be overwritted by
//	mlx_put_image_to_window if they have one (x;y) position.
//	By offsetting image to the 42 pixels left and 21 pixels down
//	we will not overwrite white pixel putted directle on the window

	mlx_loop(mlx);

//you can see two pixels (white and red) in our window
	return (0);
}

//compilation: gcc main.c -I../mlx -L../mlx -lmlx -framework OpenGL -framework AppKit