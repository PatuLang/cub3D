/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:26:52 by plang             #+#    #+#             */
/*   Updated: 2024/08/19 14:02:00 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

void	rgb_free(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

uint32_t	bitshift_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_int_of_rgb(t_fcheck *check, char **surface)
{
	int	i;
	int	j;

	i = 0;
	while (surface[i] != NULL)
	{
		j = 0;
		clean_from_space_nl(&surface[i]);
		while (surface[i][j] != '\0')
		{
			if (ft_isdigit((int)surface[i][j]) == 0)
				check->error = 1;
			j++;
		}
		if (ft_atoi(surface[i]) < 0 || ft_atoi(surface[i]) > 255)
			check->error = 1;
		if (i++ > 2)
			check->error = 1;
		if (check->error == 1)
			return (-1);
	}
	return (0);
}

void	check_rgb_floor(t_fcheck *check)
{
	char	**floor;
	char	*temp;
	int		tempnum;

	floor = NULL;
	temp = check->ground;
	while (*temp != ' ')
		temp++;
	floor = ft_split(temp, ',');
	if (!floor)
		error_inside_file(check, MALLOCFAIL);
	tempnum = check_int_of_rgb(check, floor);
	if (tempnum == 0)
	{
		check->bottom = bitshift_rgba(ft_atoi(floor[0]), ft_atoi(floor[1]), \
		ft_atoi(floor[2]), 210);
	}
	else
		check->error = 1;
	rgb_free(floor);
}

void	check_rgb_ceiling(t_fcheck *check)
{
	char	**ceiling;
	char	*temp;
	int		tempnum;

	ceiling = NULL;
	temp = check->sky;
	while (*temp != ' ')
		temp++;
	ceiling = ft_split(temp, ',');
	if (!ceiling)
		error_inside_file(check, MALLOCFAIL);
	tempnum = check_int_of_rgb(check, ceiling);
	if (tempnum == 0)
	{
		check->top = bitshift_rgba(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]), \
		ft_atoi(ceiling[2]), 210);
	}
	else
		check->error = 1;
	rgb_free(ceiling);
}
