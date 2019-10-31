<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%! int fontSize; %> 
<html> 
<head><title>FOR Ñ­»·Ê¾Àý</title></head> 
<body>
<%for ( fontSize = 1; fontSize <= 3; fontSize++){ %>
   <font color="green" size="<%= fontSize %>">
    JSP Tutorial
   </font><br />
<%}%>
</body> 
</html> 