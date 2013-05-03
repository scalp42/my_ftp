/*
** fct_cd.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<strings.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"ftp.h"

#ifdef sun4
char *realpath(const char *file_name, char *resolved_name);
#endif

void		send_cd_on_sock(client_ftp_t *client_ftp, char *real_path)
{
  client_ftp->pwd = strdup(real_path);
  if ((strncmp(client_ftp->pwd, client_ftp->pwd_init, strlen(client_ftp->pwd_init)) != 0) ||
      (chdir(client_ftp->pwd)) == -1)
    xsend(client_ftp->cs, NOPATH, strlen(NOPATH), 0);
  else
    xsend(client_ftp->cs, PATH, strlen(PATH), 0);
}

void		fct_cd(char *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  char		path[MAXPATHLEN];
  char		real_path[MAXPATHLEN];
  int		size;

  bzero(path, MAXPATHLEN);
  strcpy(path, client_ftp->pwd);
  strcat(path, cmd + 4);
  realpath(path, real_path);
  free(client_ftp->pwd);
  size = strlen(real_path);
  if (real_path[size - 1] != '/')
    {
      real_path[size] = '/';
      real_path[size + 1] = '\0';
    }
  send_cd_on_sock(client_ftp, real_path);
}
