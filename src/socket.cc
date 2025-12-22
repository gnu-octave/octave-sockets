// Copyright (C) John Swensen <jpswensen@comcast.net>
// Copyright (C) 2007 Tom Holroyd <tomh@kurage.nimh.nih.gov>
// Copyright (C) 2009 Paul Dreik <slask@pauldreik.se>
// Copyright (C) 2013 Carnë Draug <carandraug@octave.org>
// Copyright (C) 2020 Octave maintainers <maintainers@octave.org>
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, see <http://www.gnu.org/licenses/>.

// eliminate some compiler warnings
#ifdef __WIN32__
#define _NO_SYS_GUID_OPERATOR_EQ_ 1
#endif

// Octave Includes
#include <octave/oct.h>
#include <octave/parse.h>
#include <octave/cmd-hist.h>
#include <octave/symtab.h>
#include <octave/variables.h>
#include <octave/Array.h>

#include <octave/ops.h>
#include <octave/ov-base.h>
#include <octave/ov-typeinfo.h>
#include <octave/ov.h>
#include <octave/ov-scalar.h>
#include <octave/ov-struct.h>
#include <octave/ov-uint8.h>

#include <octave/defun-dld.h>

// System includes
#include <sys/types.h>
#ifndef __WIN32__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#define SOCK_OPT_TYPE void*
#else
typedef int socklen_t;
#define SOCK_OPT_TYPE char*
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <errno.h>
#include <string.h>

/*
 * fixes for older octave
 */
#if (OCTAVE_MAJOR_VERSION<4) || ( (OCTAVE_MAJOR_VERSION==4) && (OCTAVE_MINOR_VERSION<4))
  // changed for 4.4
  #define isempty is_empty
  #define isstruct is_map
#endif

/*
 * macro for defining all the socket constants as
 * octave functions.
 */
# define DEFUN_DLD_SOCKET_CONSTANT_VALUE(name, value)\
  DEFUNX_DLD ( #name, F ## name, G ## name, args, nargout, \
               "socket constant")                          \
  {    return octave_value(value); };

# define DEFUN_DLD_SOCKET_CONSTANT(name)\
  DEFUNX_DLD ( #name, F ## name, G ## name, args, nargout, \
               "socket constant")                          \
  {    return octave_value( name ); };

