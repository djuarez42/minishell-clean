/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:30:46 by djuarez           #+#    #+#             */
/*   Updated: 2025/08/06 17:23:54 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*tests[] = {
		"echo hola mundo",
		"   ls   -la   ",
		"cat    archivo.txt",
		"grep    'hola mundo' archivo.txt",
		"echo\"hola\"",
		"\"quoted\"text",
		"\"\"echo\"\" hola",
		"\"ec\"\"ho\" \"ho\"la",
		"   ",
		"",
		NULL
	};
	int		i;
	char	**tokens;
	int		j;

	for (i = 0; tests[i]; i++)
	{
		printf("\n📥 Test %d: [%s]\n", i + 1, tests[i]);
		tokens = reconstruct_words(tests[i]);
		if (!tokens)
		{
			printf("❌ reconstruct_words devolvió NULL\n");
			continue;
		}
		for (j = 0; tokens[j]; j++)
			printf("🔹 Token %d: [%s]\n", j, tokens[j]);
		// liberar memoria
		for (j = 0; tokens[j]; j++)
			free(tokens[j]);
		free(tokens);
	}
	return (0);
}
