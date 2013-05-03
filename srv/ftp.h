/*
** ftp.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#ifndef __MY_FTP__
#define __MY_FTP__

#include	<arpa/inet.h>
#include	<stdio.h>

#define WELCOME	"220 Welcome newbee\n"
#define LOG	"331 Please specify the password\n"
#define PASS	"230 Login successfull\n"
#define SYST	"215 UNIX Type: L8\n"
#define FEAT	"211 End\n"
#define PWD    	"257 \"%s\"\n"
#define EPSV 	"500\n"
#define	PASV	"227 Entering Passive Mode(%s)\n"
#define	LIST	"150 Here comes the directory listing.\n"
#define	END_LI	"226 Directory send OK.\n"
#define	NOPATH	"550 Failed to change directory.\n"
#define	PATH	"250 Directory successfully changed.\n"
#define	ENVIAR	"226 Transfer complete.\n"
#define GET	"150 Open BINARY mode data connection for %s (%d)\n"
#define	PUT	"150 Opening BINARY mode data connection for %s.\n"
#define	NO_FILE	"550 Failed to open file.\n"
#define ASCII	"200 Type set : ascii.\n"
#define BINARY	"200 Type set : binary.\n"
#define	TYPE_W	"400 Error of type\n"
#define	QUIT	"221 Goodbye.\n"
#define __UNUSED__ __attribute__ ((unused))

typedef struct	cmd_s
{
  char		*cmd;
  int		size;
  void		(*f)();
}		cmd_t;

typedef	struct	client_ftp_s
{
  int		cs;
  int		cs_data;
  char		*pwd;
  char		*pwd_init;
  char		type;
}		client_ftp_t;

typedef struct	ftp_s
{
  int			s;
  int			s_data;
  int			port1;
  int			port2;
  struct sockaddr_in    sin;
}		ftp_t;

void		fct_epsv(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_feat(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_pass(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_pasv(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_pwd(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_syst(char *cmd, client_ftp_t *cs, ftp_t *ftp);
void		fct_user(char *cmd, client_ftp_t *cs, ftp_t *ftp);
char		*get_next_line(int fd);
void		*xmalloc(int size);
int		xread(int id_open, void *buffer, int nbytes);
char		*itoa(int nb);
char		*stick_addr(char *ipaddr, char *port1, char *port2, int len);
char	       	*seek_addr(char *ipaddr, int porta, int portb);
char		*create_real_mess(char *ipaddr);
char		open_new_socket(client_ftp_t *client_ftp, ftp_t *ftp);
void		fct_ls(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
void		fct_cd(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
void		fct_retr(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
void		fct_stor(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
void		init_pwd(client_ftp_t *client_ftp);
void		fct_type(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
void		fct_quit(char *cmd, client_ftp_t *client_ftp, ftp_t *ftp);
FILE		*init_transfert(char *cmd, client_ftp_t *client_ftp);
int		size_file(FILE *fs);
ssize_t		xsend(int s, const void *msg, size_t len, int flags);
ssize_t		xrecv(int s, void *buf, size_t len, int flags);

#ifdef sun4
char		*strdup(const char *s1);
void		bzero(void *s, size_t n);
#endif

#endif
