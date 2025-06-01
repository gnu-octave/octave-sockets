---
layout: "default"
permalink: "/functions/6_socket/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - socket"
category: "Sockets functions"
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
- id: "16_Socketconstants"
  name: "&nbsp;&nbsp;Socket constants"
  url: "/functions/#16_Socketconstants"
- id: "news"
  name: "News"
  url: "/news"
- id: "manual"
  name: "Manual"
  url: "/manual"
---
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-socket"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">()</code><a class="copiable-link" href="#index-socket"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-socket-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>)</code><a class="copiable-link" href="#index-socket-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-socket-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>, <var class="var">type</var>)</code><a class="copiable-link" href="#index-socket-2"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-socket-3"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">sock</var> =</code> <strong class="def-name">socket</strong> <code class="def-code-arguments">(<var class="var">domain</var>, <var class="var">type</var>, <var class="var">protocol</var>)</code><a class="copiable-link" href="#index-socket-3"></a></span></dt>
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