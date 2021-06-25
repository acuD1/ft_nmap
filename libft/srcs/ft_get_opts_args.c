/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opts_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:29:09 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 17:59:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	+--------+---------+---------+------------------------------------------+
**	| a - z  |  A - Z  |  0 - 9  |             unallowed option             |
**	+--------+---------+---------+------------------------------------------+
**	| 0 - 25 | 26 - 51 | 52 - 61 | 63. return % 128 to get unallowed option |
**	+--------+---------+---------+------------------------------------------+
**	"-c" option = [00000000 00000100]
**	use (option & (1ULL << 3)) to catch
**
**
*/

static void          usage(void)
{
    dprintf(STDERR_FILENO, "%s%s%s%s%s%s",
        "\nUsage: ft_get_ops_args(): ",
        "struct s_opts_conf must be properly configured.\n\n",
        "typedef struct\t\ts_opts_conf\n{\n",
        "\tconst char\t*allowed_opt;\t\t('-')\t\t| Minimal configuration !\n",
        "\tconst char\t*allowed_opt_arg;\t('-' + arg)\n"
        "\tconst char\t**allowed_opt_tab;\t('--')\n",
        "\tconst char\t**allowed_opt_tab_arg;\t('--' + arg)\n}\t\t\tt_opts_conf;\n\n");
}

/* debug function */
void                debug_opts_args(t_opts_args *opts_args)
{
    if (!opts_args)
    {
        printf("WARNING : opt no allocated\n");
        return ;
    }
    printf("%s\n\n%s\n\t\t%s\n%s\n",
        ">> OPTS_ARGS DEBUG",
        "=>  invalid: ", opts_args->invalid, "=>  args:");
    if (opts_args->args)
    {
        t_list   *tmp    = opts_args->args;

        while (tmp)
        {
            printf("\t\t- [%d] | %s\n", ((t_args_db *)tmp->data)->argc, ((t_args_db *)tmp->data)->arg);
            tmp = tmp->next;
        }

    }
    else
        printf("\t\t(null)\n");
    printf("=>  opt_set:\n");
    if (opts_args->opt_set)
    {
        t_list   *tmp    = opts_args->opt_set;
        size_t  i       = 0;

        while (tmp)
        {
            printf(
                "\t\t- [%zu] | current -> %s\n\t\t      | arg \t-> %s\n",
                i++, ((t_opt_set_db *)tmp->data)->current,
                ((t_opt_set_db *)tmp->data)->arg);
            tmp = tmp->next;
        }
    }
    else
        printf("\t\t(null)\n");
}

/* get arg with his position */
t_args_db             *get_arg(t_list **alist_args, int argc)
{
    t_list  *args    = *alist_args;
    size_t  i        = 1;

    if (!args)
        return (NULL);
    while (i < (size_t)argc)
    {
        if (!args)
            return (NULL);
        args = args->next;
        i++;
    }
    if (args)
        return ((t_args_db *)args->data);
    return (NULL);
}

static uint8_t       find_opt_set_db(void *current, void *to_find)
{
    t_opt_set_db    *tmp_current = current;
    char            *tmp_to_find = to_find;

    return (ft_strequ(tmp_current->current, tmp_to_find));
}

/* get data from an opt_set including his name, argument and his position */
t_opt_set_db        *get_opt_set_db(t_list **alist_opt_set, char *to_find)
{
    t_list  *opt_set    = *alist_opt_set;
    t_list  *tmp        = NULL;

    if (!opt_set)
        return (NULL);
    if ((tmp = ft_lstfind(opt_set, to_find, (int (*)(void*, void*))find_opt_set_db)))
        return ((t_opt_set_db *)tmp->data);
    return (NULL);
}

