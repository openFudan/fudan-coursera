//用户验证servlet  
  
  
package yan.guoqi;  
  
import javax.servlet.http.*;  
  
import java.io.*;  
  
  
  
public class LoginCL extends HttpServlet{  
      
    public void doGet(HttpServletRequest req, HttpServletResponse res){  
    //业务逻辑  
    try{  
    //接受用户名和密码  
    String u = req.getParameter("username");  
    String p = req.getParameter("passwd");  
    //验证  
    if(u.equals("yan") && p.equals("yan")){  
        //合法  
        //跳转到welcome  
              
        res.sendRedirect("wel");  
          
    }  
    else{  
        //不合法  
        //跳转  
        res.sendRedirect("login");//你要跳转的servlet的url  
    }  
          
      
    }  
    catch(Exception ex){  
        ex.printStackTrace();  
    }  
      
          
    }  
      
    public void doPost(HttpServletRequest req, HttpServletResponse res){  
          
        this.doGet(req, res);  
    }  
}  
