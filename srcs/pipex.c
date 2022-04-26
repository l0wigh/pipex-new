/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:08:01 by thomathi          #+#    #+#             */
/*   Updated: 2022/04/26 00:51:43 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// If you read this, keep in mind that, I hate/love pipex !

#include "pipex.h"

// TODO: Ajouter l'argv[1] pour l'open
// TODO: Ajouter le fichier open dans le dup
void	first_pid(int *fd)
{
	char	**arguments;
	char	*chemin;

	// arguments = ft_split(argv[2]);
	// chemin = prepare_exec(envp, arguments);
	// if (!chemin)
	//		return (1);
	return;
}

// TODO: Ajouter l'argv[4] pour l'open
// TODO: Créer le fichier si l'open fonctionne pas
void	second_pid(int *fd)
{
	char	**arguments;
	char	*chemin;

	// arguments = ft_split(argv[3]);
	// chemin = prepare_exec(envp, arguments);
	// if (!chemin)
	//		return (1);
	return;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		*fd;
	int		fd_isopen;
	pid_t	pid1;
	pid_t	pid2;

	if (argc < 5)
		return (1);
	fd_isopen = pipe(fd);
	if (fd_isopen == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		first_pid(fd);
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (1);
		if (pid2 == 0)
		{
			second_pid(fd);
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (0);
}
