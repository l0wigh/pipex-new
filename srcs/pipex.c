/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:08:01 by thomathi          #+#    #+#             */
/*   Updated: 2022/06/05 17:52:41 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Si tu lis ça, sache que je déteste pipex
// Même si en vrai c'était sympa à coder
// Mais Fuck Pipex quand même

#include "pipex.h"
#include <unistd.h>

char	*prepare_exec(char *environnement[], char arguments[])
{
	char	**chemin;
	char	*access_test;
	int		i;

	chemin = ft_getpath(environnement);
	i = 0;
	while (chemin[i])
	{
		access_test = ft_strjoin(chemin[i], arguments);
		if (access(access_test, F_OK) == 0)
		{
			arguments = ft_strjoin(chemin[i], arguments);
			return (arguments);
		}
		i++;
	}
	return (NULL);
}

void	first_pid(int *fd, char *file, char *commande, char *chemin)
{
	int		file_open;
	char	**arguments;

	file_open = open(file, O_RDONLY);
	dup2(file_open, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_open);
	arguments = ft_split(commande, ' ');
	execve(chemin, arguments, NULL);
	close(fd[0]);
	close(fd[1]);
	close(file_open);
	return ;
}

void	second_pid(int *fd, char *file, char *commande, char *chemin)
{
	int		file_open;
	char	**arguments;

	file_open = open(file, O_CREAT | O_WRONLY, 0644);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_open, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_open);
	arguments = ft_split(commande, ' ');
	execve(chemin, arguments, NULL);
	close(fd[0]);
	close(fd[1]);
	close(file_open);
	return ;
}

void	split_pour_norminette(char *envp[], char *argv[], pid_t pid1, int *fd)
{
	pid_t	pid2;
	char	*chemin;
	char	**arguments;

	pid2 = fork();
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		arguments = ft_split(argv[3], ' ');
		chemin = prepare_exec(envp, arguments[0]);
		if (!chemin)
			return ;
		second_pid(fd, argv[4], argv[3], chemin);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		fd_isopen;
	pid_t	pid1;
	char	*chemin;
	char	**arguments;

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
		arguments = ft_split(argv[2], ' ');
		chemin = prepare_exec(envp, arguments[0]);
		if (!chemin)
			return (1);
		first_pid(fd, argv[1], argv[2], chemin);
	}
	else
		split_pour_norminette(envp, argv, pid1, fd);
	return (0);
}
