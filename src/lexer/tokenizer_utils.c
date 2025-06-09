/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:40:15 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/04 15:59:37 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	operator_len(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	token_len(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	if (is_quote(s[0]))
	{
		quote = s[0];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			i++;
	}
	else
	{
		while (s[i] && !is_operator(s[i]) && !is_quote(s[i])
			&& !ft_isspace(s[i]))
			i++;
	}
	return (i);
}

char	*next_token(const char *s)
{
	int		i;
	char	*quote_token;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (NULL);
	if (is_operator(s[i]))
	{
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<'
				&& s[i + 1] == '<'))
			return (ft_substr(s, i, 2));
		return (ft_substr(s, i, 1));
	}
	if (is_quote(s[i]))
	{
		quote_token = handle_quotes(s, i);
		return (quote_token);
	}
	return (extract_word(s, i));
}