void                free_opts_args(t_opts_args *opts_args)
{
    if (!opts_args)
        return ;
    while (opts_args->opt_set)
    {
        t_list   *tmp = NULL;

        ft_strdel(&((t_opt_set_db*)(opts_args->opt_set->data))->current);
        ft_strdel(&((t_opt_set_db*)(opts_args->opt_set->data))->arg);
        free(opts_args->opt_set->data);
        tmp = opts_args->opt_set;
        opts_args->opt_set = opts_args->opt_set->next;
        free(tmp);
    }
    while (opts_args->args)
    {
        t_list   *tmp = NULL;

        ft_strdel(&((t_args_db*)(opts_args->args->data))->arg);
        free(opts_args->args->data);
        tmp = opts_args->args;
        opts_args->args = opts_args->args->next;
        free(tmp);
    }
    ft_strdel(&opts_args->invalid);
}

static t_opt_set_db *fetch_set_opt(t_opt_set_db *opt_set_db, char *current, char *arg, int argc)
{
    if (!(opt_set_db->current = ft_strdup(current)))
        return (NULL);
    if (!arg)
        opt_set_db->arg = NULL;
    else if (!(opt_set_db->arg = ft_strdup(arg)))
        return (NULL);
    opt_set_db->argc = argc;
    return (opt_set_db);
}

static t_args_db    *fetch_args(t_args_db *args_db, char *arg, int argc)
{
    if (!(args_db->arg = ft_strdup(arg)))
        return (NULL);
    args_db->argc = argc;
    return (args_db);
}

