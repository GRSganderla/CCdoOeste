package servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import unioeste.geral.Assistant.*;
import unioeste.geral.controleestoque.manager.UCControleEstoqueServicos;

/**
 * Servlet implementation class chat
 */
@WebServlet("/chat")
public class chat extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public chat() {
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
		
		String input = request.getParameter("msg");
		System.out.println(input);
		
		String []ibm = IBM.IBMAssistant(input);
	
		UCControleEstoqueServicos uCCE = new UCControleEstoqueServicos();
		
		if(ibm[1].equals("consultar_nota_fiscal")) {
			
			String res[][];
			res = uCCE.ConsultarNotaVenda(Integer.parseInt(ibm[0]));
			
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
		else if(ibm[1].equals("consultar_produto")) {
			String prod[] = uCCE.ConsultarProduto(Integer.parseInt(ibm[0]));
			
			String codBarras = prod[0];
			String nome = prod[1];
			String fornecedor = prod[2];
			String valorCusto = prod[3];
			String valorVenda = prod[4];
			String qtd = prod[5];
			
			request.setAttribute("codProd", ibm[0]);
			request.setAttribute("codBarras", codBarras);
			request.setAttribute("nomeProd", nome);
			request.setAttribute("fornecedor", fornecedor);
			request.setAttribute("prAtual", valorCusto);
			request.setAttribute("prVenda", valorVenda);
			request.setAttribute("qtdAtual", qtd);

			request.getRequestDispatcher("/produto.jsp").forward(request, response);
		}
		else {
			response.sendRedirect("index.jsp");
		}
	}
}
