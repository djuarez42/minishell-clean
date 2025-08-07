/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:30:46 by djuarez           #+#    #+#             */
/*   Updated: 2025/08/06 20:51:42 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char *tests[] = {
		"echo hola mundo",
		"   ls   -la   ",
		"cat    archivo.txt",
		"grep    'hola mundo' archivo.txt",
		"echo\"hola\"",
		"\"quoted\"text",
		"\"\"echo\"\" hola",
		"\"ec\"\"ho\" \"ho\"la",
		"   ",
		"",
		"echo hola > out.txt",
		"ls -l | grep mini",
		"cat < infile.txt > outfile.txt",
		"echo hey >> log.txt",
		"cat << EOF",
		NULL
	};
	for (int i = 0; tests[i]; i++)
	{
		printf("\n🔹 TEST %d: [%s]\n", i + 1, tests[i]);
		char *input = ft_strdup(tests[i]);
		if (!input)
			continue ;
		t_token *tokens = tokenize_input(input);
		if (!tokens)
		{
			printf("Lexer returned NULL\n");
			free(input);
			continue ;
		}
		t_cmd *cmd_list = parser_tokens(tokens);
		if (!cmd_list)
		{
			printf("Parser returned NULL\n");
			free_token_list(tokens);
			free(input);
			continue ;
		}
		print_cmd_list(cmd_list);
		free_cmds(cmd_list);
		free_token_list(tokens);
		free(input);
	}
	return (0);
}
