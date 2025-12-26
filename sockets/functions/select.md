---
layout: "default"
permalink: "/functions/6_select/"
pkg_name: "sockets"
pkg_version: "1.5.0"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - select"
category: "Socket constants"
func_name: "select"
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
<dt class="deftypefn def-line" id="index-select"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">status</var>, <var class="var">rfdset</var>, <var class="var">wfdset</var>, <var class="var">efdset</var>] =</code> <strong class="def-name">select</strong> <code class="def-code-arguments">(<var class="var">nfds</var>, <var class="var">rfdset</var>, <var class="var">wfdset</var>, <var class="var">efdset</var>, <var class="var">timeout</var>)</code><a class="copiable-link" href="#index-select"></a></span></dt>
<dd><p>Wait for socket activity on selected sockets.
</p>
<p>The fdsets are vectors of fds to check, for example [1 2 3]. Empty vectors equate to null.
</p>
<p>nfds tests file descriptions in the range of 0 - nfds-1.
</p>
<p>Timeout is can be either an real value for number of seconds, a struct with a tm_sec and tm_usec fields, or empty set for null.
</p>
<p><var class="var">status</var> returns as  0 if timeout, or number of waiting sockets if ok.
</p>
<p>See the <code class="command">select</code> man pages for further details.
</p>
</dd></dl>