---
layout: "default"
permalink: "/functions/6_select/"
pkg_name: "sockets"
pkg_version: "1.4.1"
pkg_description: "Socket functions for networking from within octave."
title: "Sockets Toolkit - select"
category: "Sockets functions"
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
<dt class="deftypefn" id="index-select"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">status</var>, <var class="var">rfdset</var>, <var class="var">wfdset</var>, <var class="var">efdset</var>] =</code> <strong class="def-name">select</strong> <code class="def-code-arguments">(<var class="var">nfds</var>, <var class="var">rfdset</var>, <var class="var">wfdset</var>, <var class="var">efdset</var>, <var class="var">timeout</var>)</code><a class="copiable-link" href="#index-select"></a></span></dt>
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