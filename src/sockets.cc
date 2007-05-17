
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
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
  bool is_data_available() {};

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
// of function helps can take place.
#define DEFUN_DLD_SOCKET_CONSTANT(name, help ) \
DEFUNX_DLD ( #name, F ## name, FS ## name, args, nargout, help) \
{ return octave_value( name ); };

DEFUN_DLD_SOCKET_CONSTANT(AF_UNIX, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(AF_LOCAL, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(AF_INET, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(AF_APPLETALK, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_INET6, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_IPX, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_NETLINK, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_X25, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_AX25, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_ATMPVC, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(AF_PACKET, "socket constant" );

DEFUN_DLD_SOCKET_CONSTANT(SOCK_STREAM, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(SOCK_DGRAM, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(SOCK_SEQPACKET, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RAW, "socket constant" );
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RDM, "socket constant" );
//DEFUN_DLD_SOCKET_CONSTANT(SOCK_PACKET, "socket constant" );


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
	::close( sock_fd );
	socket_map.erase( sock_fd );
	sock_fd = -1;
}



// Function to create a socket
DEFUN_DLD(socket,args,nargout,"socket(int,int,int)\nSee the socket() man pages\n")
{
  int domain    = AF_INET;
  int type      = SOCK_STREAM;
  int protocol  = 0;

  if ( !type_loaded )
  {
    octave_socket::register_type ();
    install_socket_ops();
    type_loaded = true;
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

// function to create an outgoing connection
DEFUN_DLD(connect,args,nargout, \
	  "connect(octave_socket,struct)\nSee the connect() man pages")
{
  int retval = -1;
  struct sockaddr_in serverInfo;
  struct hostent*    hostInfo;

  if ( args.length() < 2 )
  {
    error("connect: you must specify 2 paramters");
    return octave_value(-1);
  }

  // Extract information about the server to connect to.
  const octave_base_value& struct_serverInfo = args(1).get_rep();
  octave_struct& addrInfo = ((octave_struct&)struct_serverInfo);

  string addr = addrInfo.map_value().stringfield("addr");
  int port = addrInfo.map_value().intfield("port");

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
    error("connect: expecting a octave_socket or integer");
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

// function to disconnect asocket
DEFUN_DLD(disconnect,args,nargout, \
	  "disconnect(octave_socket)\nSince we can't call fclose on the fd directly, use this to disconnect")
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
    error("connect: expecting a octave_socket or integer");
    return octave_value(-1);
  }

  s->remove_sock_fd();

  return octave_value(0);

}

// function to get a host number from a host name
DEFUN_DLD(gethostbyname,args,nargout, \
	  "gethostbyname(string)\nSee the gethostbyname() man pages")
{
  struct hostent*    hostInfo = NULL;
  string_vector host_list;


  if ( args(0).is_string() )
  {
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
  }

  return octave_value(host_list);
}

// function to send data over a socket
DEFUN_DLD(send,args,nargout, \
	  "send(octave_socket,octave_value)\nSee the send() man pages.  This will only allow the" \
	  " user to send uint8 arrays or strings")
{
  int retval = 0;
  int flags = 0;

  if ( args.length() < 2 )
  {
    error( "send: you must specify 2 parameters");
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
    error("connect: expecting a octave_socket or integer");
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
    delete buf;
  }
  else
  {
    error( "connect: you have specified an invalid data type to send.  Please format it prior to sending" );
    return octave_value(-1);
  }

  return octave_value(retval);
}

// function to receive data over a socket
DEFUN_DLD(recv,args,nargout, \
	  "recv(octave_socket,int)\nSee the send() man pages.  This will only allow the" \
	  " user to receive uint8 arrays or strings")
{
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
  {
    int fd = args(0).int_value();
    s = socket_map[fd];
  }
  else
  {
    error("connect: expecting a octave_socket or integer");
    return octave_value(-1);
  }

  long len = args(1).int_value();
  unsigned char* buf = new unsigned char[ len ];
  retval = ::recv( s->get_sock_fd(), buf, len, flags );

  Matrix return_buf(1,retval);
  octave_value_list return_list;
  for ( int i = 0 ; i < retval ; i++ )
    return_buf(0,i) = buf[i];

  octave_value in_buf(return_buf);
  octave_value out_buf;
  OCTAVE_TYPE_CONV( in_buf, out_buf, uint8 );
  return_list(0) = out_buf;
	//return_list(0) = return_buf;
  return_list(1) = retval;

  return return_list;
}

// function to bind a socket
DEFUN_DLD(bind,args,nargout, \
	  "bind(octave_socket,int)\nSee the bind() man pages.  This will bind a socket to a" \
	  " specific port")
{
  int retval = 0;
  if ( args.length() < 2 )
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
    error("connect: expecting a octave_socket or integer");
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

// function to listen on a socket
DEFUN_DLD(listen,args,nargout, \
	  "listen(octave_socket,int)\nSee the listen() man pages")
{
  int retval = 0;
  if ( args.length() < 2 )
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
    error("connect: expecting a octave_socket or integer");
    return octave_value(-1);
  }

  int backlog = args(1).int_value();
//  octave_stdout << "BACKLOG: " << backlog << endl;

  retval = ::listen( s->get_sock_fd(), backlog );

  return octave_value(retval);
}

// function to accept on a listening socket
DEFUN_DLD(accept,args,nargout, \
	  "accept(octave_socket)\nSee the accept() man pages")
{
  int retval = 0;
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
    error("accept: expecting a octave_socket or integer");
    return octave_value(-1);
  }

  int fd = ::accept( s->get_sock_fd(), (struct sockaddr *)&clientInfo, &clientLen );
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


// function to load socket constants
DEFUN_DLD(load_socket_constants,args,nargout, \
	  "Loads various socket constants like AF_INET, SOCK_STREAM, etc.")
{
  octave_socket temp();
  return octave_value();
}

