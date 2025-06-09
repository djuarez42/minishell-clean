/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:06:07 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/06 19:21:51 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*extract_word(const char *s, int i)
{
	int	start;

	start = i;
	while (s[i] && !ft_isspace(s[i]) && !is_operator(s[i]) && !is_quote(s[i]))
		i++;
	return (ft_substr(s, start, i - start));
}

int	next_token_len(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	if (is_operator(s[i]))
		return (operator_len(s + i));
	if (is_quote(s[i]))
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			i++;
		return (i);
	}
	while (s[i] && !ft_isspace(s[i]) && !is_operator(s[i]) && !is_quote(s[i]))
		i++;
	return (i);
}

int next_token_and_len(const char *s, char **token)
{
	int	start;
	int	len;
	int	total_len;

	start = 0;
	len = 0;

	while (s[start] && ft_isspace(s[start]))
		start++;
	if (!s[start])
	{
		*token = NULL;
		return (0);
	}
	len = next_token_len(s + start);
	if (len == 0)
	{
		*token = NULL;
		return (0);
	}
	*token = ft_substr(s, start, len);
	if (!*token)
	{
		perror("malloc");
		return (0);
	}
	total_len = start + len;
	return (total_len);
}


