/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:27:03 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/21 16:59:01 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
* parse() function:
* 1. Extracts the content of the file.
* 2. Validates the content.
* 3. Sets the textures and colors.
* 4. Finds the start of the map.
* 5. Parses the map.
* 6. Cleans up and returns success or failure.
*/
int	parse(char *path, t_data *data)
{
	char	**content;
	int		index;

	content = extract_f(path);
	if (content == NULL)
		return (printf("Error\nThe file wasn't found.\n"), -1);
	if (validate_content(content) < 0
		|| texture_n_colors(data, content) < 0)
		return (free_darray(content), -1);
	index = find_start(content);
	if (index == -1)
		printf("Error\nNo valid map found in the file.\n");
	if (index == -1 || parse_map(data, content + index, index) == -1)
		return (free_all(data), free_darray(content), -1);
	free_darray(content);
	return (0);
}
