<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<html>
<head>
<title>get and set property</title>
</head>
<body>

<jsp:useBean id="students" 
                    class="com.runoob.StudentsBean"> 
   <jsp:setProperty name="students" property="firstName"
                    value="xiao qiang"/>
   <jsp:setProperty name="students" property="lastName" 
                    value="Wang"/>
   <jsp:setProperty name="students" property="age"
                    value="10"/>
</jsp:useBean>

<p>the firstName of student: 
   <jsp:getProperty name="students" property="firstName"/>
</p>
<p>the lastName of student: 
   <jsp:getProperty name="students" property="lastName"/>
</p>
<p>the age of student: 
   <jsp:getProperty name="students" property="age"/>
</p>

</body>
</html>