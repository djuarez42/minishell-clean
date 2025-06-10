/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:21:22 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/10 15:33:39 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*create_redir(t_token *cur)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = cur->type;
	redir->file = ft_strdup(cur->next->value);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

int	add_argument(t_cmd *cmd, char *value, int *argc)
{
	cmd->argv[*argc] = ft_strdup(value);
	if (!cmd->argv[*argc])
	{
		while (--(*argc) >= 0)
			free(cmd->argv[*argc]);
		free(cmd->argv);
		cmd->argv = NULL;
		return (0);
	}
	(*argc)++;
	return (1);
}

void	print_cmd_structure(t_cmd *cmd)
{
	int i;
	t_redir *redir;
	int cmd_num = 1;

	while (cmd)
	{
		printf("=== Command #%d ===\n", cmd_num++);
		
		// Mostrar los argumentos
		printf("Arguments:\n");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf("  argv[%d]: %s\n", i, cmd->argv[i]);
		}
		else
		{
			printf("  (No arguments)\n");
		}

		// Mostrar si hay pipe
		printf("Pipe after this command: %s\n", cmd->pipe ? "Yes" : "No");

		// Mostrar las redirecciones
		redir = cmd->redirs;
		if (redir)
		{
			printf("Redirections:\n");
			while (redir)
			{
				char *type = "UNKNOWN";
				if (redir->type == TOKEN_REDIRECT_OUT)
					type = "REDIRECT_OUT";
				else if (redir->type == TOKEN_REDIRECT_IN)
					type = "REDIRECT_IN";
				else if (redir->type == TOKEN_APPEND)
					type = "APPEND";
				else if (redir->type == TOKEN_HEREDOC)
					type = "HEREDOC";
				printf("  %s -> %s\n", type, redir->file);
				redir = redir->next;
			}
		}
		else
		{
			printf("Redirections: (None)\n");
		}

		printf("\n");
		cmd = cmd->next;
	}
}

