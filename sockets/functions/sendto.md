---
layout: "default"
permalink: "/functions/6_sendto/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - sendto"
category: "Sockets functions"
func_name: "sendto"
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
<dt class="deftypefn" id="index-sendto"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">sendto</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>, <var class="var">dest_info</var>)</code><a class="copiable-link" href="#index-sendto"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-sendto-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">sendto</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>, <var class="var">flags</var>, <var class="var">dest_info</var>)</code><a class="copiable-link" href="#index-sendto-1"></a></span></dt>
<dd><p>Send data on specified socket.
</p>
<p>Sends data on socket <var class="var">s</var> to destination.  <var class="var">data</var> should be an uint8 array or
a string.
</p>
<p>The dest_info struct <var class="var">dest_info</var> must contain the
following fields:
</p>
<dl class="table">
<dt><code class="code">addr</code></dt>
<dd><p>a string with the host name to send to
</p>
</dd>
<dt><code class="code">port</code></dt>
<dd><p>the port number to send to (an integer)
</p></dd>
</dl>

<p>See the <code class="command">sendto</code> man pages for further details.
</p>
</dd></dl>