/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:45:58 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/26 16:08:06 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

const char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_APPEND)
		return ("APPEND");
	if (type == TOKEN_EOF)
		return ("EOF");
	return ("UNKNOWN");
}

char	*remove_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 1 && str[0] == '"' && str[len - 1] == '"')
	{
		str[len - 1] = '\0';
		return (str + 1);
	}
	return (str);
}
