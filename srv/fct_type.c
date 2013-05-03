/*
** fct_type.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<string.h>
#include	<sys/socket.h>
#include	"ftp.h"

void		fct_type(char *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  if (strcmp(cmd, "TYPE I") == 0)
    {
      client_ftp->type = 0;
      xsend(client_ftp->cs, BINARY, strlen(BINARY), 0);
    }
  else if (strcmp(cmd, "TYPE A") == 0)
    {
      client_ftp->type = 1;
      xsend(client_ftp->cs, ASCII, strlen(ASCII), 0);
    }
  else
    {
      xsend(client_ftp->cs, TYPE_W, strlen(TYPE_W), 0);
    }
}
