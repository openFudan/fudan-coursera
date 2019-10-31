<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%! int fontSize; %> 
<html> 
<head><title>WHILE循环示例</title></head> 
<body>
<h2>While循环示例：</h2>
<%while ( fontSize <= 5){ %>
   <font color="green" size="<%= fontSize %>">
    JSP Tutorial
   </font><br />
<%fontSize++;%>
<%}%>
</body> 
</html>