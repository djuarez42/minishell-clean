/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:00:07 by djuarez           #+#    #+#             */
/*   Updated: 2025/06/08 19:50:35 by djuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd   *cmds = NULL;    // Lista completa de comandos
	t_cmd   *cmd = NULL;     // Comando actual que estamos creando
	t_cmd   *last = NULL;    // Puntero al último comando de la lista
	t_token *cur = tokens;   // Puntero para recorrer tokens

	while (cur)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			free_cmds(cmds);
			return (NULL);
		}
		// parse_cmd_block consume tokens hasta pipe o EOF y llena cmd
		cur = parse_cmd_block(cur, cmd);
		if (cur && cur->type == TOKEN_PIPE)
		{
			cmd->pipe = 1;
			cur = cur->next;
		}
		// Insertar cmd en la lista cmds
		if (!cmds)
		{
			cmds = cmd;   // Primer comando
			last = cmd;
		}
		else
		{
			last->next = cmd; // Enlazamos al final
			last = cmd;       // Actualizamos último comando
		}
	}
	return cmds;
}
