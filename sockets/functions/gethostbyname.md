---
layout: "default"
permalink: "/functions/13_gethostbyname/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - gethostbyname"
category: "Socket constants"
func_name: "gethostbyname"
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
<dt class="deftypefn def-line" id="index-gethostbyname"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">ipaddress</var> =</code> <strong class="def-name">gethostbyname</strong> <code class="def-code-arguments">(<var class="var">hostname</var>)</code><a class="copiable-link" href="#index-gethostbyname"></a></span></dt>
<dd><p>Return IP address for host name.
</p>
<p>For example:
</p>
<div class="example">
<div class="group"><pre class="example-preformatted">gethostbyname (&quot;localhost&quot;)
  &rArr; 127.0.0.1
</pre></div></div>

<p>See the <code class="command">gethostbyname</code> man pages for details.
</p>
</dd></dl>