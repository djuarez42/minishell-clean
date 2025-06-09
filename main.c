/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/09 19:37:14 by djuarez          ###   ########.fr       */
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
#include <stdio.h>
#include <stdlib.h>

// Función para imprimir los comandos parseados (debug)
void print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("Command:\n");

		// Imprimir argumentos
		if (cmds->argv)
		{
			printf("  argv: ");
			for (int i = 0; cmds->argv[i]; i++)
				printf("'%s' ", cmds->argv[i]);
			printf("\n");
		}
		else
			printf("  argv: (null)\n");

		// Imprimir redirecciones
		t_redir *r = cmds->redirs;
		while (r)
		{
			printf("  redir type: %d, file: %s\n", r->type, r->file);
			r = r->next;
		}

		// Imprimir si hay pipe
		if (cmds->pipe)
			printf("  pipe: yes\n");
		else
			printf("  pipe: no\n");

		cmds = cmds->next;
	}
}

int main(void)
{
	char *input = "echo hola > out.txt | cat < in.txt";

	// 1. Lexing
	t_token *tokens = lexer(input);
	if (!tokens)
	{
		printf("Lexer failed.\n");
		return (1);
	}

	// 2. Parsing
	t_cmd *cmds = parser_tokens(tokens);
	if (!cmds)
	{
		printf("Parser failed.\n");
		free_tokens(tokens); // Si tienes esta función
		return (1);
	}

	// 3. Imprimir resultado
	print_cmds(cmds);

	// 4. Liberar memoria
	free_tokens(tokens); // si tienes
	free_cmds(cmds);     // si tienes

	return (0);
}
