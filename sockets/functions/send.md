---
layout: "default"
permalink: "/functions/4_send/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - send"
category: "Sockets functions"
func_name: "send"
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
<dt class="deftypefn" id="index-send"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">send</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>)</code><a class="copiable-link" href="#index-send"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-send-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">retval</var> =</code> <strong class="def-name">send</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">data</var>, <var class="var">flags</var>)</code><a class="copiable-link" href="#index-send-1"></a></span></dt>
<dd><p>Send data on specified socket.
</p>
<p>Sends data on socket <var class="var">s</var>.  <var class="var">data</var> should be an uint8 array or
a string.
</p>
<p>See the <code class="command">send</code> man pages for further details.
</p>
</dd></dl>