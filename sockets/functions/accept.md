---
layout: "default"
permalink: "/functions/6_accept/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - accept"
category: "Sockets functions"
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
<dt class="deftypefn" id="index-accept"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">client</var>, <var class="var">info</var>] =</code> <strong class="def-name">accept</strong> <code class="def-code-arguments">(<var class="var">s</var>)</code><a class="copiable-link" href="#index-accept"></a></span></dt>
<dd><p>Accept incoming connection on specified socket.
</p>
<p>Accepts an incoming connection on the socket <var class="var">s</var>.
The newly created socket is returned in <var class="var">client</var>, and
associated information in a struct info.
</p>
<p>See the <code class="command">accept</code> man pages for further details.
</p>
</dd></dl>