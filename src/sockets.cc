// Copyright (C) John Swensen <jpswensen@comcast.net>
// Copyright (C) 2007 Tom Holroyd <tomh@kurage.nimh.nih.gov>
// Copyright (C) 2009 Paul Dreik <slask@pauldreik.se>
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

// C++ STL includes
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// Octave Includes
#include <octave/oct.h>
#include <octave/parse.h>
#include <octave/toplev.h>
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
#else
typedef unsigned int socklen_t;
#include <winsock2.h>
#endif
#include <errno.h>

template <class T>
std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
{
  std::ostringstream oss;
  oss << f << t;
  return oss.str();
}

#define OCTAVE_TYPE_CONV_HELPER(VAR_IN, VAR_OUT, NAME, MATRIX_RESULT_T, SCALAR_RESULT_T) \
 \
      int t_arg = VAR_IN.type_id (); \
 \
      int t_result = MATRIX_RESULT_T::static_type_id (); \
 \
      if (t_arg == t_result || VAR_IN.class_name () == #NAME) \
	{ \
	  VAR_OUT = VAR_IN; \
	} \
      else \
	{ \
	  octave_base_value::type_conv_fcn cf \
	    = octave_value_typeinfo::lookup_type_conv_op (t_arg, t_result); \
 \
	  if (cf) \
	    { \
	      octave_base_value *tmp (cf (*(VAR_IN.internal_rep ()))); \
 \
	      if (tmp) \
		{ \
		  VAR_OUT = octave_value (tmp); \
 \
		  VAR_OUT.maybe_mutate (); \
		} \
	    } \
	  else \
	    { \
	      std::string arg_tname = VAR_IN.type_name (); \
 \
	      std::string result_tname = VAR_IN.numel () == 1 \
		? SCALAR_RESULT_T::static_type_name () \
		: MATRIX_RESULT_T::static_type_name (); \
 \
	      gripe_invalid_conversion (arg_tname, result_tname); \
	    } \
	}


#define OCTAVE_TYPE_CONV(VAR_IN, VAR_OUT, NAME) \
  OCTAVE_TYPE_CONV_HELPER (VAR_IN, VAR_OUT, NAME, octave_ ## NAME ## _matrix, \
			  octave_ ## NAME ## _scalar)

// Derive an octave_socket class from octave_base_value
class octave_socket : public octave_base_value
{
private:

  /**
   * Socket file descriptor
   */
  int sock_fd;

public:

  /**
   * Default constructor.  Must be defined, but never used.
   */
  octave_socket() {}

  /**
   * Constructor used to set the fd on creation.
   */
  octave_socket( int fd );

  /**
   * Constructor used to create the socket.
   */
  octave_socket( int domain, int type, int protocol );

  /**
   * Destructor.
   */
  ~octave_socket();

  /**
   * Various properties of the octave_socket datatype.
   */
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool print_as_scalar (void) const { return true;}

  // Still undefined.
  //bool is_data_available() {};

  /**
   * Overloaded methods to print the fd as the socket id
   */
  void print (ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  /**
   * Utility function for retrieving the socket fd.
   */
  int get_sock_fd(void) { return sock_fd;};

  void remove_sock_fd(void);

  virtual double scalar_value (bool frc_str_conv = false) const
  {
    return (double)sock_fd;
  }

  double socket_value () const
  {
    return (double)sock_fd;
  }

private:
  DECLARE_OCTAVE_ALLOCATOR
  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};


DEFBINOP_OP (lt_sock_s, socket, scalar, <)
DEFBINOP_OP (le_sock_s, socket, scalar, <=)
DEFBINOP_OP (eq_sock_s, socket, scalar, ==)
DEFBINOP_OP (ge_sock_s, socket, scalar, >=)
DEFBINOP_OP (gt_sock_s, socket, scalar, >)
DEFBINOP_OP (ne_sock_s, socket, scalar, !=)

DEFBINOP_OP (lt_s_sock, scalar, socket, <)
DEFBINOP_OP (le_s_sock, scalar, socket, <=)
DEFBINOP_OP (eq_s_sock, scalar, socket, ==)
DEFBINOP_OP (ge_s_sock, scalar, socket, >=)
DEFBINOP_OP (gt_s_sock, scalar, socket, >)
DEFBINOP_OP (ne_s_sock, scalar, socket, !=)

void install_socket_ops(void)
{
  INSTALL_BINOP (op_lt, octave_socket, octave_scalar, lt_sock_s);
  INSTALL_BINOP (op_le, octave_socket, octave_scalar, le_sock_s);
  INSTALL_BINOP (op_eq, octave_socket, octave_scalar, eq_sock_s);
  INSTALL_BINOP (op_ge, octave_socket, octave_scalar, ge_sock_s);
  INSTALL_BINOP (op_gt, octave_socket, octave_scalar, gt_sock_s);
  INSTALL_BINOP (op_ne, octave_socket, octave_scalar, ne_sock_s);

  INSTALL_BINOP (op_lt, octave_scalar, octave_socket, lt_s_sock);
  INSTALL_BINOP (op_le, octave_scalar, octave_socket, le_s_sock);
  INSTALL_BINOP (op_eq, octave_scalar, octave_socket, eq_s_sock);
  INSTALL_BINOP (op_ge, octave_scalar, octave_socket, ge_s_sock);
  INSTALL_BINOP (op_gt, octave_scalar, octave_socket, gt_s_sock);
  INSTALL_BINOP (op_ne, octave_scalar, octave_socket, ne_s_sock);
}


DEFINE_OCTAVE_ALLOCATOR (octave_socket);
DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_socket, "octave_socket", "octave_socket");



// This macro must start with DEFUN_DLD so that the automatic collection
// of function helps can take place. To get the code working in
// multiple versions of octave, we have to check the version number.
#if !defined(MINORVERSION) || !defined(MAJORVERSION)
# error "please define MAJORVERSION and MINORVERSION to the octave version numbers"
#endif

#if MAJORVERSION==3 && MINORVERSION<2
# define DEFUN_DLD_SOCKET_CONSTANT(name, help )				\
  DEFUNX_DLD ( #name, F ## name, FS ## name, args, nargout, help)	\
  {    return octave_value( name ); };					
#else
# define DEFUN_DLD_SOCKET_CONSTANT(name, help )				\
  DEFUNX_DLD ( #name, F ## name, G ## name, args, nargout, help)	\
  {    return octave_value( name ); };					
#endif


// PKG_ADD: autoload ("AF_UNIX", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(AF_UNIX, "socket constant" );
#ifndef __WIN32__
// PKG_ADD: autoload ("AF_LOCAL", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(AF_LOCAL, "socket constant" );
#else
DEFUNX_DLD ("AF_LOCAL", FAF_LOCAL, GAF_LOCAL, args, nargout, "(not supported)")
{ error( "AF_LOCAL address family not supported on this platform" );
  return octave_value(); };
#endif
// PKG_ADD: autoload ("AF_INET", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(AF_INET, "socket constant" );
// PKG_ADD: autoload ("AF_APPLETALK", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(AF_APPLETALK, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_INET6, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_IPX, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_NETLINK, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_X25, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_AX25, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_ATMPVC, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_PACKET, "socket constant" );

// PKG_ADD: autoload ("SOCK_STREAM", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(SOCK_STREAM, "socket constant" );
// PKG_ADD: autoload ("SOCK_DGRAM", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(SOCK_DGRAM, "socket constant" );
// PKG_ADD: autoload ("SOCK_SEQPACKET", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(SOCK_SEQPACKET, "socket constant" );
// PKG_ADD: autoload ("SOCK_RAW", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RAW, "socket constant" );
// PKG_ADD: autoload ("SOCK_RDM", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RDM, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(SOCK_PACKET, "socket constant" );

// PKG_ADD: autoload ("MSG_PEEK", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(MSG_PEEK, "socket constant" );
#ifdef MSG_DONTWAIT
// PKG_ADD: autoload ("MSG_DONTWAIT", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(MSG_DONTWAIT, "socket constant" );
#endif
#ifdef MSG_WAITALL
// PKG_ADD: autoload ("MSG_WAITALL", "sockets.oct");
DEFUN_DLD_SOCKET_CONSTANT(MSG_WAITALL, "socket constant" );
#endif

std::map< int, octave_socket * > socket_map;
static bool type_loaded = false;


//////////////////////////////////////////////////////////////////////////////////////////
octave_socket::octave_socket( int fd )
{
  sock_fd = fd;
  socket_map[sock_fd] = this;
}


//////////////////////////////////////////////////////////////////////////////////////////
octave_socket::octave_socket( int domain, int type, int protocol )
{
  sock_fd = ::socket( domain, type, protocol );
  if ( sock_fd == -1 )
  {
    error( "octave_socket: Error creating socket" );
  }
  else
  {
    socket_map[sock_fd] = this;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////
octave_socket::~octave_socket()
{
	remove_sock_fd();
}


//////////////////////////////////////////////////////////////////////////////////////////
void octave_socket::print (ostream& os, bool pr_as_read_syntax ) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void octave_socket::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << sock_fd;
}

void octave_socket::remove_sock_fd(void)
{
#ifndef __WIN32__
	::close( sock_fd );
#else
	::closesocket( sock_fd );
#endif
	socket_map.erase( sock_fd );
	sock_fd = -1;
}


// PKG_ADD: autoload ("socket", "sockets.oct");
// Function to create a socket
DEFUN_DLD(socket,args,nargout,
	  "s=socket(domain,type,protocol)\n"
	  "Creates a socket s. Domain is an integer, where the value AF_INET\n"
	  "can be used to create an IPv4 socket.\n"
	  "type is an integer describing the socket. When using IP, specifying "
	  "SOCK_STREAM gives a TCP socket.\n"
	  "protocol is currently not used and should be 0 if specified.\n"
	  "\n"
	  "If no input arguments are given, default values AF_INET and \n"
	  "SOCK_STREAM are used.\n"
	  "See the local socket() reference for more details.\n")
{
  int domain    = AF_INET;
  int type      = SOCK_STREAM;
  int protocol  = 0;

  if ( !type_loaded )
  {
    octave_socket::register_type ();
    install_socket_ops();
    type_loaded = true;
#ifdef __WIN32__
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
      error( "could not initialize winsock library" );
      return octave_value();
    }
#endif
  }

  // Convert the arguments to their #define'd value
  if ( args.length() > 0 )
  {
		domain = args(0).int_value();
  }

  if ( args.length() > 1 )
  {
		type = args(1).int_value();
  }

  if ( args.length() > 2 )
  {
		protocol = args(2).int_value();
		if( protocol != 0 )
		{
			error( "For now, protocol must always be 0 (zero)" );
	return octave_value(-1);
		}
  }

  // Create the new socket
  octave_socket* retval = new octave_socket( domain, type, protocol );
  if ( nargout > 0 && retval->get_sock_fd() != -1 )
    return octave_value(retval);

  return octave_value();

}

// PKG_ADD: autoload ("connect", "sockets.oct");
// function to create an outgoing connection
DEFUN_DLD(connect,args,nargout, \
	  "status=connect(s,serverinfo)\n"
	  "Connects the socket s following the information\n"
	  "in the struct serverinfo.\n"
	  "serverinfo shall contain the following fields:\n"
	  " addr - a string with the host name to connect to\n"
	  " port - the port number to connect to (an integer)\n"
	  "\n"
	  "On successful connect, the returned status is zero.\n"
	  "\n"
	  "See the connect() man pages for further details.\n")
{
  int retval = -1;
  struct sockaddr_in serverInfo;
  struct hostent*    hostInfo;

  if ( args.length() != 2 )
  {
    error("connect: you must specify 2 parameters.");
    return octave_value(-1);
  }

  // Extract information about the server to connect to.
  const octave_base_value& struct_serverInfo = args(1).get_rep();
  octave_struct& addrInfo = ((octave_struct&)struct_serverInfo);

#if MINORVERSION <= 2
  string addr = addrInfo.map_value().stringfield("addr");
  int port = addrInfo.map_value().intfield("port");
#else
  const Cell addr_cell = addrInfo.map_value().getfield ("addr");
  string addr;
  if (addr_cell.numel () == 1 && addr_cell (0).is_string ())
    {
      addr = addr_cell (0).string_value ();
    }
  else
    {
      error ("connect: invalid input: no 'addr' field in serverinfo.");
      return octave_value (-1);
    }

  const Cell port_cell = addrInfo.map_value().getfield ("port");
  int port;
  if (port_cell.numel () == 1 && port_cell (0).is_numeric_type ())
    {
      port = port_cell (0).int_value ();
    }
  else
    {
      error ("connect: invalid input: no 'port' field in serverinfo.");
      return octave_value (-1);
    }
#endif


  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting an octave_socket or integer");
    return octave_value(-1);
  }

  // Fill in the server info struct
  serverInfo.sin_family = AF_INET;
  if ( addr.length() > 0 )
  {
    hostInfo = gethostbyname( addr.c_str() );
    if ( hostInfo )
    {
      serverInfo.sin_addr.s_addr = *((long*)hostInfo->h_addr_list[0]);
    }
    else
    {
      error( "connect: error in gethostbyname()" );
      return octave_value(-1);
    }
  }
  else
  {
    error( "connect: empty address" );
    return octave_value(-1);
  }
  serverInfo.sin_port = htons(port);

  retval = connect( s->get_sock_fd(), (struct sockaddr*)&serverInfo, sizeof(struct sockaddr) );

  return octave_value(retval);
}

// PKG_ADD: autoload ("disconnect", "sockets.oct");
// function to disconnect asocket
DEFUN_DLD(disconnect,args,nargout, \
	  "disconnect(s)\n"
	  "Disconnects the socket s.\n"
	  "Since we can't call fclose on the file descriptor directly,\n"
	  "use this function to disconnect the socket.")
{
  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting an octave_socket or integer");
    return octave_value(-1);
  }

  s->remove_sock_fd();

  return octave_value(0);

}

// PKG_ADD: autoload ("gethostbyname", "sockets.oct");
// function to get a host number from a host name
DEFUN_DLD(gethostbyname,args,nargout, \
	  "addr=gethostbyname(hostname)\n"
	  "Returns an IP adress addr for a host name.\n"
	  "Example:\n"
	  "addr=gethostbyname('localhost')\n"
	  "addr = 127.0.0.1\n"
	  "\n"
	  "See the gethostbyname() man pages for details.")
{
  int nargin = args.length ();
  struct hostent*    hostInfo = NULL;
  octave_value retval;

  if (nargin != 1)
    print_usage ();
  else if ( args(0).is_string() )
    {
      string_vector host_list;
      string addr = args(0).string_value();
      hostInfo = gethostbyname( addr.c_str() );
      if ( hostInfo )
	{
	  for ( int i = 0 ; i < hostInfo->h_length/4 ; i++ )
	    {
	      string temp_addr = string(  inet_ntoa( *(struct in_addr*)hostInfo->h_addr_list[i] ));
	      host_list.append( temp_addr );
	    }
	}
      retval = octave_value (host_list);
    }
  else
    print_usage ();

  return retval;
}

// PKG_ADD: autoload ("send", "sockets.oct");
// function to send data over a socket
DEFUN_DLD(send,args,nargout, \
	  "send(s,data,flags)\n"
	  "Sends data on socket s. data should be an uint8 array or\n"
	  "a string.\n"
	  "See the send() man pages for further details.\n")
{
  int retval = 0;
  int flags = 0;

  if ( args.length() < 2 )
  {
    error( "send: you must specify two or more parameters");
    return octave_value(-1);
  }

  if ( args.length() > 2 && args(2).is_scalar_type() )
    flags = args(2).int_value();


  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting an octave_socket or integer");
    return octave_value(-1);
  }

  // Extract the data from the octave variable and send it
  const octave_base_value& data = args(1).get_rep();
  if ( data.is_string() )
  {
    string buf = data.string_value();
    retval = ::send( s->get_sock_fd(), buf.c_str(), buf.length(), flags );
  }
  else if ( data.byte_size() == data.numel() )
  {
    NDArray d1 = data.array_value();
    unsigned char* buf = new unsigned char[ d1.length() ];
    for ( int i = 0 ; i < d1.length() ; i++ )
      buf[i] = (unsigned char)d1(i);
    retval = ::send( s->get_sock_fd(), (const char*)buf, data.byte_size(), 0 );
    delete[] buf;
  }
  else
  {
    error( "connect: you have specified an invalid data type to send.  Please format it prior to sending" );
    return octave_value(-1);
  }

  return octave_value(retval);
}

// PKG_ADD: autoload ("recv", "sockets.oct");
// function to receive data over a socket
DEFUN_DLD(recv,args,nargout, \
	  "[data,count]=recv(s,len,flags)\n"
	  "Requests reading len bytes from the socket s.\n"
	  "The integer flags parameter can be used to modify the behaviour\n"
	  "of recv.\n"
	  "\n"
	  "The read data is returned in an uint8 array data. The number of\n"
	  "bytes read is returned in count.\n"
	  "\n"
	  "You can get non-blocking operation by using the flag MSG_DONTWAIT\n"
	  "which makes the recv() call return immediately. If there are no\n"
	  "data, -1 is returned in count.\n"
	  "See the recv() man pages for further details.\n")
{
  if(nargout>2) 
    {
      error("recv: please use at most two output arguments.");
      return octave_value(-1);
    }

  int retval = 0;
  int flags = 0;

  if ( args.length() < 2 )
  {
    error( "recv: you must specify 2 parameters" );
    return octave_value(-1);
  }

  if ( args.length() > 2 && args(2).is_scalar_type() )
    flags = args(2).int_value();

  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
    {//what happens if fd does not exist in socket_map?
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("recv: expecting an octave_socket or integer");
    return octave_value(-1);
  }

  long len = args(1).int_value();
  if(len<0) {
    error("recv: negative receive length requested");
    return octave_value(-1);
  }

  unsigned char* buf = new unsigned char[ len ];
#ifndef __WIN32__
  retval = ::recv( s->get_sock_fd(), buf, len, flags );
#else
  retval = ::recv( s->get_sock_fd(), ( char* )buf, len, flags );
#endif

  octave_value_list return_list;
  uint8NDArray data;

  //always return the status in the second output parameter
  return_list(1) = retval; 
  if(retval<0) {
    //We get -1 if an error occurs,or if there is no data and the
    //socket is non-blocking. We should return in both cases.
    return_list(0) = data;
  } else if (0==retval) {
    //The peer has shut down.
    return_list(0) = data;
  } else {
    //Normal behaviour. Copy the buffer to the output variable. For
    //backward compatibility, a row vector is returned.
    dim_vector d;
    d(0)=1;
    d(1)=retval;
    data.resize(d);

    //this could possibly be made more efficient with memcpy and
    //fortran_vec() instead.
    for ( int i = 0 ; i < retval ; i++ )
      data(i) = buf[i];
    
    return_list(0) = data;
  }

  delete[] buf;
  
  return return_list;
}

// PKG_ADD: autoload ("bind", "sockets.oct");
// function to bind a socket
DEFUN_DLD(bind,args,nargout, \
	  "bind(s,portnumber)\n"
	  "binds the sockets to port portnumber.\n"
	  "See the bind() man pages for further details.\n")
{
  int retval = 0;
  if ( args.length() != 2 )
  {
    error( "bind: you must specify 2 parameters" );
    return octave_value(-1);
  }

  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting an octave_socket or integer");
    return octave_value(-1);
  }


  long port = args(1).int_value();

  struct sockaddr_in serverInfo;
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons( port );
  serverInfo.sin_addr.s_addr = INADDR_ANY;

  retval = ::bind( s->get_sock_fd(), (struct sockaddr *)&serverInfo, sizeof(serverInfo) );

  return octave_value(retval);
}

