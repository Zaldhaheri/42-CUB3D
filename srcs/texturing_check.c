#include "../include/cub3d.h"

int	init_textures(char *file, t_data *game, unsigned int texture[64][64])
{
	void	*image;
	char	*address;
	int		info[3];
	int		index;
	int		jindex;

	if (ft_strncmp(file + ft_strlen(file) - 4, ".xpm", 5))
		return (write(1, "Error: Texture extension should be '.xpm'.\n", 44),
			0);
	image = NULL;
	image = game_xpm_file_to_image(game->mlx, file, info + 1, info + 2);
	if (!image)
		return (0);
	address = mlx_get_data_addr(image, info, info + 1, info + 2);
	index = -1;
	while (++index < 64)
	{
		jindex = -1;
		while (++jindex < 64)
			texture[jindex][index] = *(unsigned int *)(address + index * info[1]
					+ jindex * (info[0] / 8));
	}
	mlx_destroy_image(game->mlx, image);
	return (1);
}

int	setting_textures(t_data *game, char **part)
{
	char	*path;

	if ((!part[1] || part[2]) && (!ft_strncmp(part[0], "NO", 3)
			|| !ft_strncmp(part[0], "SO", 3) || !ft_strncmp(part[0], "WE", 3)
			|| !ft_strncmp(part[0], "EA", 3)))
		return (0);
	path = part[1];
	if (!ft_strncmp(part[0], "NO", 3))
		return (init_textures(path, &game, game->parsing->so));
	else if (!ft_strncmp(part[0], "SO", 3))
		return (init_textures(path, &game, game->parsing->no));
	else if (!ft_strncmp(part[0], "WE", 3))
		return (init_textures(path, &game, game->parsing->we));
	else if (!ft_strncmp(part[0], "EA", 3))
		return (init_textures(path, &game, game->parsing->ea));
	return (1);
}

int	color_and_texture(t_data *game, char **content)
{
	int index;
	char **part;

	index = -1;
	part = NULL;
	while (content[++index])
	{
		free_darray(part);
		trim_end(content[index], " \t\n");
		part = ft_split(content[index], ' ');
		if (!part || !part[0])
			continue ;
		if (!setting_textures(game, part))
			return (free_darray(part), 0);
		if ((string_compare(part[0], "F") || string_compare(part[0], "C"))
			&& !setting_color(game, part))
			return (free_darray(part), 0);
	}
	free_darray(part);
	return (1);
}