# minilibx
Understanding minilibx
Examples with minilibx

# Links
link on documentation https://harm-smits.github.io/42docs/libs/minilibx.html

# Installation on MacOs
1. Uncompress a tar archive with minilibx

  `tar -xvf lib/minilibx_opengl.tgz`

2. cd into folder

  `cd minilibx_opengl_20191021/`

3. run makefile

  `make`

4. libmlx.a file created

# Compilation
1. Copy libmlx.a and mlx.h files to your folder
2. Write your main.c file
3. Compile

`gcc main.c -L. -lmlx -framework OpenGL -framework AppKit`

4. Executable a.out file created
