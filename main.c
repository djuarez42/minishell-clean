/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/10 18:15:12 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		add_history(input);
		// Here you would typically parse the input and execute commands.
		free(input);
	}
	return (0);
}
*/

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;

	input = "ls -l | grep minishell > output.txt";
	tokens = tokenize_input(input);
	cmd = parser_tokens(tokens);
	print_token_list(tokens);
	print_cmd_list(cmd);
	free_token_list(tokens);
	free_cmds(cmd);
	return (0);
}
