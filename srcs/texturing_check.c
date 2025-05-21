/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:20:32 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 15:28:51 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
 * Function that sets the color in .cub to the data struct variable
 * Returns the count of occurrences
 */
static int	set_color(t_data *data, char *texture)
{
	char	**split_string;
	char	**split_color;
	int		total;
	int		count;

	total = 0;
	count = count_chars(texture, ',');
	split_color = color_split(texture);
	if (count != 2)
		return (free_darray(split_color), 0);
	if (!split_color || !split_color[0] || !split_color[1] || !split_color[2]
		|| split_color[3])
		return (printf("Error\nInvalid color iden\n"), 0);
	split_string = ft_split(texture, ' ');
	if (ft_strcmp(split_string[0], "F") == 0)
		total = use_atoi(data, split_color, 'F');
	else if (ft_strcmp(split_string[0], "C") == 0)
		total = use_atoi(data, split_color, 'C');
	else
		total = printf("Error\nUnknown color iden\n") - 31;
	free_darray(split_string);
	return (free_darray(split_color), total);
}

/*
 * Function to initialize/set the xpm to a image pointer
 * Returns 0 on success or -1 on error
 */
static int	initialise_textures(char *file, t_data *mlx,
	unsigned int texture[TEX_SIZE][TEX_SIZE])
{
	(void) file;
	(void) mlx;
	(void) texture;
	// void	*img_ptr;
	// char	*add;
	// int		stuff[3];
	// int		index;
	// int		jindex;

	// if (ft_strncmp(file + ft_strlen(file) - 4, ".xpm", 5))
	// 	return (printf("Error\nInvalid texture file extension.\n"), -1);
	// // img_ptr = NULL;
	// // img_ptr = mlx_xpm_file_to_image(mlx->mlx, file, stuff + 1, stuff + 2);
	// // if (!img_ptr)
	// // 	return (-1);
	// // add = mlx_get_data_addr(img_ptr, stuff, stuff + 1, stuff + 2);
	// index = -1;
	// // while (++index < TEX_SIZE)
	// // {
	// // 	jindex = -1;
	// // 	while (++jindex < TEX_SIZE)
	// // 		texture[jindex][index] = *(unsigned int *)(add + index
	// // 				* stuff[1] + jindex * (stuff[0] / 8));
	// // }
	// // mlx_destroy_image(mlx->mlx, img_ptr);
	return (0);
}

/*
 * Function to check what texture to set
 * Returns 0 on success or -1 on error
 */
int	set_texture(t_data *data, char **split)
{
	char	*path;

	if ((!split[1] || split[2]) && (!ft_strncmp(split[0], "NO", 3)
			|| !ft_strncmp(split[0], "SO", 3) || !ft_strncmp(split[0], "WE", 3)
			|| !ft_strncmp(split[0], "EA", 3)))
		return (-1);
	path = split[1];
	if (!ft_strncmp(split[0], "NO", 3))
		return (initialise_textures(path, data, data->textures.north));
	else if (!ft_strncmp(split[0], "SO", 3))
		return (initialise_textures(path, data, data->textures.south));
	else if (!ft_strncmp(split[0], "WE", 3))
		return (initialise_textures(path, data, data->textures.west));
	else if (!ft_strncmp(split[0], "EA", 3))
		return (initialise_textures(path, data, data->textures.east));
	return (0);
}

/*
 * Function to handle setting the textures and colors
 * Returns 0 on success or -1 on error
 */
int	texture_n_colors(t_data *data, char **f_data)
{
	int		index;
	char	**split;

	index = -1;
	split = NULL;
	while (f_data[++index])
	{
		free_darray(split);
		ft_revtrim(f_data[index], " \t\n");
		split = ft_split(f_data[index], ' ');
		if (!split || !split[0])
			continue ;
		if (set_texture(data, split) == -1)
			(printf("Error\nFailed to set texture: %s\n", split[0]),
				free_darray(split), free(data->mlx), free_darray(f_data), free_all(data), exit(1));
		if ((!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
			&& !set_color(data, f_data[index]))
			(printf("Error\nFailed to set color: %s\n", split[0]),
				free_darray(split), free(data->mlx), free_darray(f_data), free_all(data), exit(1));
	}
	return (free_darray(split), 0);
}
