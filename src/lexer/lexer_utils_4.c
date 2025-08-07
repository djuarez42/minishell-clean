/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:09:54 by djuarez           #+#    #+#             */
/*   Updated: 2025/08/06 21:26:27 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

char	*handle_quoted_part(const char *input, int *i, char *tmp)
{
	int		len;
	char	*segment;

	segment = extract_quoted_segment(&input[*i], &len);
	if (!segment)
	{
		printf("❌ extract_quoted_segment falló en i = %d\n", *i);
		*i += 1;
		return (tmp);
	}
	tmp = str_append(tmp, segment);
	free (segment);
	*i += len;
	return (tmp);
}

char	*handle_plain_text(const char *input, int *i, char *tmp)
{
	int		start;
	char	*segment;

	start = *i;
	while (input[*i] && !is_quote(input[*i]) && !ft_isspace(input[*i]))
		(*i)++;
	segment = ft_substr(input, start, *i - start);
	tmp = str_append(tmp, segment);
	free(segment);
	return (tmp);
}

void	add_token(char **tokens, int *tok_i, char **tmp)
{
	tokens[*tok_i] = *tmp;
	(*tok_i)++;
	*tmp = NULL;
}

char	**reconstruct_words(const char *input)
{
	int		i;
	int		last_i;
	char	*tmp;
	char	**tokens;
	int		tok_i;

	i = 0;
	tok_i = 0;
	tmp = NULL;
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		last_i = i;
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_quote(input[i]))
			tmp = handle_quoted_part(input, &i, tmp);
		else if (!ft_isspace(input[i]) && input[i] != '\0')
			tmp = handle_plain_text(input, &i, tmp);
		if (tmp && (ft_isspace(input[i]) || input[i] == '\0'))
		{
			if (tmp[0] != '\0')
				add_token(tokens, &tok_i, &tmp);
		}
		if (last_i == i)
			i++;
	}
	tokens[tok_i] = NULL;
	return (tokens);
}

char	**clean_input_quotes(const char *input)
{
	if (!are_quotes_closed(input))
		return (NULL);
	return (reconstruct_words(input));
}
