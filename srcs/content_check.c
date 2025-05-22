/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:12:40 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 16:02:01 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
 * Function to set a flag in the flags array
 * Returns 0 on success or -1 on error
 */
static int	set_flag(bool *flag, char *identifier)
{
	if (*flag)
		return (printf("Error\nDuplicate '%s'\n", identifier), -1);
	*flag = 1;
	return (0);
}

/*
 * Function to check for missing flags in the file
 * Returns 0 on success or -1 on error
 */
static int	check_missing_flags(bool *flags)
{
	const char	*characters[6];
	int			index;

	characters[0] = "NO";
	characters[1] = "SO";
	characters[2] = "WE";
	characters[3] = "EA";
	characters[4] = "F";
	characters[5] = "C";
	index = 0;
	while (index < 6 && flags[index])
		index++;
	if (index != 6)
		return (printf("Error\nMissing '%s'\n", characters[index]), -1);
	return (0);
}

/*
 * Function to check for duplicate flags in the file
 * Returns 0 on success or -1 on error
 */
static int	check_flags(char *line, bool *flags)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
		return (set_flag(flags, "NO"));
	else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
		return (set_flag(flags + 1, "SO"));
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
		return (set_flag(flags + 2, "WE"));
	else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
		return (set_flag(flags + 3, "EA"));
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (set_flag(flags + 4, "F"));
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (set_flag(flags + 5, "C"));
	return (0);
}

/*
 * Function to validate the content of the file
 * Checks for duplicate flags and missing flags
 * Returns 0 on success or -1 on error
 */
int	validate_content(char **f_data)
{
	int		index;
	bool	flags[6];
	char	*t_line;

	index = -1;
	if (f_data[0] == NULL)
		return (printf("Error\nEmpty file.\n"), -1);
	ft_memset(flags, 0, sizeof(flags));
	while (f_data[++index])
	{
		t_line = ft_strtrim(f_data[index], " \t\n");
		if (!t_line)
			continue ;
		if (t_line[0] && check_flags(t_line, flags) < 0)
			return (free(t_line), -1);
		free(t_line);
	}
	if (check_missing_flags(flags) == -1)
		return (-1);
	return (0);
}
