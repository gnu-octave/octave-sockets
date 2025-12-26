---
layout: "default"
permalink: "/functions/11_getaddrinfo/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - getaddrinfo"
category: "Socket constants"
func_name: "getaddrinfo"
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
<dt class="deftypefn def-line" id="index-getaddrinfo"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">addrinforesults</var> =</code> <strong class="def-name">getaddrinfo</strong> <code class="def-code-arguments">(<var class="var">hostname</var>, <var class="var">service</var>, <var class="var">hints</var>)</code><a class="copiable-link" href="#index-getaddrinfo"></a></span></dt>
<dd><p>Get addressinfo lookup for a hostname/service.
</p>
<p>Returns an array of addressinfo structs with the following fields:
</p>
<dl class="table">
<dt><code class="code">family</code></dt>
<dd><p>Integer family value
</p></dd>
<dt><code class="code">socktype</code></dt>
<dd><p>Integer socktype value
</p></dd>
<dt><code class="code">protocol</code></dt>
<dd><p>Integer protocol value
</p></dd>
<dt><code class="code">addr</code></dt>
<dd><p>a string with the host name to send to
</p>
</dd>
<dt><code class="code">port</code></dt>
<dd><p>the port number to send to (an integer)
</p></dd>
</dl>

<p>hints is optional with one or more fields:
</p>
<dl class="table">
<dt><code class="code">family</code></dt>
<dd><p>Integer family value
</p></dd>
<dt><code class="code">socktype</code></dt>
<dd><p>Integer socktype value
</p></dd>
<dt><code class="code">protocol</code></dt>
<dd><p>Integer protocol value
</p></dd>
<dt><code class="code">flags</code></dt>
<dd><p>a integer ai flags
</p></dd>
</dl>

<p>See the <code class="command">getaddrinfo</code> man pages for details.
</p>
</dd></dl>