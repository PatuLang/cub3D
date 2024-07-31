#include "../includes/cub3d.h"

#include <stdio.h>

int checkwallhit(t_map *map, int y, int x)
{
	int mapy = (int)map->cameraposy / 20;
	int mapx = (int)map->cameraposx / 20 + 8;
	//double deltadistx = sqrt(1 + (map->raydiry * map->raydiry) / (rmap->raydirx * map->raydirx));
	//double deltadisty = sqrt(1 + (map->raydirx * map->raydirx) / (map->raydiry * map->raydiry));
	//if (map->raydirx < 0)
    //{
    //    map->stepx = -1;
    //    map->sidedistx = (posX - mapX) * deltadistx;
    //}
    //else
    //{
    //    map->stepx = 1;
    //    map->sidedistx = (mapX + 1.0 - posX) * deltadistx;
    //}
    //if (map->raydiry < 0)
    //{
    //    map->stepy = -1;
    //    sideDistY = (posY - mapY) * deltadisty;
    //}
    //else
    //{
    //	map->stepy = 1;
    //	sideDistY = (mapY + 1.0 - posY) * deltadisty;
    //}
	int yn;
	int xn;

	yn = 0;
	xn = 0;
	while (x >= 0)
	{
		xn++;
		x -= 20;
	}
	while (y >= 0)
	{
		yn++;
		y -= 20;
	}
	if (map->mapsave[yn + 7][xn - 1] == '1')
		return (1);
	return (0);
}


//void	makethewalls(t_map *map)
//{
//	double length = sqrt((map->cameraposx - map->rayposx) * (map->cameraposx - map->rayposx) +
//                      (map->cameraposy - map->rayposy) * (map->cameraposy - map->rayposy));
//	double correct = map->pa - map->raypa;
//	length *= cos(correct);
//	int wall_height;
//	if (length > 0)
//		wall_height = (20 * screenlength) / length;
//	else
//		wall_height = (20 * screenlength);
//	int	begin;
//	int end;
//	int y;

//	map->fd = 1;


//	int i = 0;
//	while (i < 20)
//	{
//		begin = (screenlength / 2) - (wall_height / 3);
// 		end = (screenlength / 2) + (wall_height / 3);
//		y = begin - 1;
//		while  (y < 0)
//			y++;
//		while (++y < end && y < screenlength)
//			mlx_put_pixel(map->background, map->rayamount + i, y, 0XFFFFFF);
//		i++;
//	}
//}

void	makethewalls(t_map *map)
{
	double length = sqrt(pow(map->cameraposx - map->rayposx, 2) + pow(map->cameraposy - map->rayposy, 2));
	double correct = map->pa - map->raypa;
	length *= cos(correct);
	int wall_height;
	if (length > 0)
		wall_height = (20 * screenlength) / length;
	else
		wall_height = (20 * screenlength);
	int	begin;
	int end;
	int y;

	int i = 0;
	int untily;
	while (i < 20)
	{
		begin = (screenlength / 2) - (wall_height / 2);
 		end = (screenlength / 2) + (wall_height / 2);
		y = begin - 1;
		untily = 0;
		while  (y < 0)
			y++;
		while (untily++ < y)
			mlx_put_pixel(map->background, map->rayamount + i, untily, 11111111);
		while (++y < end && y < screenlength)
					mlx_put_pixel(map->background, map->rayamount + i, y, 0XFFFFFF);
		while (y++ <= screenlength)	
			mlx_put_pixel(map->background, map->rayamount + i, y, 00000000);
		i++;
	}
}

void shoot_ray(t_map *map)
{
	double yx[2];
	int i = 0;
	yx[1] = map->cameraposy;
	yx[0] = map->cameraposx;
	//printf("y%f x%f | iy%d ix%d\n", yx[1], yx[0], map->player->instances[0].y, map->player->instances[0].x);
	while (!checkwallhit(map, yx[1], yx[0]))
	{
		//mlx_put_pixel(map->background, yx[0], yx[1], 0XFFFFFF);
		yx[0] += map->raydirx / 10;
		yx[1] += map->raydiry / 10;
		i++;
	}
	map->rayposx = yx[0];
	map->rayposy = yx[1];
}

