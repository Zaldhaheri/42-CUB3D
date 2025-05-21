/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:14:52 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 15:07:26 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* 
 * Function to update the player's fov direction based on character in map
 */
static void	init_camera(char character, t_data *data)
{
	if (character == 'N')
	{
		data->plr->dir_x = 0;
		data->plr->dir_y = -1;
		data->plr->orientation = 90;
	}
	else if (character == 'S')
	{
		data->plr->dir_x = 0;
		data->plr->dir_y = 1;
		data->plr->orientation = 270;
	}
	else if (character == 'W')
	{
		data->plr->dir_x = -1;
		data->plr->dir_y = 0;
		data->plr->orientation = 180;
	}
	else if (character == 'E')
	{
		data->plr->dir_x = 1;
		data->plr->dir_y = 0;
		data->plr->orientation = 0;
	}
}

/*
 * Function to create the map from the parsed content into a 2D array.
 * Returns 0 on success or -1 on error
 */
static int	create_map(t_data *data, char **map)
{
	int		i;
	int		length;

	i = -1;
	while (map[++i])
	{
		length = ft_strlen(map[i]);
		if (length > data->map_width)
			data->map_width = length;
	}
	data->map = ft_calloc((data->map_height + 1), sizeof(char *));
	if (!data->map)
		return (printf("Error\nMalloc failed in map creation\n"), -1);
	i = -1;
	while (map[++i])
	{
		data->map[i] = malloc((data->map_width + 1) * sizeof(char));
		if (!data->map[i])
			return (free_darray(data->map),
				printf("Error\nMalloc failed in map creation\n"), -1);
		data->map[i][data->map_width] = '\0';
		ft_memset(data->map[i], 32, data->map_width);
		ft_memcpy(data->map[i], map[i], ft_strlen(map[i]));
	}
	return (0);
}

int	set_player_position(t_data *data, char dir, int x, int y)
{
	data->plr = malloc(sizeof(t_player));
	if (!data->plr)
		return (printf("Error\nMalloc failed for player\n"), -1);
	data->plr->pos_x = x + 0.5;
	data->plr->pos_y = y + 0.5;
	init_camera(dir, data);
	update_plane(data->plr);
	return (0);
}

/*
 * Function to check if the map contains valid characters, also sets the
 * player position and direction, and initializes the camera.
 * Returns 0 on success or -1 on error
 */
static int	valid_map_chars(char **content, int i, int *p_found, t_data *data)
{
	int	j;

	j = -1;
	while (content[i][++j])
	{
		if (ft_strchr("SNWE", content[i][j]))
		{
			if (*p_found == 0)
			{
				if (set_player_position(data, content[i][j], j, i) == -1)
					return (-1);
			}
			content[i][j] = '0';
			(*p_found)++;
		}
		else if (!ft_strchr("01NSEWD \t\n", content[i][j]))
		{
			printf("Error\nInvalid character '%c' at position [%d][%d].\n",
				content[i][j], i, j);
			return (-1);
		}
	}
	return (0);
}

/*
 * Function to parse the map and check for valid characters, walls, and player
 * Returns 0 on success or -1 on error
 */
int	parse_map(t_data *data, char **content, int i)
{
	int	player;

	i = -1;
	player = 0;
	while (content[data->map_height])
		data->map_height++;
	while (content[++i])
	{
		if (!content[i][0])
			return (printf("Error\nBlank line detected at line %d\n",
					data->map_height - i), -1);
		if (valid_map_chars(content, i, &player, data) == -1)
			return (-1);
	}
	if (player != 1)
		printf("Error: There must be exactly one player in the map.\n");
	if (player != 1 || create_map(data, content)
		|| check_walls(data))
		return (-1);
	return (0);
}