# define DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(name)\
  DEFUNX_DLD ( #name, F ## name, G ## name, args, nargout, \
               "socket constant")                          \
  {    error (#name " is not supported on this platform.");   return octave_value(); };


// PKG_ADD: autoload ("AF_UNSPEC", which ("socket"));
// PKG_DEL: try; autoload ("AF_UNSPEC", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_UNSPEC );

// PKG_ADD: autoload ("AF_UNIX", which ("socket"));
// PKG_DEL: try; autoload ("AF_UNIX", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_UNIX );
#ifndef __WIN32__
// PKG_ADD: autoload ("AF_LOCAL", which ("socket"));
// PKG_DEL: try; autoload ("AF_LOCAL", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_LOCAL );
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(AF_LOCAL );
#endif
// PKG_ADD: autoload ("AF_INET", which ("socket"));
// PKG_DEL: try; autoload ("AF_INET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_INET );
// PKG_ADD: autoload ("AF_APPLETALK", which ("socket"));
// PKG_DEL: try; autoload ("AF_APPLETALK", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_APPLETALK );
//DEFUN_DLD_SOCKET_CONSTANT(AF_INET6 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_IPX );
//DEFUN_DLD_SOCKET_CONSTANT(AF_NETLINK );
//DEFUN_DLD_SOCKET_CONSTANT(AF_X25 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_AX25 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_ATMPVC );
//DEFUN_DLD_SOCKET_CONSTANT(AF_PACKET );

// PKG_ADD: autoload ("SOCK_STREAM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_STREAM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_STREAM );
// PKG_ADD: autoload ("SOCK_DGRAM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_DGRAM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_DGRAM );
// PKG_ADD: autoload ("SOCK_SEQPACKET", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_SEQPACKET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_SEQPACKET );
// PKG_ADD: autoload ("SOCK_RAW", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_RAW", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RAW );
// PKG_ADD: autoload ("SOCK_RDM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_RDM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RDM );
//DEFUN_DLD_SOCKET_CONSTANT(SOCK_PACKET );

// PKG_ADD: autoload ("MSG_PEEK", which ("socket"));
// PKG_DEL: try; autoload ("MSG_PEEK", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_PEEK );
#ifdef MSG_DONTWAIT
// PKG_ADD: autoload ("MSG_DONTWAIT", which ("socket"));
// PKG_DEL: try; autoload ("MSG_DONTWAIT", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_DONTWAIT );
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(MSG_DONTWAIT );
#endif
#ifdef MSG_WAITALL
// PKG_ADD: autoload ("MSG_WAITALL", which ("socket"));
// PKG_DEL: try; autoload ("MSG_WAITALL", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_WAITALL );
#else
#define MSG_WAITALL -1
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(MSG_WAITALL );
#endif

// PKG_ADD: autoload ("SOL_SOCKET", which ("socket"));
// PKG_DEL: try; autoload ("SOL_SOCKET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOL_SOCKET );

// PKG_ADD: autoload ("SO_KEEPALIVE", which ("socket"));
// PKG_DEL: try; autoload ("SO_KEEPALIVE", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_KEEPALIVE );

// PKG_ADD: autoload ("SO_REUSEADDR", which ("socket"));
// PKG_DEL: try; autoload ("SO_REUSEADDR", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_REUSEADDR );

// PKG_ADD: autoload ("SO_TYPE", which ("socket"));
// PKG_DEL: try; autoload ("SO_TYPE", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_TYPE );

#ifdef SO_DONTROUTE
// PKG_ADD: autoload ("SO_DONTROUTE", which ("socket"));
// PKG_DEL: try; autoload ("SO_DONTROUTE", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_DONTROUTE );
#else
#define SO_DONTROUTE -1
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(SO_DONTROUTE );
#endif

#ifdef SO_BROADCAST
// PKG_ADD: autoload ("SO_BROADCAST", which ("socket"));
// PKG_DEL: try; autoload ("SO_BROADCAST", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_BROADCAST );
#else
#define SO_BROADCAST -1
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(SO_BROADCAST );
#endif

#ifdef SO_DEBUG
// PKG_ADD: autoload ("SO_DEBUG", which ("socket"));
// PKG_DEL: try; autoload ("SO_DEBUG", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_DEBUG );
#else
#define S_DEBUG -1
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(SO_DEBUG );
#endif

// PKG_ADD: autoload ("SHUT_RD", which ("socket"));
// PKG_DEL: try; autoload ("SHUT_RD", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT_VALUE(SHUT_RD, 0);

// PKG_ADD: autoload ("SHUT_WR", which ("socket"));
// PKG_DEL: try; autoload ("SHUT_WR", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT_VALUE(SHUT_WR, 1);

// PKG_ADD: autoload ("SHUT_RDWR", which ("socket"));
// PKG_DEL: try; autoload ("SHUT_RDWR", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT_VALUE(SHUT_RDWR, 2);

// A few well known IPPROTO_ values

// PKG_ADD: autoload ("IPPROTO_IP", which ("socket"));
// PKG_DEL: try; autoload ("IPPROTO_IP", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(IPPROTO_IP);

// PKG_ADD: autoload ("IPPROTO_ICMP", which ("socket"));
// PKG_DEL: try; autoload ("IPPROTO_ICMP", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(IPPROTO_ICMP);

// PKG_ADD: autoload ("IPPROTO_TCP", which ("socket"));
// PKG_DEL: try; autoload ("IPPROTO_TCP", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(IPPROTO_TCP);

// PKG_ADD: autoload ("IPPROTO_UDP", which ("socket"));
// PKG_DEL: try; autoload ("IPPROTO_UDP", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(IPPROTO_UDP);

// AI flags

// PKG_ADD: autoload ("AI_PASSIVE", which ("socket"));
// PKG_DEL: try; autoload ("AI_PASSIVE", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AI_PASSIVE);

// PKG_ADD: autoload ("AI_NUMERICSERV", which ("socket"));
// PKG_DEL: try; autoload ("AI_NUMERICSERV", which ("socket"), "remove"); catch; end;
#ifdef AI_NUMERICSERV
DEFUN_DLD_SOCKET_CONSTANT(AI_NUMERICSERV);
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(AI_NUMERICSERV );
#endif

// PKG_ADD: autoload ("AI_V4MAPPED", which ("socket"));
// PKG_DEL: try; autoload ("AI_V4MAPPED", which ("socket"), "remove"); catch; end;
#ifdef AI_V4MAPPED
DEFUN_DLD_SOCKET_CONSTANT(AI_V4MAPPED);
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(AI_V4MAPPED);
#endif

// PKG_ADD: autoload ("AI_ADDRCONFIG", which ("socket"));
// PKG_DEL: try; autoload ("AI_ADDRCONFIG", which ("socket"), "remove"); catch; end;
#ifdef AI_ADDRCONFIG
DEFUN_DLD_SOCKET_CONSTANT(AI_ADDRCONFIG);
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(AI_ADDRCONFIG);
#endif

// PKG_ADD: autoload ("AI_ALL", which ("socket"));
// PKG_DEL: try; autoload ("AI_ALL", which ("socket"), "remove"); catch; end;
#ifdef AI_ALL
DEFUN_DLD_SOCKET_CONSTANT(AI_ALL);
#else
DEFUN_DLD_UNIMPLMENTED_SOCKET_CONSTANT(AI_ALL);
#endif

//we need to keep track if sockets has been loaded, as it
//requires initialization on windows platforms.
#ifdef __WIN32__
static bool type_loaded = false;
#endif

// PKG_ADD: autoload ("socket", which ("socket"));
// PKG_DEL: try; autoload ("socket", which ("socket"), "remove"); catch; end;
// Function to create a socket
DEFUN_DLD(socket, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {@var{sock} =} socket ()\n\
@deftypefnx {Loadable Function} {@var{sock} =} socket (@var{domain})\n\
@deftypefnx {Loadable Function} {@var{sock} =} socket (@var{domain}, @var{type})\n\
@deftypefnx {Loadable Function} {@var{sock} =} socket (@var{domain}, @var{type}, @var{protocol})\n\
Creates a socket.\n\
\n\
@var{domain} is an integer, where the value AF_INET\n\
can be used to create an IPv4 socket.\n\
\n\
@var{type} is an integer describing the socket.  When using IP, specifying\n\
SOCK_STREAM gives a TCP socket.\n\
\n\
@var{protocol} is currently not used and should be 0 if specified.\n\
\n\
If no input arguments are given, default values AF_INET and\n\
SOCK_STREAM are used.\n\
\n\
See the local @command{socket} reference for more details.\n\
@end deftypefn")
{
  int domain    = AF_INET;
  int type      = SOCK_STREAM;
  int protocol  = 0;

#ifdef __WIN32__
  if (! type_loaded)
    {
      type_loaded = true;

      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      wVersionRequested = MAKEWORD (2, 2);
      err = WSAStartup (wVersionRequested, &wsaData);
      if (err != 0)
        {
          error ("socket: could not initialize winsock library");
          return octave_value();
        }
    }
#endif

  // Convert the arguments to their #define'd value
  const octave_idx_type nargin = args.length ();
  if (nargin > 0)
    {
      if (! args(0).is_real_scalar ())
        {
          error ("socket: DOMAIN must be a scalar integer");
          return octave_value ();
        }
      domain = args(0).int_value ();
    }

  if (nargin > 1)
    {
      if (! args(0).is_real_scalar ())
        {
          error ("socket: TYPE must be a scalar integer");
          return octave_value ();
        }
 
      type = args(1).int_value ();
    }

  if (nargin > 2)
    {
      if (! args(0).is_real_scalar ())
        {
          error ("socket: PROTOCOL must be a scalar integer");
          return octave_value ();
        }
 
      protocol = args(2).int_value ();
      if (protocol != 0)
        {
          error ("socket: for now, PROTOCOL must always be 0 (zero)");
          return octave_value ();
        }
    }

  // Create the new socket
  const int sock_fd = ::socket (domain, type, protocol);
  if (sock_fd == -1)
      error ("socket failed with error %i (%s)", errno, strerror(errno));

  return octave_value(sock_fd);
}

/*
 * helper function to convert an octave value to an integer,
 * returning -1 if it failed.
 */
int get_socket(const octave_value& arg)
{
  if (! arg.is_real_scalar ())
    {
      return -1;
    }

  const int fd = arg.int_value();

  return fd;
}


/*
 * closes the given socket file descriptor
 */
inline void close_octavesocket(const int sock_fd) {
#ifndef __WIN32__
  ::close (sock_fd);
#else
  ::closesocket (sock_fd);
#endif
}

// PKG_ADD: autoload ("connect", which ("socket"));
// PKG_DEL: try; autoload ("connect", which ("socket"), "remove"); catch; end;
// function to create an outgoing connection
DEFUN_DLD(connect, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} connect (@var{s}, @var{serverinfo})\n\
Connect socket.\n\
\n\
Connects the socket @var{s} following the information\n\
in the struct @var{serverinfo} which must contain the\n\
following fields:\n\
\n\
@table @code\n\
@item addr\n\
a string with the host name to connect to\n\
\n\
@item port\n\
the port number to connect to (an integer)\n\
@end table\n\
\n\
On successful connect, the returned status is zero.\n\
\n\
See the @command{connect} man pages for further details.\n\
@end deftypefn")
{

  if (args.length () != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("connect: S must be a valid socket");
      return octave_value ();
    }

  // Extract information about the server to connect to.
  const octave_scalar_map struct_serverInfo = args(1).scalar_map_value ();
  if (struct_serverInfo.nfields () == 0)
    {
      error ("connect: SERVERINFO must be a struct");
      return octave_value ();
    }

  if(! (struct_serverInfo.contains ("addr") && struct_serverInfo.contains ("port")))
    {
      error ("connect: SERVERINFO must have a string and integer in fields \"addr\" and \"port\"");
      return octave_value ();
    }

  if(! (struct_serverInfo.getfield ("addr").is_string() && struct_serverInfo.getfield ("port").is_real_scalar()))
    {
      error ("connect: SERVERINFO must have a string and integer in fields \"addr\" and \"port\"");
      return octave_value ();
    }
  const std::string addr = struct_serverInfo.getfield ("addr").string_value ();
  const int port    = struct_serverInfo.getfield ("port").int_value ();
  if (addr.empty ())
    {
      error ("connect: SERVERINFO addr is an empty string");
      return octave_value ();
    }

  // Fill in the server info struct
  struct sockaddr_in serverInfo;
  serverInfo.sin_family = AF_INET;

  struct hostent* hostInfo = gethostbyname (addr.c_str ());
  if (! hostInfo)
    {
      error ("connect: error in gethostbyname()");
      return octave_value ();
    }
  serverInfo.sin_addr.s_addr = *((long*)hostInfo->h_addr_list[0]);
  serverInfo.sin_port = htons(port);

  const int retval = connect (s, (struct sockaddr*)&serverInfo,
                              sizeof (struct sockaddr));
  if (retval == -1)
      error ("connect failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("disconnect", which ("socket"));
// PKG_DEL: try ; autoload ("disconnect", which ("socket"), "remove") ; catch ; end;
// function to disconnect asocket
DEFUN_DLD(disconnect, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} disconnect (@var{s})\n\
Disconnect socket.\n\
\n\
Disconnects the socket @var{s}.  If successful, @code{disconnect} returns 0,\n\
otherwise, it returns -1.\n\
\n\
Since we can't call fclose on the file descriptor directly, use this\n\
function to disconnect the socket.\n\
\n\
@end deftypefn")
{
  if (args.length () != 1)
    {
      print_usage ();
      return octave_value ();
    }

  int retval = -1;
  const int s = get_socket (args(0));
  if (s != -1)
    {
      close_octavesocket(s);
      retval = 0;
    }
  return octave_value (retval);
}

// PKG_ADD: autoload ("getaddrinfo", which ("socket"));
// PKG_DEL: try; autoload ("getaddrinfo", which ("socket"), "remove"); ; catch; end;
// function to get a host information from a host name/service
DEFUN_DLD(getaddrinfo, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{addrinforesults} =} getaddrinfo (@var{hostname}, @var{service}, @var{hints})\n\
Get addressinfo lookup for a hostname/service.\n\
\n\
Returns an array of addressinfo structs with the following fields:\n\
\n\
@table @code\n\
@item family\n\
Integer family value\n\
@item socktype\n\
Integer socktype value\n\
@item protocol\n\
Integer protocol value\n\
@item addr\n\
a string with the host name to send to\n\
\n\
@item port\n\
the port number to send to (an integer)\n\
@end table\n\
\n\
hints is optional with one or more fields:\n\
\n\
@table @code\n\
@item family\n\
Integer family value\n\
@item socktype\n\
Integer socktype value\n\
@item protocol\n\
Integer protocol value\n\
@item flags\n\
a integer ai flags\n\
@end table\n\
\
\n\
See the @command{getaddrinfo} man pages for details.\n\
\n\
@end deftypefn")
{
  const int nargin = args.length ();

  if (nargin < 2 || nargin > 3)
    {
      print_usage ();
      return octave_value ();
    }

  if (! args(0).is_string ())
    {
      error ("getaddrinfo: HOSTNAME must be a string");
      return octave_value ();
    }
  const std::string addr = args(0).string_value ();

  if (! args(1).is_string ())
    {
      error ("getaddrinfo: SERVICE must be a string");
      return octave_value ();
    }

  const std::string service = args(1).string_value ();
 

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;    /* ipv4 */
  hints.ai_socktype = SOCK_STREAM; /* any type */
  hints.ai_flags = 0; //AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  if (nargin > 2 && !args(2).isempty())
    {
      const octave_scalar_map struct_hint_info = args(2).scalar_map_value ();
      if (struct_hint_info.nfields () == 0)
        {
          error ("getaddrinfo: HINTS must be a struct");
          return octave_value ();
        }
      // family, socktype, flags, protocol
      if (struct_hint_info.contains ("family"))
        {
          if (struct_hint_info.getfield ("family").is_real_scalar ())
            hints.ai_family = struct_hint_info.getfield ("family").int_value();
	  else
            {
              error ("getaddrinfo: HINTS.family must be an integer value");
              return octave_value ();
            }
        }

      if (struct_hint_info.contains ("socktype"))
        {
          if (struct_hint_info.getfield ("socktype").is_real_scalar ())
            hints.ai_socktype = struct_hint_info.getfield ("socktype").int_value();
	  else
            {
              error ("getaddrinfo: HINTS.socktype must be an integer value");
              return octave_value ();
            }
        }

      if (struct_hint_info.contains ("flags"))
        {
          if (struct_hint_info.getfield ("flags").is_real_scalar ())
            hints.ai_flags = struct_hint_info.getfield ("flags").int_value();
	  else
            {
              error ("getaddrinfo: HINTS.flags must be an integer value");
              return octave_value ();
            }
        }

      if (struct_hint_info.contains ("protocol"))
        {
          if (struct_hint_info.getfield ("protocol").is_real_scalar ())
            hints.ai_protocol = struct_hint_info.getfield ("protocol").int_value();
	  else
            {
              error ("getaddrinfo: HINTS.protocol must be an integer value");
              return octave_value ();
            }
        }
    }

  int status;
  struct addrinfo *result, *rp;

  if ((status = getaddrinfo (
    addr.empty() ? NULL : addr.c_str(),
    service.empty() ? NULL : service.c_str(),
    &hints, &result)) != 0)
    {
      error ("getaddrinfo: Failed to get info - error %d", status);
      return octave_value ();
    }

  std::vector<octave_value> result_array;
  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      octave_scalar_map  client_info_map;
      client_info_map.assign ("family", octave_value (rp->ai_family));
      client_info_map.assign ("socktype", octave_value (rp->ai_socktype));
      client_info_map.assign ("protocol", octave_value (rp->ai_protocol));

      // there would normally be addr
      // TODO: depend on family here
      sockaddr_in * addr = (sockaddr_in*)rp->ai_addr;
      client_info_map.assign ("port", octave_value (ntohs(addr->sin_port)));
      client_info_map.assign ("addr", octave_value (inet_ntoa(addr->sin_addr)));
      result_array.push_back(octave_value(client_info_map));
    }
 
  freeaddrinfo(result); // free the linked-list

  Cell cell(result_array.size(), 1);
  for(octave_idx_type i=0; i<(octave_idx_type)result_array.size(); i++)
    cell(i, 0) = result_array[i];
    
  octave_value_list ret;
  ret(0) = cell;
  return ret;
}
 
// PKG_ADD: autoload ("gethostbyname", which ("socket"));
// PKG_DEL: try; autoload ("gethostbyname", which ("socket"), "remove"); ; catch; end;
// function to get a host number from a host name
DEFUN_DLD(gethostbyname, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{ipaddress} =} gethostbyname (@var{hostname})\n\
Return IP address for host name.\n\
\n\
For example:\n\
\n\
@example\n\
@group\n\
gethostbyname (\"localhost\")\n\
  @result{} 127.0.0.1\n\
@end group\n\
@end example\n\
\n\
See the @command{gethostbyname} man pages for details.\n\
\n\
@end deftypefn")
{
  const int nargin = args.length ();

  if (nargin != 1)
    {
      print_usage ();
      return octave_value ();
    }

  if (! args(0).is_string ())
    {
      error ("gethostbyname: HOSTNAME must be a string");
      return octave_value ();
    }
  const std::string addr = args(0).string_value ();

  string_vector host_list;
  struct hostent* hostInfo = gethostbyname (addr.c_str ());
  if (hostInfo)
    {
      for (int i = 0 ; i < hostInfo->h_length/4; i++)
        {
          std::string temp_addr = inet_ntoa (*(struct in_addr*)hostInfo->h_addr_list[i]);
          host_list.append (temp_addr);
        }
    }
  return octave_value (host_list);
}

// PKG_ADD: autoload ("send", which ("socket"));
// PKG_DEL: try; autoload ("send", which ("socket"), "remove"); catch; end;
// function to send data over a socket
DEFUN_DLD(send, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {@var{retval} =} send (@var{s}, @var{data})\n\
@deftypefnx {Loadable Function} {@var{retval} =} send (@var{s}, @var{data}, @var{flags})\n\
Send data on specified socket.\n\
\n\
Sends data on socket @var{s}.  @var{data} should be an uint8 array or\n\
a string.\n\
\n\
See the @command{send} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();

  if (nargin < 2 || nargin > 3)
  {
    print_usage ();
    return octave_value ();
  }

  int flags = 0;
  if (nargin > 2)
    {
      if (! args(2).is_real_scalar ())
        {
          error ("send: FLAGS must be a scalar integer");
          return octave_value ();
         }

      flags = args(2).int_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("send: s must be a valid socket");
      return octave_value ();
    }

  int retval = -1;
  // Extract the data from the octave variable and send it
  const octave_base_value& data = args(1).get_rep ();
  if (data.is_string ())
    {
      std::string buf = data.string_value ();
      retval = ::send (s, buf.c_str (), buf.length (), flags);
    }
  else if (data.byte_size () == size_t (data.numel ()))
    {
      const NDArray d1 = data.array_value ();
      const octave_idx_type length = d1.numel ();
      const double* d1fvec = d1.data ();

      OCTAVE_LOCAL_BUFFER (unsigned char, buf, length);
      for (int i = 0 ; i < length; i++)
        buf[i] = (unsigned char)d1fvec[i];
      
      //hmm, flags are set to 0, unlike the call above!
      retval = ::send (s, (const char*)buf, data.byte_size (), 0);
    }
  else
    {
      error( "connect: invalid DATA to send.  Please format it prior to sending" );
      return octave_value ();
    }

  return octave_value (retval);
}

// PKG_ADD: autoload ("recv", which ("socket"));
// PKG_DEL: try; autoload ("recv", which ("socket"), "remove"); catch; end;
// function to receive data over a socket
DEFUN_DLD(recv, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {[@var{data}, @var{count}] =} recv (@var{s}, @var{len})\n\
@deftypefnx {Loadable Function} {[@var{data}, @var{count}] =} recv (@var{s}, @var{len}, @var{flags})\n\
Read data from specified socket.\n\
\n\
Requests reading @var{len} bytes from the socket @var{s}.\n\
The optional integer @var{flags} parameter can be used to modify the\n\
behaviour of @code{recv}.\n\
\n\
The read data is returned in the uint8 array @var{data}.  The number of\n\
bytes read is returned in @var{count}.\n\
\n\
You can get non-blocking operation by using the flag @code{MSG_DONTWAIT}\n\
which makes the @code{recv()} call return immediately.  If there is no\n\
data, -1 is returned in count.\n\
\n\
See the @command{recv} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();
  int retval = 0;
  int flags = 0;

  if (nargin < 2 || nargin > 3)
    {
      print_usage ();
      return octave_value ();
    }

  if (nargin > 2)
    {
      if (! args(2).is_real_scalar ())
        {
          error ("recv: FLAGS must be a scalar integer");
          return octave_value ();
        }

      flags = args(2).int_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("recv: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("recv: LEN must be a non-negative integer");
      return octave_value (-1);
    }

  const long len = args(1).int_value ();
  if (len < 0)
    {
      error ("recv: LEN must be a non-negative integer");
      return octave_value(-1);
    }

  OCTAVE_LOCAL_BUFFER (unsigned char, buf, len);
#ifndef __WIN32__
  retval = ::recv( s, buf, len, flags );
#else
  retval = ::recv( s, ( char* )buf, len, flags );
#endif

  octave_value_list return_list;
  uint8NDArray data;

  //always return the status in the second output parameter
  return_list(1) = retval;
  if (retval <= 0)
    // We get -1 if an error occurs,or if there is no data and the
    // socket is non-blocking. We should return in both cases.
    // We get 0 if the peer has shut down.
    return_list(0) = data;
  else
    {
      //Normal behaviour. Copy the buffer to the output variable. For
      //backward compatibility, a row vector is returned.
      data.resize (dim_vector (1, retval));
      octave_uint8* data_fvec = data.fortran_vec ();
      for (int i = 0 ; i < retval ; i++)
        data_fvec[i] = buf[i];

      return_list(0) = data;
    }
  return return_list;
}

// PKG_ADD: autoload ("bind", which ("socket"));
// PKG_DEL: try; autoload ("bind", which ("socket"), "remove"); catch; end;
// function to bind a socket
DEFUN_DLD(bind, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} bind (@var{s}, @var{portnumber})\n\
Bind specific socket to port number.\n\
\n\
See the @command{bind} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length () != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("bind: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("bind: PORT must be a scalar integer");
      return octave_value (-1);
    }

  const long port = args(1).int_value ();

  struct sockaddr_in serverInfo;
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons (port);
  serverInfo.sin_addr.s_addr = INADDR_ANY;

  int retval = ::bind (s, (struct sockaddr *)&serverInfo, sizeof (serverInfo));
  if (retval == -1)
      error ("bind failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("listen", which ("socket"));
// PKG_DEL: try; autoload ("listen", which ("socket"), "remove"); catch; end;
// function to listen on a socket
DEFUN_DLD(listen, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} listen (@var{s}, @var{backlog})\n\
Listen on socket for connections.\n\
\n\
Listens on socket @var{s} for connections.  @var{backlog} specifies\n\
how large the queue of incoming connections is allowed to\n\
grow.\n\
\n\
On success, zero is returned.\n\
\n\
See the @command{listen} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length() != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("listen: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("listen: BACKLOG must be an integer scalar");
      return octave_value (-1);
    }

  const int backlog = args(1).int_value ();

  const int retval = ::listen (s, backlog);
  if (retval == -1)
      error ("listen failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("accept", which ("socket"));
// PKG_DEL: try; autoload ("accept", which ("socket"), "remove"); catch; end;
// function to accept on a listening socket
DEFUN_DLD(accept,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{client}, @var{info}] =} accept (@var{s})\n\
Accept incoming connection on specified socket.\n\
\n\
Accepts an incoming connection on the socket @var{s}.\n\
The newly created socket is returned in @var{client}, and\n\
associated information in a struct info.\n\
\n\
See the @command{accept} man pages for further details.\n\
\n\
@end deftypefn")
{
  struct sockaddr_in clientInfo;
  socklen_t clientLen = sizeof (struct sockaddr_in);

  if (args.length () != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("accept: S must be a valid socket");
      return octave_value ();
    }

#ifndef __WIN32__
  int fd = ::accept( s, (struct sockaddr *)&clientInfo, &clientLen );
#else
  int fd = ::accept( s, (struct sockaddr *)&clientInfo, ( int* )&clientLen );
#endif
  if (fd == -1)
    {
      error ("accept failed with error %i (%s)", errno, strerror(errno));
      return octave_value ();
    }

#if 0
  // create the octave_socket object and set the fd
  octave_socket* retobj = new octave_socket(fd);
#endif
  // place the client information into a structure
  octave_scalar_map client_info_map;
  client_info_map.assign ("sin_family", octave_value (clientInfo.sin_family));
  client_info_map.assign ("sin_port", octave_value (clientInfo.sin_port));
  client_info_map.assign ("sin_addr", octave_value (inet_ntoa(clientInfo.sin_addr)));

  // returns the accepted socket and a clientinfo structure
  octave_value_list return_list;
  return_list(0) = octave_value (fd);
  return_list(1) = client_info_map;

  return return_list;
}

// PKG_ADD: autoload ("sendto", which ("socket"));
// PKG_DEL: try; autoload ("sendto", which ("socket"), "remove"); catch; end;
// function to send data over a socket
DEFUN_DLD(sendto, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{retval} =} sendto (@var{s}, @var{data}, @var{dest_info})\n\
@deftypefnx {Loadable Function} {@var{retval} =} sendto (@var{s}, @var{data}, @var{flags}, @var{dest_info})\n\
Send data on specified socket.\n\
\n\
Sends data on socket @var{s} to destination.  @var{data} should be an uint8 array or\n\
a string.\n\
\n\
The dest_info struct @var{dest_info} must contain the\n\
following fields:\n\
\n\
@table @code\n\
@item addr\n\
a string with the host name to send to\n\
\n\
@item port\n\
the port number to send to (an integer)\n\
@end table\n\
\n\
See the @command{sendto} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();

  if (nargin < 3 || nargin > 4)
  {
    print_usage ();
    return octave_value ();
  }

  int dest_info_pos = 2;
  int flags = 0;
  if (nargin == 4)
    {
      if (! args(2).is_real_scalar ())
        {
          error ("send: FLAGS must be a scalar integer");
          return octave_value ();
        }
      dest_info_pos = 3;
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("send: s must be a valid socket");
      return octave_value ();
    }

  // Extract information about the server to send to.
  const octave_scalar_map struct_dest_info = args(dest_info_pos).scalar_map_value ();
  if (struct_dest_info.nfields () == 0)
    {
      error ("sendto: DESTINFO must be a struct");
      return octave_value ();
    }

  if(! (struct_dest_info.contains ("addr") && struct_dest_info.contains ("port")))
    {
      error ("sendto: DESTINFO must have a string and integer in fields \"addr\" and \"port\"");
      return octave_value ();
    }

  if(! (struct_dest_info.getfield ("addr").is_string() && struct_dest_info.getfield ("port").is_real_scalar()))
    {
      error ("sendto: DESTINFO must have a string and integer in fields \"addr\" and \"port\"");
      return octave_value ();
    }
  const std::string addr = struct_dest_info.getfield ("addr").string_value ();
  const int port    = struct_dest_info.getfield ("port").int_value ();
  if (addr.empty ())
    {
      error ("sendto: DESTINFO addr is an empty string");
      return octave_value ();
    }

  // Fill in the dest info struct
  struct sockaddr_in dest_info;
  memset(&dest_info, 0, sizeof(dest_info));
  dest_info.sin_family = AF_INET;

  struct hostent* hostInfo = gethostbyname (addr.c_str ());
  if (! hostInfo)
    {
      error ("sendto: error in gethostbyname()");
      return octave_value ();
    }
  dest_info.sin_addr.s_addr = *((long*)hostInfo->h_addr_list[0]);
  dest_info.sin_port = htons(port);

  int retval = -1;
  // Extract the data from the octave variable and send it
  const octave_base_value& data = args(1).get_rep ();
  if (data.is_string ())
    {
      std::string buf = data.string_value ();
      retval = ::sendto (s, buf.c_str (), buf.length (), flags, (sockaddr*)&dest_info, sizeof(dest_info));
    }
  else if (data.byte_size () == size_t (data.numel ()))
    {
      const NDArray d1 = data.array_value ();
      const octave_idx_type length = d1.numel ();
      const double* d1fvec = d1.data ();

      OCTAVE_LOCAL_BUFFER (unsigned char, buf, length);
      for (int i = 0 ; i < length; i++)
        buf[i] = (unsigned char)d1fvec[i];
      
      //hmm, flags are set to 0, unlike the call above!
      retval = ::sendto (s, (const char*)buf, data.byte_size (), flags, (sockaddr*)&dest_info, sizeof(dest_info));
    }
  else
    {
      error( "sendto: invalid DATA to send.  Please format it prior to sending" );
      return octave_value ();
    }

  return octave_value (retval);
}

// PKG_ADD: autoload ("recvfrom", which ("socket"));
// PKG_DEL: try; autoload ("recvfrom", which ("socket"), "remove"); catch; end;
// function to receive data over a socket
DEFUN_DLD(recvfrom, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {[@var{data}, @var{count}, @var{src_info}] =} recvfrom (@var{s}, @var{len})\n\
@deftypefnx {Loadable Function} {[@var{data}, @var{count}, @var{src_info}] =} recvfrom (@var{s}, @var{len}, @var{flags})\n\
Read data from specified socket.\n\
\n\
Requests reading @var{len} bytes from the socket @var{s}.\n\
The optional integer @var{flags} parameter can be used to modify the\n\
behaviour of @code{recvfrom}.\n\
\n\
The read data is returned in the uint8 array @var{data}.  The number of\n\
bytes read is returned in @var{count} and a structure with fields addr and port contain the source of the\n\
data.\n\
\n\
You can get non-blocking operation by using the flag @code{MSG_DONTWAIT}\n\
which makes the @code{recvfrom()} call return immediately.  If there is no\n\
data, -1 is returned in count.\n\
\n\
See the @command{recvfrom} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();
  int retval = 0;
  int flags = 0;

  if (nargin < 2 || nargin > 3)
    {
      print_usage ();
      return octave_value ();
    }

  if (nargin > 2)
    {
      if (! args(2).is_real_scalar ())
        {
          error ("recv: FLAGS must be a scalar integer");
          return octave_value ();
        }

      flags = args(2).int_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("recv: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("recv: LEN must be a non-negative integer");
      return octave_value (-1);
    }

  const long len = args(1).int_value ();
  if (len < 0)
    {
      error ("recv: LEN must be a non-negative integer");
      return octave_value(-1);
    }

  struct sockaddr_in src_addr;
#ifndef __WIN32__
  socklen_t addrlen = sizeof(src_addr);
#else
  int addrlen = sizeof(src_addr);
#endif

  OCTAVE_LOCAL_BUFFER (unsigned char, buf, len);
#ifndef __WIN32__
  retval = ::recvfrom( s, buf, len, flags, (sockaddr*)&src_addr, &addrlen );
#else
  retval = ::recvfrom( s, ( char* )buf, len, flags, (sockaddr*)&src_addr, &addrlen );
#endif

  octave_value_list return_list;
  uint8NDArray data;

  octave_scalar_map client_info_map;

  //always return the status in the second output parameter
  return_list(1) = retval;
  return_list(2) = client_info_map;
  if (retval <= 0)
    // We get -1 if an error occurs,or if there is no data and the
    // socket is non-blocking. We should return in both cases.
    // We get 0 if the peer has shut down.
    return_list(0) = data;
  else
    {
      //Normal behaviour. Copy the buffer to the output variable. For
      //backward compatibility, a row vector is returned.
      data.resize (dim_vector (1, retval));
      octave_uint8* data_fvec = data.fortran_vec ();
      for (int i = 0 ; i < retval ; i++)
        data_fvec[i] = buf[i];

      return_list(0) = data;

      client_info_map.assign ("family", octave_value (src_addr.sin_family));
      client_info_map.assign ("port", octave_value (htons(src_addr.sin_port)));
      client_info_map.assign ("addr", octave_value (inet_ntoa(src_addr.sin_addr)));
      return_list(2) = client_info_map;
    }
  return return_list;
}

// PKG_ADD: autoload ("getsockopt", which ("socket"));
// PKG_DEL: try; autoload ("getsockopt", which ("socket"), "remove"); catch; end;
// function to get socket option
DEFUN_DLD(getsockopt,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{data}, @var{status}] =} getsockopt (@var{s}, @var{level}, @var{optname})\n\
Get a socket option value from a socket.\n\
\n\
Returns the value of @var{level} @var{optname} from the socket @var{s}.\n\
\n\
Data type depends on the option used. @var{status} returns as  0 if no error.\n\
\n\
See the @command{getsockopt} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length () != 3)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("getsockopt: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("getsockopt: LEVEL must be a scalar integer");
      return octave_value (-1);
    }

  if (! args(2).is_real_scalar ())
    {
      error ("getsockopt: OPTNAME must be a scalar integer");
      return octave_value (-1);
    }

  const int level = args(1).int_value ();
  const int optname = args(2).int_value ();

  if (level != SOL_SOCKET)
    {
      error ("getsockopt: currently only a level of SOL_SOCKET is supported");
      return octave_value (-1);
    }

  socklen_t optlen;
  SOCK_OPT_TYPE optvalue;
#ifndef __WIN32__
  int ivalue = 0;
#else
  DWORD ivalue = 0;
#endif

  if (optname == SO_KEEPALIVE || optname == SO_REUSEADDR || optname == SO_TYPE || 
      optname == SO_DONTROUTE || optname == SO_BROADCAST || optname == SO_DEBUG)
    {
      optlen = sizeof(ivalue);
      optvalue = (SOCK_OPT_TYPE)&ivalue;
    }
  else
    {
      error ("getsockopt: currently unimplmented or unknown socket optname");
      return octave_value (-1);
    }

  int result = ::getsockopt( s, level, optname, optvalue, &optlen);

  octave_value value;

  if(result == 0)
    {
      if (optname == SO_KEEPALIVE || optname == SO_REUSEADDR || optname == SO_TYPE ||
          optname == SO_DONTROUTE || optname == SO_BROADCAST || optname == SO_DEBUG)
        value = octave_value(ivalue);
    }

  // returns the accepted socket and a clientinfo structure
  octave_value_list return_list;
  return_list(0) = value;
  return_list(1) = octave_value(result);

  return return_list;
}

// PKG_ADD: autoload ("setsockopt", which ("socket"));
// PKG_DEL: try; autoload ("setsockopt", which ("socket"), "remove"); catch; end;
// function to get socket option
DEFUN_DLD(setsockopt,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{status} =} setsockopt (@var{s}, @var{level}, @var{optname}, @var{optvalue})\n\
Set a socket option value on a socket.\n\
\n\
@var{status} returns as  0 if no error.\n\
\n\
See the @command{setsockopt} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length () != 4)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("setsockopt: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("setsockopt: LEVEL must be a scalar integer");
      return octave_value (-1);
    }

  if (! args(2).is_real_scalar ())
    {
      error ("setsockopt: OPTNAME must be a scalar integer");
      return octave_value (-1);
    }

  const int level = args(1).int_value ();
  const int optname = args(2).int_value ();

  if (level != SOL_SOCKET)
    {
      error ("setsockopt: currently only a level of SOL_SOCKET is supported");
      return octave_value (-1);
    }

  socklen_t optlen;
  SOCK_OPT_TYPE optvalue;
#ifndef __WIN32__
  int ivalue = 0;
#else
  DWORD ivalue = 0;
#endif

  if (optname == SO_KEEPALIVE || optname == SO_REUSEADDR || optname == SO_DONTROUTE ||
      optname == SO_BROADCAST || optname == SO_DEBUG)
    {
      if (! args(3).is_real_scalar ())
        {
          error ("setsockopt: OPTVALUE must be a scalar integer");
          return octave_value (-1);
        }

      ivalue = args(3).int_value ();

      optlen = sizeof(ivalue);
      optvalue = (SOCK_OPT_TYPE)&ivalue;
    }
  else if (optname == SO_TYPE)
    {
      error ("setsockopt: can not set SO_TYPE");
      return octave_value (-1);
    }
  else
    {
      error ("setsockopt: currently unimplemented or unknown socket optname");
      return octave_value (-1);
    }

  int result = ::setsockopt( s, level, optname, optvalue, optlen);

  return octave_value(result);
}

// PKG_ADD: autoload ("select", which ("socket"));
// PKG_DEL: try; autoload ("select", which ("socket"), "remove"); catch; end;
// function wait for data on a socket
DEFUN_DLD(select,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{status}, @var{rfdset}, @var{wfdset}, @var{efdset}] =} select (@var{nfds}, @var{rfdset}, @var{wfdset}, @var{efdset}, @var{timeout})\n\
Wait for socket activity on selected sockets.\n\
\n\
The fdsets are vectors of fds to check, for example [1 2 3]. Empty vectors equate to null.\n\
\n\
nfds tests file descriptions in the range of 0 - nfds-1.\n\
\n\
Timeout is can be either an real value for number of seconds, a struct with a tm_sec and tm_usec fields, or empty set for null.\n\
\n\
@var{status} returns as  0 if timeout, or number of waiting sockets if ok.\n\
\n\
See the @command{select} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length () != 5)
    {
      print_usage ();
      return octave_value ();
    }

  if (! args(0).is_real_scalar ())
    {
      error ("select: NFDS must be a scalar integer");
      return octave_value (-1);
    }

  if (! args(1).isempty () && ! args(1).is_real_matrix () && ! args(1).is_real_scalar ())
    {
      error ("select: RFDS must be a vector");
      return octave_value (-1);
    }

  if (! args(2).isempty () && ! args(2).is_real_matrix () && ! args(2).is_real_scalar ())
    {
      error ("select: WFDS must be a vector");
      return octave_value (-1);
    }

  if (! args(3).isempty () && ! args(3).is_real_matrix () && ! args(3).is_real_scalar ())
    {
      error ("select: EFDS must be a vector");
      return octave_value (-1);
    }

  // timeout
  if (! args(4).isempty ())
    { 
      if (!args(4).is_real_scalar ())
        {
          if (!args(4).isstruct ())
	    {
               error ("select: TIMEOUT must be a real value or struct");
	    }
	  else
            {
               const octave_scalar_map timeout = args(4).scalar_map_value ();

               if(! (timeout.contains ("tv_sec") && timeout.contains ("tv_usec")))
                 {
                    error ("select: TIMEOUT must have integer fields \"tv_sec\" and \"tv_usec\"");
                    return octave_value ();
                 }

               if(! (timeout.getfield ("tv_sec").is_real_scalar() && timeout.getfield ("tv_usec").is_real_scalar()))
                 {
                   error ("select: TIMEOUT must have integer fields \"tv_sec\" and \"tv_usec\"");
                   return octave_value ();
                 }
            }
	}
    }

  // verify all the inputs are valid sockets ?
  fd_set wfdset, rfdset, efdset;
  fd_set *wfdsetp, *rfdsetp, *efdsetp;
  FD_ZERO (&wfdset);
  FD_ZERO (&rfdset);
  FD_ZERO (&efdset);

  const int nfds = args(0).int_value ();

  if (args(1).isempty())
    {
      rfdsetp = NULL;
    }
  else
    {
      rfdsetp = &rfdset;

      const Array<double> d1 = args(1).vector_value();

      for (octave_idx_type i = 0 ; i < d1.numel(); i++)
        {
          FD_SET((int)d1(i), rfdsetp);
        }
    }

  if (args(2).isempty())
    {
      wfdsetp = NULL;
    }
  else
    {
      wfdsetp = &wfdset;

      const Array<double> d1 = args(2).vector_value();

      for (octave_idx_type i = 0 ; i < d1.numel(); i++)
        {
          FD_SET((int)d1(i), wfdsetp);
        }
    }

  if (args(3).isempty())
    {
      efdsetp = NULL;
    }
  else
    {
      efdsetp = &efdset;

      const Array<double> d1 = args(3).vector_value();

      for (octave_idx_type i = 0 ; i < d1.numel(); i++)
        {
          FD_SET((int)d1(i), efdsetp);
        }
    }

  struct timeval tv;
  struct timeval *tvp;

  if (args(4).isempty ())
    { 
      tvp = NULL;
    }
  else if (args(4).is_real_scalar ())
    {
      tvp = &tv;
      double ivalue, fvalue;
      fvalue = modf(args(4).double_value(), &ivalue);
      tv.tv_sec = (long)ivalue;
      tv.tv_usec = (long)(fvalue * 1000000L);
    }
  else
   {
      tvp = &tv;

      const octave_scalar_map timeout = args(4).scalar_map_value ();

      tv.tv_sec = timeout.getfield ("tv_sec").long_value();
      tv.tv_usec = timeout.getfield ("tv_usec").long_value();
    }

  octave_value rret = Matrix(0,0);
  octave_value wret = Matrix(0,0);
  octave_value eret = Matrix(0,0);

  int result = ::select( nfds, rfdsetp, wfdsetp, efdsetp, tvp);

  if (result > 0)
    {
      if (! args(1).isempty())
        {
          const Array<double> d1 = args(1).vector_value();
          std::vector<double> selfd;

          for (octave_idx_type i = 0 ; i < d1.numel(); i++)
          {
            if (FD_ISSET((int)d1(i), rfdsetp))
	    {
              selfd.push_back((int)d1(i));
	    }
          }
          MArray<double> arr(dim_vector(1,selfd.size()));
          for (octave_idx_type i = 0 ; i < (octave_idx_type)selfd.size(); i++)
	    {
              arr(i) = selfd[i]; 
	    }
	  if (selfd.size() > 0)
	    rret = arr;
        }

      if (! args(2).isempty())
        {
          const Array<double> d1 = args(2).vector_value();
          std::vector<double> selfd;

          for (octave_idx_type i = 0 ; i < d1.numel(); i++)
          {
            if (FD_ISSET((int)d1(i), wfdsetp))
	    {
              selfd.push_back((int)d1(i));
	    }
          }
          MArray<double> arr(dim_vector(1,selfd.size()));
          for (octave_idx_type i = 0 ; i < (octave_idx_type)selfd.size(); i++)
	    {
              arr(i) = selfd[i]; 
	    }
	  if (selfd.size() > 0)
	    wret = arr;
        }

      if (! args(3).isempty())
        {
          const Array<double> d1 = args(3).vector_value();
          std::vector<double> selfd;

          for (octave_idx_type i = 0 ; i < d1.numel(); i++)
          {
            if (FD_ISSET((int)d1(i), efdsetp))
	    {
              selfd.push_back((int)d1(i));
	    }
          }
          MArray<double> arr(dim_vector(1,selfd.size()));
          for (octave_idx_type i = 0 ; i < (octave_idx_type)selfd.size(); i++)
	    {
              arr(i) = selfd[i]; 
	    }

	  if (selfd.size() > 0)
	    eret = arr;
        }
    }

  octave_value_list return_list;

  return_list(0) = octave_value(result);
  return_list(1) = octave_value(rret);
  return_list(2) = octave_value(wret);
  return_list(3) = octave_value(eret);

  return return_list;
}

