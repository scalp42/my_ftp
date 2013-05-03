/*
** open_data_connection.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"client.h"

void		open_data_connection(client_ftp_t *client_ftp)
{
  struct sockaddr_in	sin;
  int			port;

  if ((client_ftp->s_data = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Problem in socket open\n");
      exit(1);
    }
  port = client_ftp->port1 * 256 + client_ftp->port2;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(client_ftp->ipaddr);
  connect(client_ftp->s_data, (struct sockaddr *)&sin, sizeof (struct sockaddr_in));
  printf("Data connected to %s %d\n", inet_ntoa(sin.sin_addr), port);
}
