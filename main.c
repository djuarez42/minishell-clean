/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/21 16:48:57 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;

	input = "ls -l";
	tokens = tokenize_input(input);
	cmd = parser_tokens(tokens);
	if (cmd)
		executor(cmd, envp);
	//print_token_list(tokens);
	//print_cmd_list(cmd);
	//executor(cmd, envp);
	free_token_list(tokens);
	free_cmds(cmd);
	return (0);
}
