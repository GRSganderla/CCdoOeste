package servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import unioeste.geral.controleestoque.manager.UCControleEstoqueServicos;

/**
 * Servlet implementation class consultaNota
 */
@WebServlet("/consultaNota")
public class consultaNota extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public consultaNota() {
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
		request.setCharacterEncoding("UTF-8");
		UCControleEstoqueServicos ucCE = new UCControleEstoqueServicos();
	
		String tipo = request.getParameter("tipo");
		
		String[][] res = null;
		String numNota = request.getParameter("numNota");
		
		if(tipo.equals("Venda")) {
			res = ucCE.ConsultarNotaVenda(Integer.parseInt(numNota));
		
			String [][] tabela = new String[res.length-2][5];
			int i;
			for(i = 1; i < res.length-1; i++) {
				tabela[i-1][0] = res[i][0];
				tabela[i-1][1] = res[i][1];
				tabela[i-1][2] = res[i][2];
				tabela[i-1][3] = res[i][3];
				tabela[i-1][4] = res[i][4];
			}
			
			request.setAttribute("numNota", res[0][0]);
			request.setAttribute("data", res[0][1]);
			request.setAttribute("cliente", res[0][2]);
			request.setAttribute("totNota", res[i][0]);
			request.setAttribute("descTot", res[i][1]);
			request.setAttribute("valorLiq", res[i][2]);
			request.setAttribute("tabela", tabela);
			request.getRequestDispatcher("/consultaNota.jsp").forward(request, response);
		}
	}

}