---
layout: "default"
permalink: "/functions/4_send/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - send"
category: "Socket constants"
func_name: "send"
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
<dt class="deftypefn def-line" id="index-send"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">send</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>)</code><a class="copiable-link" href="#index-send"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-send-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">send</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>, <var class="var">flags</var>)</code><a class="copiable-link" href="#index-send-1"></a></span></dt>
<dd><p>Send data on specified socket.
</p>
<p>Sends data on socket <var class="var">s</var>.  <var class="var">data</var> should be an uint8 array or
a string.
</p>
<p>See the <code class="command">send</code> man pages for further details.
</p>
</dd></dl>