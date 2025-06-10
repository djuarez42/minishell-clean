/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:20:01 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/10 15:00:05 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_token	*tokenize_input(const char *input)
{
	char	**raw_tokens;
	t_token	*token_list;
	int		count;
	int		j;

	if (!input)
		return (NULL);
	count = count_tokens(input);
	raw_tokens = malloc(sizeof(char *) * count + 1);
	if (!raw_tokens)
		return (NULL);
	j = 0;
	while (j < count + 1)
		raw_tokens[j++] = NULL;
	if (!fill_tokens(input, raw_tokens))
	{
		free_tokens(raw_tokens, count);
		return (NULL);
	}
	token_list = build_token_list(raw_tokens);
	free_tokens(raw_tokens, count);
	return (token_list);
}


