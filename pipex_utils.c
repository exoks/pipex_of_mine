/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:40:18 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/26 22:36:30 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_get_cmd_path(char *cmd_name, char **env);
char	**ft_get_paths(char **env);

void	ft_print_cmds(t_cmd *cmds)
{
	int	i;

	i = -1;
	while (cmds[++i].id)
	{
		printf("ID|=> %d\n", cmds[i].id);
		while (*cmds[i].args)
				printf(":-> %s\n", *(cmds[i].args++));
		printf("PATH|==> %s\n", cmds[i].path);
	}
}

void	ft_clear_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i].id)
	{
		free(cmds[i].name);
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
	int		i;

	cmds = (t_cmd *) malloc(sizeof(t_cmd) * ac - 2);
	if (!cmds)
		return (0);
	i = 1;
	while (++i < ac - 1)
	{
		cmds[i - 2].id = i - 1;
		/*int	j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '\'')
				av[i][j] = '"';
		}*/
		if (ft_strchr(ft_strtrim(av[i], "/"), '/'))
			av[i] = ft_strrchr(ft_strtrim(av[i], "/"), '/') + 1;
		if (ft_strrchr(av[i], '\'') && !ft_strchr(av[i], '"'))
			cmds[i - 2].args = ft_split(av[i], '\'');
		else if (ft_strrchr(av[i], '"') && !ft_strchr(av[i], '\''))
			cmds[i - 2].args = ft_split(av[i], '"');
		else if (ft_strchr(av[i], '"') && ft_strchr(av[i], '\''))
		{
			cmds[i - 2].args = ft_split(av[i], '\'');
			(cmds[i - 2].args)[1] = ft_strtrim((cmds[i - 2].args)[1], "\"");
			(cmds[i - 2].args)[0] = ft_strtrim((cmds[i - 2].args)[0], "\"");
		}
		else
			cmds[i - 2].args = ft_split(av[i], ' ');
		cmds[i - 2].name = ft_strtrim((cmds[i - 2].args)[0], " ");
		cmds[i - 2].path = ft_get_cmd_path(ft_strjoin("/", cmds[i - 2].name), env);
		cmds[i - 2].ncmds = ac - 3;
		cmds[i - 2].infile = av[1];
		cmds[i - 2].outfile = av[ac - 1];
	}
	cmds[i - 2].id = 0;
	return (cmds);
}

char	*ft_get_cmd_path(char *cmd_name, char **env)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*path;

	path = 0;
	paths = ft_get_paths(env);
	if (!paths)
		exit(127);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], cmd_name);
		if (!access(tmp, F_OK | X_OK))
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
