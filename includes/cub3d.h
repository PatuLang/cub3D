#ifndef CUB3D_H
#define CUB3D_H

#define WALL "textures/wall.png"
#define GROUND "textures/ground.png"
#define PI 3.14159265358979323846
#define FOV 60
#define DEGREE 0.01745329
#define STEPSIZE 1

#define screenwidth  1500 // HIGHER VALUES WILL CAUSE LAG
#define screenlength 1000 // HIGHER VALUES WILL CAUSE LAG

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_wall
{
	mlx_texture_t	*txt[4];
	int side;
	double	x;
	double	y;
	double	ty_off;
	double	ty_step;
}	t_wall;

typedef struct s_map
{
	int	fd;
	int	linecount;
	int wallcount;
	int	lenght;
	int	plocation[2]; // 0 for x // 1 for y

	double pa;

	int side;

	double diry;
	double dirx;

	double raydirx;
	double raydiry;
	double raypa;

	double	rayposy;
	double	rayposx;

	double	cameraposy;
	double	cameraposx;

	double wallX;
	double wallY;

	int stepy;
	int stepx;

	t_wall	wall;

	//double sidedisty;
	//double sidedistx;

	double deltadisty;
	double deltadistx;

	int mapy;
	int mapx;

	int lastx;
	int	lasty;

	int rayamount;

	double firstray[2]; // 0 for x // 1 for y

	char	playerstartpos;
	char	**mapsave;
	char	**mapcopy;
	mlx_t	*mlx;

	mlx_image_t		*background;
	mlx_texture_t	*background_txt;
	mlx_texture_t	*player_txt;

}	t_map;


void	ft_init_textu(t_map *map);
void	ft_create_wall(t_map *img);


void	 read_map(t_map *map, char *map_name);
void	save_map(t_map *map, char *map_name);
int		wallfloodfill(t_map *map, int posy, int posx);
int		check_num(char c);
void	loop_trough(t_map *map, char *str, int count);


#endif