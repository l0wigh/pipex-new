/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:22:43 by thomathi          #+#    #+#             */
/*   Updated: 2022/04/19 12:26:15 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getenvp(char *environnement[])
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	path = NULL;
	path_array = NULL;
	while (environnement[i])
	{
		if (ft_strncmp("PATH", environnement[i], 4) == 0)
		{
			path = ft_strdup(environnement[i]);
			path = path + 5;
			path_array = ft_split(path, ':');
			return (path_array);
		}
		i++;
	}
	return (NULL);
}

char	**ft_getpath(char **environnement)
{
	char	**path_array;
	int		i;

	i = 0;
	path_array = ft_getenvp(environnement);
	while (path_array[i])
	{
		if (path_array[i][ft_strlen(path_array[i]) - 1] != '/')
			path_array[i] = ft_strjoin(path_array[i], "/");
		i++;
	}
	return (path_array);
}
