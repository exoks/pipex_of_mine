/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:40:18 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/24 21:45:03 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_get_cmd_path(char *cmd_name, char **env);
char	**ft_get_paths(char **env);

void	ft_clear_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i].id)
	{
		free(cmds[i].path);
		j = -1;
		while((cmds[i].args)[++j])
			free((cmds[i].args)[j]);
		free(cmds[i].args);
	}
	free(cmds);
}

t_cmd	*ft_extract_cmds(int ac, char **av, char **env)
{
	t_cmd   *cmds;
	int             i;

	cmds = (t_cmd *) malloc(sizeof(t_cmd) * ac - 2);
	if (!cmds)
		return (0);
	i = 1;
	while (++i < ac - 1)
	{
		cmds[i - 2].id = i - 1;
		cmds[i - 2].args = ft_split(av[i], ' ');
		cmds[i - 2].path = ft_get_cmd_path(ft_strjoin("/", (cmds[i - 2].args)[0]), env);
		cmds[i - 2].ncmds = ac - 3;
	}
	cmds[i - 2].id = 0;
	return (cmds);
}

char	*ft_get_cmd_path(char *cmd_name, char **env)
{
	int	i;
	char	*tmp;
	char	**paths;
	char	*path;

	path = 0;
	paths = ft_get_paths(env);
	if (!paths)
		write(2, "PATH NOT FOUND \n", 16);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], cmd_name);
		if (!access(tmp, F_OK))
			path = ft_strjoin(paths[i], cmd_name);
		free(tmp);
		free(paths[i]);
	}
	free(cmd_name);
	free(paths);
	return (path);
}

char	**ft_get_paths(char **env)
{
	while (*env && !ft_strnstr(*env, "PATH", 4))
		env++;
	if (*env)
		return (ft_split(ft_strchr(*env, '/'), ':'));
	return (0);
}