uint8_t             ft_get_opts_args(t_opts_args *opts_args, t_opts_conf *opts_conf, int argc, char **argv)
{
    if (!opts_conf)
    {
        usage();
        return (FAILURE);
    }
    for (size_t i = 1; i < (size_t)argc; i++)
    {
        t_opt_set_db    opt_set_db;
        t_args_db       args_db;
        size_t          j                           = 1;
        size_t          z                           = 0;
        char            buffer[BUFF_SIZE];
        char            buffer_opt[2];
        uint8_t         allowed_found               = FALSE;
        uint8_t         allowed_opt_tab_arg_found   = FALSE;


        ft_memset(&opt_set_db, 0, sizeof(t_opt_set_db));
        ft_memset(&args_db, 0, sizeof(t_args_db));
        ft_memset(buffer, 0, sizeof(buffer));
        ft_memset(buffer_opt, 0, sizeof(buffer_opt));

        if (argv[i][0] == '-' && !argv[i][1])
        {
            if (!(ft_lstaddback(&opts_args->args, ft_lstnew(fetch_args(&args_db, argv[i], (int)i), sizeof(t_args_db)))))
                return (FAILURE);
            continue;
        }

        /* '--' handling */
        if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
        {
            i++;
            while (argv[i])
            {
                if (!(ft_lstaddback(&opts_args->args, ft_lstnew(fetch_args(&args_db, argv[i], (int)i), sizeof(t_args_db)))))
                    return (FAILURE);
                i++;

            }
            break;
        }

        /* Default '-' 'option' patern */
        if ((argv[i][0] == '-' && argv[i][1] != '-')
            || (!opts_conf->allowed_opt_tab
            && argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2]))
        {
            /* one string '-' option handler */
            if (ft_strchr(opts_conf->allowed_opt_arg, argv[i][j]) && argv[i][j + 1])
            {
                if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
                    opts_args->all = opts_args->all | (1ULL << (argv[i][j] - 'a'));
                if (argv[i][j] >= 'A' && argv[i][j] <= 'Z')
                    opts_args->all = opts_args->all | (1ULL << ((argv[i][j] - 'A') + 26));
                if (argv[i][j] >= '0' && argv[i][j] <= '9')
                    opts_args->all = opts_args->all | (1ULL << ((argv[i][j] - '0') + 52));
                size_t k = 0;
                size_t f = 2;
                while (argv[i][f])
                {
                    buffer[k] = argv[i][f];
                    k++;
                    f++;
                }
                buffer[k] = '\0';
                buffer_opt[0] = argv[i][1];
                buffer_opt[1] = '\0';
                if (!(ft_lstaddback(&opts_args->opt_set,
                        ft_lstnew(
                            fetch_set_opt(&opt_set_db, buffer_opt, buffer, (int)i),
                                sizeof(t_opt_set_db)))))
                        return (FAILURE);
            }
            else
            {
                while (argv[i][j])
                {
                    if (!ft_strchr(opts_conf->allowed_opt, argv[i][j]))
                    {
                        opts_args->all = (uint64_t)argv[i][j] | 1ULL << 63;
                        opts_args->argc = (int)i;
                        return (SUCCESS);
                    }
                    if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
                        opts_args->all = opts_args->all | (1ULL << (argv[i][j] - 'a'));
                    if (argv[i][j] >= 'A' && argv[i][j] <= 'Z')
                        opts_args->all = opts_args->all | (1ULL << ((argv[i][j] - 'A') + 26));
                    if (argv[i][j] >= '0' && argv[i][j] <= '9')
                        opts_args->all = opts_args->all | (1ULL << ((argv[i][j] - '0') + 52));
                    j++;
                }
                if ((argv[i + 1] && argv[i + 1][0] != '-') || !argv[i + 1])
                {
                    j--;
                    if (opts_conf->allowed_opt_arg && ft_strchr(opts_conf->allowed_opt_arg, argv[i][j]))
                    {
                        buffer[0] = argv[i][j];
                        buffer[1] = '\0';
                        if (!(ft_lstaddback(&opts_args->opt_set,
                            ft_lstnew(
                                fetch_set_opt(&opt_set_db, buffer, argv[i + 1] ? argv[i + 1] : NULL, (int)i),
                                    sizeof(t_opt_set_db)))))
                            return (FAILURE);
                    }
                    else
                    {
                        if (argv[i + 1] && !(ft_lstaddback(&opts_args->args, ft_lstnew(fetch_args(&args_db, argv[i + 1], (int)i + 1), sizeof(t_args_db)))))
                            return (FAILURE);
                    }
                    i++;
                }
            }
        }

        /* '--' 'option' patern */
        else if (argv[i][0] == '-' && argv[i][1] == '-' && opts_conf->allowed_opt_tab)
        {
            j = 2;
            while (argv[i][j])
                buffer[z++] = argv[i][j++];
            buffer[z] = '\0';
            for (size_t y = 0; opts_conf->allowed_opt_tab[y]; y++)
            {

                /* search for allowed string options (--) */
                if (ft_strequ(buffer, opts_conf->allowed_opt_tab[y]))
                {
                    /* search if arg requiered */
                    if (opts_conf->allowed_opt_tab_arg)
                        for (size_t w = 0; opts_conf->allowed_opt_tab_arg[w]; w++)
                            if (ft_strequ(opts_conf->allowed_opt_tab_arg[w], buffer))
                                allowed_opt_tab_arg_found = TRUE;

                    if (!(ft_lstaddback(&opts_args->opt_set,
                        ft_lstnew(
                            fetch_set_opt(&opt_set_db, buffer,
                                (argv[i + 1] && argv[i + 1][0] != '-'
                                && allowed_opt_tab_arg_found == TRUE)
                                ? argv[i + 1] : NULL, (int)i), sizeof(t_opt_set_db)))))
                        return (FAILURE);

                    if (argv[i + 1] && argv[i + 1][0] != '-'
                        && allowed_opt_tab_arg_found == TRUE)
                        i++;
                    allowed_found = TRUE;
                    break ;
                }
            }
            if (allowed_found == FALSE)
            {
                opts_args->all =  1ULL << 63;
                opts_args->invalid = ft_strdup(buffer);
                opts_args->argc = (int)i;
                return (SUCCESS);
            }
        }
        else
            if (!(ft_lstaddback(&opts_args->args, ft_lstnew(fetch_args(&args_db, argv[i], (int)i), sizeof(t_args_db)))))
                return (FAILURE);
    }
    return (SUCCESS);
}
