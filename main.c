/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/07 16:55:10 by djuarez          ###   ########.fr       */
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
	char	**raw_tokens;
	t_token	*token_list;

	while (1)
	{
		input = "echo \"Hola mundo\" | ls -la > archivo.txt";
		if (!input || *input == '\0')
			break ;
		raw_tokens = tokenize_input(input);
		if (!raw_tokens)
		{
			printf("Error; failed to tokenize input.\n");
			continue ;
		}
		token_list = build_token_list(raw_tokens);
		print_token_list(token_list);
		free_tokens(raw_tokens, count_tokens(input));
		free_token_list(token_list);
		break ;
	}
	return (0);
}
