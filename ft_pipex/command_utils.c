#include "pipex.h"

char *get_env_path(char **envp, char *cmd)  // Modified to accept cmd parameter
{
    char *path_var;
    char **paths;
    char *cmd_path;
    int i;

    path_var = NULL;
    for (i = 0; envp[i]; i++)
    {
        if (!ft_strncmp(envp[i], "PATH=", 5))
        {
            path_var = envp[i] + 5;
            break;
        }
    }
    if (!path_var)
        return (NULL);
    
    paths = ft_split(path_var, ':');
    if (!paths)
        return (NULL);

    for (i = 0; paths[i]; i++)
    {
        cmd_path = join_paths(paths[i], cmd);  // Using your join_paths function
        
        if (access(cmd_path, X_OK) == 0)
        {
            // Free paths array before returning
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return (cmd_path);
        }
        free(cmd_path);
    }
    
    // Free paths array before returning NULL
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);
    return (NULL);
}