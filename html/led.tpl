<html><head><title>Test</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="main">
<h1>The LED</h1>
<p>
There is a LED connected to GPIO2, it's now <b>%ledstate%</b>. You
can change that using the buttons below.  NOTE: If you leave it on, it will
increase the battery drain.
</p>
<form method="post" action="led.cgi">
<input type="submit" name="led" value="On">
<input type="submit" name="led" value="Off">
</form>
</div>
</body></html>
