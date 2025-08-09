/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:21:10 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/08/09 14:21:10 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int is_n_flag(const char *s)
{
    size_t i;

    if (!s || s[0] != '-' || s[1] != 'n')
        return (0);
    i = 2;
    while (s[i] == 'n')
        i++;
    return (s[i] == '\0');
}

int is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    return (!ft_strncmp(cmd, "echo", 5) ||
            !ft_strncmp(cmd, "cd", 3) ||
            !ft_strncmp(cmd, "pwd", 4) ||
            !ft_strncmp(cmd, "export", 7) ||
            !ft_strncmp(cmd, "unset", 6) ||
            !ft_strncmp(cmd, "env", 4) ||
            !ft_strncmp(cmd, "exit", 5));
}

int bi_echo(char **argv)
{
    int i;
    int n_flag;

    i = 1;
    n_flag = 0;
    while (argv[i] && is_n_flag(argv[i]))
    {
        n_flag = 1;
        i++;
    }
    while (argv[i])
    {
        write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
        if (argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}

int bi_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
    return (0);
}

int bi_env(char **envp)
{
    int i;

    if (!envp)
        return (0);
    i = 0;
    while (envp[i])
    {
        ft_putendl_fd(envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

int bi_cd(char **argv, char **envp)
{
    (void)envp;
    if (!argv[1])
    {
        ft_putendl_fd("minishell: cd: missing operand", STDERR_FILENO);
        return (1);
    }
    if (chdir(argv[1]) == -1)
    {
        perror("cd");
        return (1);
    }
    // TODO: update PWD/OLDPWD in envp state
    return (0);
}

int bi_export(char **argv, char **envp)
{
    (void)argv;
    (void)envp;
    // TODO: implement environment modifications and printing (no options)
    return (0);
}

int bi_unset(char **argv, char **envp)
{
    (void)argv;
    (void)envp;
    // TODO: implement removing variables from environment
    return (0);
}

int bi_exit(char **argv)
{
    int status;

    status = 0;
    if (argv[1])
        status = ft_atoi(argv[1]);
    // In child, caller will exit(status). In parent, run_builtin_in_parent will exit.
    return (status & 0xFF);
}

static int dispatch_builtin(char **argv, char **envp)
{
    if (!ft_strncmp(argv[0], "echo", 5))
        return bi_echo(argv);
    if (!ft_strncmp(argv[0], "pwd", 4))
        return bi_pwd();
    if (!ft_strncmp(argv[0], "env", 4))
        return bi_env(envp);
    if (!ft_strncmp(argv[0], "cd", 3))
        return bi_cd(argv, envp);
    if (!ft_strncmp(argv[0], "export", 7))
        return bi_export(argv, envp);
    if (!ft_strncmp(argv[0], "unset", 6))
        return bi_unset(argv, envp);
    if (!ft_strncmp(argv[0], "exit", 5))
        return bi_exit(argv);
    return (1);
}

int run_builtin_in_child(t_cmd *cmd, char **envp)
{
    return dispatch_builtin(cmd->argv, envp);
}

int run_builtin_in_parent(t_cmd *cmd, char **envp)
{
    int status;

    status = dispatch_builtin(cmd->argv, envp);
    if (!ft_strncmp(cmd->argv[0], "exit", 5))
        exit(status);
    return status;
}
