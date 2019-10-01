package controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import daoo.LoginDAO;

/**
 * Servlet implementation class LoginController
 */
@WebServlet("/LoginController")
public class LoginController extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LoginController() {
        super();
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
		int id;
		try {
			if(request.getParameter("Login").equals("admin") && request.getParameter("Senha").equals("5555"))
				request.getRequestDispatcher("MenuAdmin.jsp").forward(request, response);
			else
				if((id = LoginDAO.verificaLogin(request.getParameter("Login"), request.getParameter("Senha"))) > 0) {
				
				request.setAttribute("clienteId", id);
				
				request.getRequestDispatcher("Menu.jsp").forward(request, response);
			}
			else {
				request.getRequestDispatcher("index.jsp").forward(request, response);
			}
					
		} catch (Exception e) {e.printStackTrace();}
	}
}
