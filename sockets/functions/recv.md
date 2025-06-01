---
layout: "default"
permalink: "/functions/4_recv/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - recv"
category: "Sockets functions"
func_name: "recv"
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
<dt class="deftypefn" id="index-recv"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">recv</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">len</var>)</code><a class="copiable-link" href="#index-recv"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-recv-1"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">recv</strong> <code class="def-code-arguments">(<var class="var">s</var>, <var class="var">len</var>, <var class="var">flags</var>)</code><a class="copiable-link" href="#index-recv-1"></a></span></dt>
<dd><p>Read data from specified socket.
</p>
<p>Requests reading <var class="var">len</var> bytes from the socket <var class="var">s</var>.
The optional integer <var class="var">flags</var> parameter can be used to modify the
behaviour of <code class="code">recv</code>.
</p>
<p>The read data is returned in the uint8 array <var class="var">data</var>.  The number of
bytes read is returned in <var class="var">count</var>.
</p>
<p>You can get non-blocking operation by using the flag <code class="code">MSG_DONTWAIT</code>
which makes the <code class="code">recv()</code> call return immediately.  If there is no
data, -1 is returned in count.
</p>
<p>See the <code class="command">recv</code> man pages for further details.
</p>
</dd></dl>