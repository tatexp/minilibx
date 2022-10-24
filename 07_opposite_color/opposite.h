#ifndef OPPOSITE_H
#define OPPOSITE_H

# include <stdlib.h>
# include <stdio.h>
# include <strings.h> //for bzero
# include "mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif

