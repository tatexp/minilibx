#include "mlx.h"

//Copy of ../00_hello_world/main.c

int main(void)
{
	void	*mlx; //pointer to mlx structure: window + image structures + loop_hook + loop_timer + ...
	void	*mlx_win; //pointer to mlx window (which will be inside mlx structure)

//void	*mlx_init(); - prototype
	mlx = mlx_init(); //start with mlx_init : init mlx structure

//void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title); - prototype
	mlx_win = mlx_new_window( //add window structure to mlx structure
		mlx,				//pointer to mlx structure
		1000,				//window's width
		500, 				//window's height
		"Hello world!" 		//window's title
	);

//int	mlx_loop (void *mlx_ptr); - prototype
	mlx_loop(				//Loop over the given mlx pointer
		mlx 				//pointer to mlx structure
	); 
	return (0);
}

//compilation: gcc main.c -I../mlx -L../mlx -lmlx -framework OpenGL -framework AppKit
