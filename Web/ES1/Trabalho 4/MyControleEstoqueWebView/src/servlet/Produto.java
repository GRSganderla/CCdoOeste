package servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import unioeste.geral.controleestoque.manager.UCControleEstoqueServicos;

/**
 * Servlet implementation class Produto
 */
@WebServlet("/Produto")
public class Produto extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Produto() {
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
		UCControleEstoqueServicos uc = new UCControleEstoqueServicos();
		
		String codProd = request.getParameter("codProd");
		
		String res[] = uc.ConsultarProduto(Integer.parseInt(codProd));
		
		String codBarras = res[0];
		String nome = res[1];
		String fornecedor = res[2];
		String valorCusto = res[3];
		String valorVenda = res[4];
		String qtd = res[5];
		
		request.setAttribute("codProd", codProd);
		request.setAttribute("codBarras", codBarras);
		request.setAttribute("nomeProd", nome);
		request.setAttribute("fornecedor", fornecedor);
		request.setAttribute("prAtual", valorCusto);
		request.setAttribute("prVenda", valorVenda);
		request.setAttribute("qtdAtual", qtd);

		request.getRequestDispatcher("/produto.jsp").forward(request, response);
	}

}