// PKG_ADD: autoload ("shutdown", which ("socket"));
// PKG_DEL: try; autoload ("shutdown", which ("socket"), "remove"); catch; end;
// function to listen on a socket
DEFUN_DLD(shutdown, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} shutdown (@var{s}, @var{how})\n\
Shutdown all or part of a connection of a socket.\n\
\n\
On success, zero is returned.\n\
\n\
See the @command{shutdown} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length() != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (s == -1)
    {
      error ("shutdown: S must be a valid socket");
      return octave_value ();
    }

  if (! args(1).is_real_scalar ())
    {
      error ("shutdown: HOW must be an integer scalar");
      return octave_value (-1);
    }

  const int how = args(1).int_value ();

  if(how < 0 || how > 2)
    {
      error ("shutdown: HOW must be an integer scalar between 0 and 2");
      return octave_value (-1);
    }

  const int retval = ::shutdown (s, how);
  if (retval == -1)
      error ("shutdown failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

/*

%!test
%! ## Server socket
%! server = socket (AF_INET, SOCK_STREAM, 0);
%! assert (server >= 0);
%!
%! rc = bind (server, 9001);
%! assert (rc, 0);
%!
%! rc = listen (server, 1);
%! assert (rc, 0);
%!
%! ## Client socket
%! client = socket (AF_INET, SOCK_STREAM, 0);
%! assert (client >= 0);
%!
%! ## Create the connection and accept the connection
%! server_info = struct ("addr", "127.0.0.1", "port", 9001);
%! rc = connect (client, server_info);
%! assert (rc, 0);
%!
%! server_data = accept (server);
%! assert (server_data >= 0);
%!
%! ## Send and receive data
%!
%! ## Send as string from client
%! msg = "Hello socket-land!";
%! rc = send (client, msg);
%! assert (rc,length (msg));
%!
%! ## Receive at server
%! [msg_s, len_s] = recv (server_data, 100);
%! assert (msg_s != -1);
%! assert (len_s, length (msg));
%!
%! ## Send back out from server
%! rc = send (server_data, msg_s);
%! assert (rc, length (msg_s));
%!
%! ## Receive at client
%! [msg_c, len_c] = recv (client, 100);
%! assert (msg_c != -1);
%! assert (len_c, length (msg));
%!
%! ## Compare original string with recv string
%! assert (msg, num2str (msg_c, "%c"));
%!
%! assert (shutdown (client, SHUT_WR), 0);
%! assert (shutdown (client, SHUT_RD), 0);
%! assert (shutdown (client, SHUT_RDWR), 0);
%!
%! assert (disconnect (client), 0);
%! assert (disconnect (server_data), 0);
%! assert (disconnect (server), 0);

%!test
%! ## UDP
%! sock = socket (AF_INET, SOCK_DGRAM, 0);
%! assert (sock >= 0);
%!
%! rc = bind (sock, 9001);
%! assert (rc, 0);
%!
%! msg = "Hello socket-land!";
%! addrinfo = struct ("addr", "127.0.0.1", "port", 9001);
%! rc = sendto (sock, msg, 0, addrinfo);
%! assert (rc,length (msg));
%!
%! [msg_c, len_c, addr_c] = recvfrom (sock, 100);
%! assert (msg_c != -1);
%! assert (len_c, length (msg));
%! assert (addr_c.port, 9001);
%!
%! assert (msg, num2str (msg_c, "%c"));
%!
%! assert (disconnect (sock), 0);

%!test
%! assert (SOL_SOCKET != 0)
%! assert (MSG_WAITALL != 0)
%! assert (MSG_PEEK != 0)
%! assert (SO_REUSEADDR != 0)
%! assert (SO_KEEPALIVE != 0)
%! assert (SO_TYPE != 0)
%! assert (SHUT_RD, 0)
%! assert (SHUT_WR, 1)
%! assert (SHUT_RDWR, 2)

%!test
%! ## select
%! sock = socket (AF_INET, SOCK_DGRAM, 0);
%! assert (sock >= 0);
%!
%! rc = bind (sock, 9001);
%! assert (rc, 0);
%!
%! [ret, rdfs, wdfs, edfs] = select(sock+1, [sock], [sock], [sock], 1);
%! assert(ret, 1);
%! assert(rdfs, []);
%! # initial open
%! assert(wdfs, [sock]);
%! assert(edfs, []);
%!
%! start = tic;
%! [ret, rdfs, wdfs, edfs] = select(sock+1, [sock], [], [], 1);
%! timeout = toc(start);
%! assert(ret, 0);
%! assert(rdfs, []);
%! assert(wdfs, []);
%! assert(edfs, []);
%! assert(timeout, 1, 0.01);
%!
%! timeout = struct ("tv_sec", 2, "tv_usec", 0);
%! start = tic;
%! [ret, rdfs, wdfs, edfs] = select(sock+1, [sock], [], [], timeout);
%! timeout = toc(start);
%! assert(ret, 0);
%! assert(rdfs, []);
%! assert(wdfs, []);
%! assert(edfs, []);
%! assert(timeout, 2, 0.01);
%!
%! msg = "Hello socket-land!";
%! addrinfo = struct ("addr", "127.0.0.1", "port", 9001);
%! rc = sendto (sock, msg, 0, addrinfo);
%! assert (rc,length (msg));
%! pause(1);
%!
%! [ret, rdfs, wdfs, edfs] = select(sock+1, [sock], [], [], .2);
%! assert(ret, 1);
%! assert(rdfs, [sock]);
%! assert(wdfs, []);
%! assert(edfs, []);
%!
%! [msg_c, len_c, addr_c] = recvfrom (sock, 100);
%! assert (msg_c != -1);
%! assert (len_c, length (msg));
%! assert (addr_c.port, 9001);
%!
%! [ret, rdfs, wdfs, edfs] = select(sock+1, [sock], [], [], .1);
%! assert(ret, 0);
%! assert(rdfs, []);
%! assert(wdfs, []);
%! assert(edfs, []);
%!
%! assert (disconnect (sock), 0);
*/

