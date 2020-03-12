package servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import unioeste.geral.controleestoque.manager.UCControleEstoqueServicos;

/**
 * Servlet implementation class notaVenda
 */
@WebServlet("/notaVenda")
public class notaVenda extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public notaVenda() {
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

		HttpSession session = request.getSession();
		
		request.setCharacterEncoding("UTF-8");
		UCControleEstoqueServicos uCE = new UCControleEstoqueServicos();
		
		String nro = request.getParameter("numNota");
		String data = request.getParameter("data");
		String cliente = request.getParameter("cliente");
		System.out.println(cliente);
		
		if(nro != null && data != null && cliente != null) {
			
			String codigos [] = request.getParameterValues("codigo");
			String nomeProdutos [] = request.getParameterValues("produto");
			String quantidades [] = request.getParameterValues("quant");
			String precos [] = request.getParameterValues("preco");
			String totais [] = request.getParameterValues("total");
			
			String totNota = request.getParameter("totNota");
			
			String descTot = request.getParameter("descTot");
			String valorLiq = request.getParameter("valorLiq");
			
			int res = uCE.RegistrarVenda(nro, cliente, data, codigos, nomeProdutos, quantidades, precos, totais, totNota, descTot, valorLiq);
			
			if(res == 1) {
				session.setAttribute("Alert", "Nota Registrada com sucesso.");
				response.sendRedirect("index.jsp");
			}
			else {
				session.setAttribute("Alert", "Ocorreu um erro no registro!");
				response.sendRedirect("index.jsp");
			}
		}
		
	}

}
