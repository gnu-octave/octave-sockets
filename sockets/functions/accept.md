---
layout: "default"
permalink: "/functions/6_accept/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - accept"
category: "Socket constants"
func_name: "accept"
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
<dt class="deftypefn def-line" id="index-accept"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">client</var>, <var class="var">info</var>] =</code> <strong class="def-name">accept</strong> <code class="def-code-arguments">(<var class="var">s</var>)</code><a class="copiable-link" href="#index-accept"></a></span></dt>
<dd><p>Accept incoming connection on specified socket.
</p>
<p>Accepts an incoming connection on the socket <var class="var">s</var>.
The newly created socket is returned in <var class="var">client</var>, and
associated information in a struct info.
</p>
<p>See the <code class="command">accept</code> man pages for further details.
</p>
</dd></dl>