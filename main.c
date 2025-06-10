/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/10 15:52:17 by djuarez          ###   ########.fr       */
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
#include "lexer.h"
#include "parser.h"

// Función para imprimir los comandos parseados (debug)
void print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("Command:\n");
		if (cmds->argv)
		{
			printf("  argv: ");
			for (int i = 0; cmds->argv[i]; i++)
				printf("'%s' ", cmds->argv[i]);
			printf("\n");
		}
		else
			printf("  argv: (null)\n");
		t_redir *r = cmds->redirs;
		while (r)
		{
			printf("  redir type: %d, file: %s\n", r->type, r->file);
			r = r->next;
		}
		if (cmds->pipe)
			printf("  pipe: yes\n");
		else
			printf("  pipe: no\n");
		cmds = cmds->next;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		input = "echo hola | grep mundo > file.txt";
		if (!input)
			break ;
		tokens = tokenize_input(input);
		if (!tokens)
		{
			fprintf(stderr, "Error: failed to tokenize input\n");
			free(input);
			continue ;
		}
		print_token_list(tokens);
		cmds = parser_tokens(tokens);
		print_cmd_structure(cmds);
		if (!cmds)
		{
			fprintf(stderr, "Error: failed to parse tokens\n");
			free_token_list(tokens);
			free(input);
			continue ;
		}
		free_token_list(tokens);
		//free_cmds(cmds);
		free(input);
	}
	return (0);
}
