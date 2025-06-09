/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:37:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/09 19:32:16 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		add_history(input);
		// Here you would typically parse the input and execute commands.
		free(input);
	}
	return (0);
}
*/

#include "minishell.h"

