/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:40:18 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/06 14:29:14 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_get_cmd_path(char *cmd_name, char **paths);
char	**ft_extract_paths(char **env);

void	ft_print_cmds(t_cmd *cmds)
{
	int	i;

	i = -1;
	while (cmds[++i].id)
	{
		printf("ID|=> %d\n", cmds[i].id);
		printf("NAME|=> %s\n", cmds[i].name);
		while (*cmds[i].args)
				printf(":--> %s\n", *(cmds[i].args++));
		printf("PATH|==> %s\n", cmds[i].path);
	}
}

int	ft_whos_first(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '\'' && s[i] != '"')
		;
	if (s[i])
		return ((int) s[i]);
	return (' ');
}

char	**ft_extract_args(char *cmd)
{
	char	sep;
	char	**args;
	char	*tmp;
//	int		i;

//	tmp = ft_strtrim(cmd, "./\"");
	if (!access(cmd, F_OK & X_OK))
		return (ft_split(cmd, '\0'));
	sep = (int) ft_whos_first(cmd);
	args = ft_split(cmd, sep);
	tmp = args[0];
	args[0] = ft_strtrim(tmp, " ");
	free(tmp);
	if (ft_strrchr(args[0], '/') && !ft_strchr(args[0], '.'))
	{
		tmp = args[0];
		args[0] = ft_strdup((ft_strrchr(args[0], '/') + 1));
	//	i = ft_strlen(tmp);
	//	while (tmp[--i] && !ft_strchr("/", tmp[i]))
	//		;
	//	cmds->path = ft_substr(tmp, 0, i);
		free(tmp);
	}
	return (args);
}

void	ft_clear_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i].id)
	{
//		free(cmds[i].name);
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
	char	**paths;

	paths = ft_extract_paths(env);
	cmds = (t_cmd *) malloc(sizeof(t_cmd) * ac - 2);
	if (!cmds || !paths)
		return (0);
	i = 1;
	while (++i < ac - 1)
	{
		cmds[i - 2].id = i - 1;
		cmds[i - 2].args = ft_extract_args(av[i]);
		cmds[i - 2].name = (cmds[i - 2].args)[0];
		if (!access((cmds[i - 2].args)[0], F_OK & X_OK) && ft_strchr((cmds[i - 2].args)[0], '/'))
			cmds[i - 2].path = ft_strdup((cmds[i - 2].args)[0]);
		else
			cmds[i - 2].path = ft_get_cmd_path(ft_strjoin("/", cmds[i - 2].name), paths);
		cmds[i - 2].ncmds = ac - 3;
		cmds[i - 2].infile = av[1];
		cmds[i - 2].outfile = av[ac - 1];
	}
	cmds[i - 2].id = 0;
	return (cmds);
}

char	*ft_get_cmd_path(char *cmd_name, char **paths)
{
	char	*path;

	if (!paths)
		return (0);
	while (*paths)
	{
		path = ft_strjoin(*paths, cmd_name);
		if (!access(path, F_OK & X_OK))
			return (path);
		free(path);
		paths++;
	}
	free(cmd_name);
	return (0);
}

char	**ft_extract_paths(char **env)
{
	char	*path;

	path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	while (env && *env && !ft_strnstr(*env, "PATH", 4))
		env++;
	if (env && *env)
		return (ft_split(ft_strchr(*env, '=') + 1, ':'));
	return (ft_split(path, ':'));
}
