/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:03:33 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/24 17:20:44 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_blank(const char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

int	count_tokens(const char *s)
{
	int		count;
	int		len;
	char	*token;

	count = 0;
	len = 0;
	token = NULL;
	while (*s)
	{
		len = next_token_and_len(s, &token);
		if (len == 0)
			break ;
		free(token);
		s += len;
		count++;
	}
	return (count);
}


void	free_tokens(char **tokens, int max)
{
	int	i;

	i = 0;
	while (i < max && tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}

int	fill_tokens(const char *input, char **tokens)
{
	int		i;
	int		len;
	char	*token;

	i = 0;
	while (*input)
	{
		len = next_token_and_len(input, &token);
		if (len == 0)
			break ;
		tokens[i] = token;
		input += len;
		i++;
	}
	tokens[i] = NULL;
	return (1);
}

char	*handle_quotes(const char *s, int i)
{
	char	quote;
	int		start;
	int		end;

	quote = s[i++];
	start = i;
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		return (NULL);
	end = i;
	//i++;
	return (ft_substr(s, start, i - start));
}