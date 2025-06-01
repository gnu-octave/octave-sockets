---
layout: "default"
permalink: "/functions/6_listen/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - listen"
category: "Sockets functions"
func_name: "listen"
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
<dt class="deftypefn" id="index-listen"><span class="category-def">Loadable Function: </span><span><strong class="def-name">listen</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">backlog</var>)</code><a class="copiable-link" href="#index-listen"></a></span></dt>
<dd><p>Listen on socket for connections.
</p>
<p>Listens on socket <var class="var">s</var> for connections.  <var class="var">backlog</var> specifies
how large the queue of incoming connections is allowed to
grow.
</p>
<p>On success, zero is returned.
</p>
<p>See the <code class="command">listen</code> man pages for further details.
</p>
</dd></dl>