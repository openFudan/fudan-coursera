//欢迎界面  
  
  
package yan.guoqi;  
  
import javax.servlet.http.*;  
  
import java.io.*;  
  
  
public class Wel extends HttpServlet{  
      
    public void doGet(HttpServletRequest req, HttpServletResponse res){  
    //业务逻辑  
    try{  
        res.setContentType("text/html;charset=gbk");  
        PrintWriter pw = res.getWriter();             
        pw.println("Welcome,恭喜您，已成功登陆！");  
      
  
  
    }  
    catch(Exception ex){  
        ex.printStackTrace();  
    }  
      
          
    }  
      
    public void doPost(HttpServletRequest req, HttpServletResponse res){  
          
        this.doGet(req, res);  
    }  
}  
