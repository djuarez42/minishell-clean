/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:09:54 by djuarez           #+#    #+#             */
/*   Updated: 2025/07/31 20:51:39 by djuarez          ###   ########.fr       */
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
	int		i = 0;
	int		last_i;
	char	*tmp = NULL;
	char	**tokens = malloc(sizeof(char *) * 1024);
	int		tok_i = 0;

	if (!tokens)
		return (NULL);

	while (input[i])
	{
		last_i = i;
		printf("\n🔎 Loop: i = %d, char = '%c'\n", i, input[i]);

		// Saltar espacios
		i = skip_spaces(input, i);
		printf("⏩ Después de skip_spaces, i = %d, char = '%c'\n", i, input[i]);

		if (!input[i])
		{
			printf("🚪 Fin del input tras skip_spaces, break\n");
			break;
		}

		if (is_quote(input[i]))
		{
			printf("🟨 Entrando a handle_quoted_part (char = %c)\n", input[i]);
			tmp = handle_quoted_part(input, &i, tmp);
			printf("✅ tmp = [%s], i = %d\n", tmp ? tmp : "NULL", i);
		}
		else if (!ft_isspace(input[i]) && input[i] != '\0')
		{
			printf("🟦 Entrando a handle_plain_text (char = %c)\n", input[i]);
			tmp = handle_plain_text(input, &i, tmp);
			printf("✅ tmp = [%s], i = %d\n", tmp ? tmp : "NULL", i);
		}
		else
		{
			printf("🔁 Ningún caso aplicó, i++\n");
			i++;
			continue;
		}

		// Condición para guardar token incluso si no hay espacio
		if (tmp)
		{
			printf("🔎 Verificando si guardar token...\n");
			printf("   input[i] = %c (%d)\n", input[i], input[i]);
			if (input[i] == '\0')
				printf("   input[i] == '\\0'\n");
			if (ft_isspace(input[i]))
				printf("   input[i] es espacio\n");
			if (is_quote(input[i]))
				printf("   input[i] es comilla\n");
		}

		if (tmp && (!input[i] || ft_isspace(input[i]) || is_quote(input[i])))
		{		
			printf("🟢 Guardando token: [%s]\n", tmp);
			add_token(tokens, &tok_i, &tmp);
			i = skip_spaces(input, i);  // ← ¡AVANZA DESPUÉS DE GUARDAR!
		}

		if (last_i == i)
		{
			printf("⚠️ i no avanzó (last_i = %d, i = %d), forzando i++\n", last_i, i);
			i++;
		}
		else
		{
			printf("✅ i avanzó correctamente (de %d a %d)\n", last_i, i);
		}
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

