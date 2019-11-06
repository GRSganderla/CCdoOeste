package unioeste.geral.endereco.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import unioeste.geral.endereco.servicos.Server;

/**
 * Servlet implementation class ObterPorIDServlet
 */
@WebServlet("/ObterPorIDServlet")
public class ObterPorIDServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ObterPorIDServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		
		int id = Integer.parseInt(request.getParameter("PorID"));
		
		if(id > 0) {
			
			Object[] out = null;
			
			try {
	
				out = Server.endIdService(id);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			request.setAttribute("Endereco", out);
			request.setAttribute("idEndereco", id);
			request.getRequestDispatcher("ConsultouID.jsp").forward(request, response);
		}
		else
			request.getRequestDispatcher("ConsultouID.jsp").forward(request, response);
	}

}
