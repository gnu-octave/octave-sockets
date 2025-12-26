---
layout: "default"
permalink: "/functions/8_recvfrom/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - recvfrom"
category: "Socket constants"
func_name: "recvfrom"
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
<dt class="deftypefn def-line" id="index-recvfrom"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>, <var class="var">src_info</var>] =</code> <strong class="def-name">recvfrom</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">len</var>)</code><a class="copiable-link" href="#index-recvfrom"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-recvfrom-1"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>, <var class="var">src_info</var>] =</code> <strong class="def-name">recvfrom</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">len</var>, <var class="var">flags</var>)</code><a class="copiable-link" href="#index-recvfrom-1"></a></span></dt>
<dd><p>Read data from specified socket.
</p>
<p>Requests reading <var class="var">len</var> bytes from the socket <var class="var">s</var>.
The optional integer <var class="var">flags</var> parameter can be used to modify the
behaviour of <code class="code">recvfrom</code>.
</p>
<p>The read data is returned in the uint8 array <var class="var">data</var>.  The number of
bytes read is returned in <var class="var">count</var> and a structure with fields addr and port contain the source of the
data.
</p>
<p>You can get non-blocking operation by using the flag <code class="code">MSG_DONTWAIT</code>
which makes the <code class="code">recvfrom()</code> call return immediately.  If there is no
data, -1 is returned in count.
</p>
<p>See the <code class="command">recvfrom</code> man pages for further details.
</p>
</dd></dl>