/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:20:01 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/31 20:50:42 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_token	*tokenize_input(const char *input)
{
	char	**tokens;
	t_token	*token_list;
	
	if (!input)
		return (NULL);
	tokens = clean_input_quotes(input);
	if (!tokens)
		return (NULL);
	token_list = build_token_list(tokens);
	free_tokens(tokens, -1);
	print_token_list(token_list);
	return (token_list);
}