void	makethelines(t_map *map)
{
	map->rayamount = screenwidth / 2;
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa;

	shoot_ray(map);
	makethewalls(map);
	//shoot_ray(map);
	int i = 0;
	while (i < 60)
	{
		map->rayamount += screenwidth / 120;
		map->raypa += 0.01;
		if (map->raypa > 2 * PI)
		{
			map->raypa -= 2 * PI;
		}
		map->raydirx = cos(map->raypa);
		map->raydiry = sin(map->raypa);
		shoot_ray(map);
		makethewalls(map);
		i++;
	}
	map->raydiry = map->diry;
	map->raydirx = map->dirx;
	map->raypa = map->pa;

	i = 1;
	map->rayamount = screenwidth / 2;
	map->rayamount -= screenwidth / 120;
	while (i < 60)
	{
		map->rayamount -= screenwidth / 120;
		map->raypa -= 0.01;
		if (map->raypa < 0)
		{
			map->raypa += 2 * PI;
		}
		map->raydirx = cos(map->raypa);
		map->raydiry = sin(map->raypa);
		shoot_ray(map);
		makethewalls(map);
		i++;
	}
}

void reset(t_map *map)
{
		int abcx = 0;
		int abcy = 0;
		while (abcx <= 1200)
		{
			abcy = 0;
			while (abcy <= 300)
			{
				mlx_put_pixel(map->background, abcx, abcy, 11111111);
				abcy++;
			}
			while (abcy <= 600)
			{
				mlx_put_pixel(map->background, abcx, abcy, 00000000);
				abcy++;
			}
			abcx++;
		}
}

void ft_loop_hook(void *param)
{
	t_map	*map;

	map = param;
	makethelines(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->cameraposy += map->diry;
		map->cameraposx += map->dirx;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->cameraposy -= map->diry;
		map->cameraposx -= map->dirx;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->cameraposy -= map->dirx / 1.5;
		map->cameraposx -= -map->diry / 1.5;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->cameraposy += map->dirx / 1.5;
		map->cameraposx += -map->diry / 1.5;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= 0.1;
		if (map->pa < 0)
		{
			map->pa += 2 * PI;
		}
		map->dirx = cos(map->pa) * 2;
		map->diry = sin(map->pa) * 2;
		//reset(map);

	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += 0.1;
		if (map->pa >= 2 * PI)
		{
			map->pa -= 2 * PI;
		}
		map->dirx = cos(map->pa) * 2;
		map->diry = sin(map->pa) * 2;
		//reset(map);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;

	//double angle = pa / (1.0 + 0.28 * pa * pa);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		{
			reset(map);
		}
}

void	start_window(t_map *map)
{
	map->mlx = mlx_init(screenwidth, screenlength, "Game", false);
	ft_init_textu(map);
	ft_init_img(map->mlx, map);
	reset(map);
	mlx_image_to_window(map->mlx, map->background, 0, 0);
	mlx_put_pixel(map->background, 440, 100, 535353);
	//ft_create_wall(map);
	if (map->playerstartpos == 'N')
		map->pa = 4.74;
	else if (map->playerstartpos == 'S')
		map->pa = -4.74;
	else if (map->playerstartpos == 'E')
		map->pa = 0;
	else if (map->playerstartpos == 'W')
		map->pa = 9.5;
	map->dirx = cos(map->pa) * 3;
	map->diry = sin(map->pa) * 3;
	mlx_key_hook(map->mlx, ft_key_hook, map);
	mlx_loop_hook(map->mlx, ft_loop_hook, map);
//	shoot_ray(map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] + 20, map->firstray[1], map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] - 30, map->firstray[1], map);
	//plot_line(map->cameraposx, map->cameraposy, map->firstray[0] + 30, map->firstray[1], map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	char	*map_name;
	t_map map;

	map_name = argv[1];
	ft_memset(&map, 0, sizeof(map));
	read_map(&map, map_name);
	start_window(&map);
	return (0);
}
