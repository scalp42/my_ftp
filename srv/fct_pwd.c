/*
** fct_pwd.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<string.h>
#include	<sys/socket.h>
#include	"ftp.h"

void	fct_pwd(char __UNUSED__ *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  char	path[1024];

  memset(path, '\0', 1024);
  sprintf(path, PWD, client_ftp->pwd);
  xsend(client_ftp->cs, path, strlen(path), 0);
}
