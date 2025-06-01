---
layout: "default"
permalink: "/functions/7_connect/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - connect"
category: "Sockets functions"
func_name: "connect"
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
<dt class="deftypefn" id="index-connect"><span class="category-def">Loadable Function: </span><span><strong class="def-name">connect</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">serverinfo</var>)</code><a class="copiable-link" href="#index-connect"></a></span></dt>
<dd><p>Connect socket.
</p>
<p>Connects the socket <var class="var">s</var> following the information
in the struct <var class="var">serverinfo</var> which must contain the
following fields:
</p>
<dl class="table">
<dt><code class="code">addr</code></dt>
<dd><p>a string with the host name to connect to
</p>
</dd>
<dt><code class="code">port</code></dt>
<dd><p>the port number to connect to (an integer)
</p></dd>
</dl>

<p>On successful connect, the returned status is zero.
</p>
<p>See the <code class="command">connect</code> man pages for further details.
</p></dd></dl>