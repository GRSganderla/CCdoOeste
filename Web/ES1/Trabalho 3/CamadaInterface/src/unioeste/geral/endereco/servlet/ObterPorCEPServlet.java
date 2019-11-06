package unioeste.geral.endereco.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import unioeste.geral.endereco.servicos.Server;

/**
 * Servlet implementation class ObterPorCEPServlet
 */
@WebServlet("/ObterPorCEPServlet")
public class ObterPorCEPServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ObterPorCEPServlet() {
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
		
		String cep = request.getParameter("PorCEP");
		
		Object[] out = null;
		
		if(cep != null) {
			
			try {
	
				out = Server.endCepService(cep);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			request.setAttribute("Endereco", out);
			request.setAttribute("CEP", cep);
			
			request.getRequestDispatcher("ConsultouCEP.jsp").forward(request, response);
		}
		else
			request.getRequestDispatcher("ConsultouCEP.jsp").forward(request, response);
	}

}
