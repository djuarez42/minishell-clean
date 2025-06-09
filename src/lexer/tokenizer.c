/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:20:01 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/07 16:04:10 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	**tokenize_input(const char *input)
{
	char	**tokens;
	int		count;
	int		j;

	if (!input)
		return (NULL);
	count = count_tokens(input);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	j = 0;
	while (j < count + 1)
		tokens[j++] = NULL;
	if (!fill_tokens(input, tokens))
	{
		free_tokens(tokens, count);
		return (NULL);
	}
	return (tokens);
}

