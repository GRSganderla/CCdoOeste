package unioeste.geral.endereco.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import unioeste.geral.endereco.servicos.Server;

/**
 * Servlet implementation class ObterEndExtServlet
 */
@WebServlet("/ObterEndExtServlet")
public class ObterEndExtServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ObterEndExtServlet() {
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
		
		String site = request.getParameter("EndExt");
		Object[] o = null;
		
		if(site != null) {
		
			try {
	
				o = Server.endEspService(site);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			request.setAttribute("Site", site);
			request.setAttribute("Endereco", o);
			request.getRequestDispatcher("ConsultouEndExt.jsp").forward(request, response);
		}
		else
			request.getRequestDispatcher("ConsultouEndExt.jsp").forward(request, response);
	}

}
