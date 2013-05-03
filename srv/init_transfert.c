/*
** init_transfert.c for ftp in /Users/scalp/projs/my_ftp
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

FILE		*init_transfert(char *cmd, client_ftp_t *client_ftp)
{
  FILE		*file;
  int		len;
  char		get[2048];

  if ((file = fopen(cmd + 5, "r")) == NULL)
    {
      xsend(client_ftp->cs, NO_FILE, strlen(NO_FILE), 0);
      return (NULL);
    }
  len = size_file(file);
  bzero(get, 2048);
  sprintf(get, GET, cmd + 5, len);
  xsend(client_ftp->cs, get, strlen(get), 0);
  return (file);
}
