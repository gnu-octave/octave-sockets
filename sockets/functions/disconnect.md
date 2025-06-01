---
layout: "default"
permalink: "/functions/10_disconnect/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - disconnect"
category: "Sockets functions"
func_name: "disconnect"
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
<dt class="deftypefn" id="index-disconnect"><span class="category-def">Loadable Function: </span><span><strong class="def-name">disconnect</strong> <code class="def-code-arguments">(<var class="var">s</var>)</code><a class="copiable-link" href="#index-disconnect"></a></span></dt>
<dd><p>Disconnect socket.
</p>
<p>Disconnects the socket <var class="var">s</var>.  If successful, <code class="code">disconnect</code> returns 0,
otherwise, it returns -1.
</p>
<p>Since we can&rsquo;t call fclose on the file descriptor directly, use this
function to disconnect the socket.
</p>
</dd></dl>