// PKG_ADD: autoload ("listen", "sockets.oct");
// function to listen on a socket
DEFUN_DLD(listen,args,nargout, \
	  "r=listen(s,backlog)\n"
	  "Listens on socket s for connections. backlog specifies\n"
	  "how large the queue of incoming connections is allowed to\n"
	  "grow.\n"
	  "On success, zero is returned.\n"
	  "See the listen() man pages for details.\n")
{
  int retval = 0;
  if ( args.length() != 2 )
  {
    error( "listen: you must specify 2 parameters" );
    return octave_value(-1);
  }

  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting an octave_socket or integer");
    return octave_value(-1);
  }

  int backlog = args(1).int_value();
//  octave_stdout << "BACKLOG: " << backlog << endl;

  if (! error_state)
    retval = ::listen( s->get_sock_fd(), backlog );

  return octave_value(retval);
}

// PKG_ADD: autoload ("accept", "sockets.oct");
// function to accept on a listening socket
DEFUN_DLD(accept,args,nargout, \
	  "[client,info]=accept(s)\n"
	  "Accepts an incoming connection on the socket s.\n"
	  "The newly created socket is returned in client, and\n"
	  "associated information in a struct info.\n"
	  "See the accept() man pages for details.\n")
{
  struct sockaddr_in clientInfo;
  socklen_t clientLen = sizeof(struct sockaddr_in);

  if ( args.length() < 1 )
  {
    error( "accept: you must specify 1 parameter" );
    return octave_value(-1);
  }

  // Determine the socket on which to operate
  octave_socket* s = NULL;
  if ( args(0).type_id() == octave_socket::static_type_id() )
  {
    const octave_base_value& rep = args(0).get_rep();
    s = &((octave_socket &)rep);
  }
  else if ( args(0).is_scalar_type() )
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("accept: expecting an octave_socket or integer");
    return octave_value(-1);
  }

