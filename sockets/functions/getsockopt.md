---
layout: "default"
permalink: "/functions/10_getsockopt/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - getsockopt"
category: "Sockets functions"
func_name: "getsockopt"
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
<dt class="deftypefn" id="index-getsockopt"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">data</var>, <var class="var">status</var>] =</code> <strong class="def-name">getsockopt</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">level</var>, <var class="var">optname</var>)</code><a class="copiable-link" href="#index-getsockopt"></a></span></dt>
<dd><p>Get a socket option value from a socket.
</p>
<p>Returns the value of <var class="var">level</var> <var class="var">optname</var> from the socket <var class="var">s</var>.
</p>
<p>Data type depends on the option used. <var class="var">status</var> returns as  0 if no error.
</p>
<p>See the <code class="command">getsockopt</code> man pages for further details.
</p>
</dd></dl>