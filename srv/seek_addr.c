/*
** seek_addr.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	<string.h>
#include	"ftp.h"

char			*seek_addr(char *ipaddr, int porta, int portb)
{
  char			*ipsta;
  int			len;
  char			*port1;
  char			*port2;

  port1 = itoa(porta);
  port2 = itoa(portb);
  len = strlen(ipaddr) + strlen(port1) + strlen(port2) + 3;
  ipaddr = realloc(ipaddr, len * sizeof(char));
  for (ipsta = ipaddr; *ipsta != '\0'; ipsta++)
    if (*ipsta == '.')
      *ipsta = ',';
  ipaddr = stick_addr(ipaddr, port1, port2, len);
  return (ipaddr);
}
