/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:42:15 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/23 16:46:12 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

char	*find_executable(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*exec_path;

	pid = fork();
	if (pid == 0)
	{
		handle_redirections(cmd->redirs);
		exec_path = find_executable(cmd->argv[0]);
		if (!exec_path)
		{
			ft_putstr_fd("Command not found: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putchar_fd('\n', 2);
			exit(127);
		}
		execve(exec_path, cmd->argv, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

void	executor(t_cmd *cmd_list, char **envp)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		execute_cmd(cmd, envp);
		cmd = cmd->next;
	}
}
