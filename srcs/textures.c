/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:36:37 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/12 15:18:50 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_textu(t_map *map)
{
	map->background_txt = mlx_load_png("textures/background.png");
	//if (map->background_txt == NULL)
	//	ft_error_mlx(map);
	map->background = mlx_texture_to_image(map->mlx, map->background_txt);
	//if (map->background == NULL)
	//	ft_error_mlx(map);
	mlx_delete_texture(map->background_txt);
	map->player_txt = mlx_load_png("textures/ground.png");
	//if (map->player_txt == NULL)
	//	ft_error_mlx(map);
	map->wall.txt[0] = mlx_load_png("textures/wall.png");
	//if (map->player_txt == NULL)
	//	ft_error_mlx(map);
}
