/*
** open_new_data_connection.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"client.h"

void		open_new_data_connection(client_ftp_t *client_ftp)
{
  int		i;
  int		j;
  int		len;
  char		addr[128];
  char		buffer[1024];

  bzero(addr, 128);
  xsend(client_ftp->s, "PASV\n", 5, 0);
  i = xrecv(client_ftp->s, buffer, 1024, 0);
  clean_buff(buffer, i);
  printf("%s\n", buffer);
  for (i = 0; buffer[i] != '\0' && buffer[i] != '('; i++)
    ;
  i++;
  for (j = 0; buffer[i] != '\0' && buffer[i] != ')'; i++, j++)
    addr[j] = buffer[i];
  addr[j] = '\0';
  len = strlen(addr);
  for (i = 0, j = 0; addr[i] != '\0'; i++)
    if (addr[i] == ',')
      {
	if (j < 3)
	  addr[i] = '.';
	else
	  addr[i] = '\0';
	j++;
      }
  client_ftp->ipaddr = strdup(addr);
  client_ftp->port1 = atoi(addr + (strlen(addr) + 1));
  len = strlen(addr + (strlen(addr) + 1));
  client_ftp->port2 = atoi(addr + strlen(addr) + len + 2);
}
