/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:23:23 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/23 19:40:36 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <sys/types.h>
# include <sys/wait.h>

//Functions
void	execute_cmds(t_cmd *cmd, char **envp);
void	executor(t_cmd *cmd_list, char **envp);
//Utils
void	free_split(char **split);
char	*ft_strjoin_free(char *s1, char *s2);
char	**new_envp(char **envp);
void	free_envp(char **envp_copy);
void	handle_redirections_out(const char *filename);
void	handle_redirections_in(const char *filename);
void	handle_redirections_append(const char *filename);
void	handle_redirections(t_redir *redir);

#endif