#ifndef __WIN32__
  int fd = ::accept( s->get_sock_fd(), (struct sockaddr *)&clientInfo, &clientLen );
#else
  int fd = ::accept( s->get_sock_fd(), (struct sockaddr *)&clientInfo, ( int* )&clientLen );
#endif
  if ( fd != -1 )
  {
    // create the octave_socket object and set the fd
    octave_socket* retobj = new octave_socket(fd);

    // place the client information into a structure
    Octave_map client_info_map;
    client_info_map.assign("sin_family", octave_value(clientInfo.sin_family));
    client_info_map.assign("sin_port", octave_value(clientInfo.sin_port));
    client_info_map.assign("sin_addr", octave_value( inet_ntoa(clientInfo.sin_addr)));

    // returns the accepted socket and a clientinfo structure
    octave_value_list return_list;
    return_list(0) = octave_value(retobj);
    return_list(1) = client_info_map;

    return return_list;
  }
  else
  {
    ostringstream os;
    os << "accept: failed with errno = " << errno;
    error(os.str().c_str());
    return octave_value(fd);
  }
}


// PKG_ADD: autoload ("load_socket_constants", "sockets.oct");
// function to load socket constants
DEFUN_DLD(load_socket_constants,args,nargout, \
	  "Loads various socket constants like AF_INET, SOCK_STREAM, etc.\n")
{
  octave_socket temp();
  return octave_value();
}

