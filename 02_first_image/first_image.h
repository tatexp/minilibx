#ifndef FIRST_IMAGE_H
#define FIRST_IMAGE_H

#include <stdlib.h>
#include "mlx.h"

typedef struct	s_data {		//structure for image
	void	*img;				//pointer to image
	char	*addr;				//data of image
	int		bits_per_pixel;		//size of one pixel of image (by default set to 8 bit * 4 = 32 bit in mlx library)
	int		line_length;		//image width in bytes (or pixels * bits_per_pixel / 8)
	int		endian;				//little/big endian 
}				t_data; 

/*
** bits_per_pixel:
		every pixel has transparency property + 
			value of red color +
			value of green color +
			value of blue color
		each of this property is value between 0 and 255
		it means that it takes 8bit * 4 = 32bit of memory
		
**  endian : 0 = sever X is little endian, 1 = big endian
**  endian : useless on macos, client and graphical framework have the same endian

*/

#endif

