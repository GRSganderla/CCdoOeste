package controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import IBMServiceConnection.IBMConnected;
import daoo.EspecProdutoDAO;
import daoo.ProdutoDAO;
import modeloss.EspecProduto;
import modeloss.Produto;

/**
 * Servlet implementation class Produto
 */
@WebServlet("/ProdutoController")
public class ProdutoController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public ProdutoController() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		
		Produto n = new Produto();
		n.setNome(request.getParameter("Nome"));
		System.out.println(request.getParameter("DescriçãoFoto"));
		
		try {
			String foto = request.getParameter("Descricao") + "\n" + IBMConnected.execReconhecimentoImg(request.getParameter("DescriçãoFoto"));
			System.out.println(foto);
			n.setDescricao(foto);
			
		} catch (Exception e1) {
			
			e1.printStackTrace();
		}
		
		n.setPeso(Float.parseFloat(request.getParameter("Peso")));
		n.setCor(request.getParameter("Cor"));
		n.setTempoFab(Integer.parseInt(request.getParameter("Tempo")));

		EspecProduto es = new EspecProduto();
		es.setModelo(request.getParameter("modelo"));
		es.setTipoProd(request.getParameter("Tipo"));

		try {
			int t = EspecProdutoDAO.inserirTabelaT(es);
			int m = EspecProdutoDAO.inserirTabelaM(es);
			ProdutoDAO.insereProduto(n, t, m);

			es.setMaterial(request.getParameter("Material1"));
			es.setPreco(Float.parseFloat(request.getParameter("Preço")));
			es.setQuant(Integer.parseInt(request.getParameter("Quant1")));
			
			int e = EspecProdutoDAO.inserirTabelaE(es);
			int mp= EspecProdutoDAO.inserirTabelaMP(es, e);
			EspecProdutoDAO.inserirTabelaPM(n, es, mp);

			
		} catch (Exception e) {
			e.printStackTrace();
		}
		request.getRequestDispatcher("MenuAdmin.jsp").forward(request, response);
	}

}
