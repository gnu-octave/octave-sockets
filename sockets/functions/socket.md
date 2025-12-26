---
layout: "default"
permalink: "/functions/6_socket/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - socket"
category: "Socket constants"
func_name: "socket"
navigation:
- id: "overview"
  name: "Overview"
  url: "/index"
- id: "Functions"
  name: "Function Reference"
  url: "/functions"
- id: "17_Socketsfunctions"
  name: "&nbsp;&nbsp;Sockets functions"
  url: "/functions/#17_Socketsfunctions"
  subitems:
- id: "16_Socketconstants"
  name: "&nbsp;&nbsp;Socket constants"
  url: "/functions/#16_Socketconstants"
  subitems:
  - id: "40_Socketconstants-Domainfamilyconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Domain family constants"
    url: "/functions/#40_Socketconstants-Domainfamilyconstants"
  - id: "38_Socketconstants-SocketTypeconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Socket Type constants"
    url: "/functions/#38_Socketconstants-SocketTypeconstants"
  - id: "41_Socketconstants-SendRecvFlagconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Send/Recv Flag constants"
    url: "/functions/#41_Socketconstants-SendRecvFlagconstants"
  - id: "39_Socketconstants-Shutdownhowconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Shutdown how constants"
    url: "/functions/#39_Socketconstants-Shutdownhowconstants"
  - id: "41_Socketconstants-Setgetsockoptconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Set/getsockopt constants"
    url: "/functions/#41_Socketconstants-Setgetsockoptconstants"
  - id: "42_Socketconstants-Socketprotocolconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Socket protocol constants"
    url: "/functions/#42_Socketconstants-Socketprotocolconstants"
  - id: "50_Socketconstants-Socketgetaddrinfoflagconstants"
    name: "&nbsp;&nbsp;&nbsp;&nbsp;Socket getaddrinfo flag constants"
    url: "/functions/#50_Socketconstants-Socketgetaddrinfoflagconstants"
- id: "news"
  name: "News"
  url: "/news"
- id: "manual"
  name: "Manual"
  url: "/manual"
---
<dl class="first-deftypefn def-block">
<dt class="deftypefn def-line" id="index-socket"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">()</code><a class="copiable-link" href="#index-socket"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-socket-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>)</code><a class="copiable-link" href="#index-socket-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-socket-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>, <var class="var">type</var>)</code><a class="copiable-link" href="#index-socket-2"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-socket-3"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>, <var class="var">type</var>, <var class="var">protocol</var>)</code><a class="copiable-link" href="#index-socket-3"></a></span></dt>
<dd><p>Creates a socket.
</p>
<p><var class="var">domain</var> is an integer, where the value AF_INET
can be used to create an IPv4 socket.
</p>
<p><var class="var">type</var> is an integer describing the socket.  When using IP, specifying
SOCK_STREAM gives a TCP socket.
</p>
<p><var class="var">protocol</var> is currently not used and should be 0 if specified.
</p>
<p>If no input arguments are given, default values AF_INET and
SOCK_STREAM are used.
</p>
<p>See the local <code class="command">socket</code> reference for more details.
</p></dd></dl>