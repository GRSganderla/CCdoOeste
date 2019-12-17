package servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class notaCompra
 */
@WebServlet("/notaCompra")
public class notaCompra extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public notaCompra() {
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
		
		String nome = request.getParameter("numNota");
		String data = request.getParameter("data");
		String fornecedor = request.getParameter("fornecedor");
		
		System.out.println("nome= " + nome + " data= " + data + " fornecedor= " + fornecedor);
		
		String codigos [] = request.getParameterValues("codigo");
		String produtos [] = request.getParameterValues("produto");
		String quantidades [] = request.getParameterValues("quant");
		String precos [] = request.getParameterValues("preco");
		String totais [] = request.getParameterValues("total");
		
		for(int i=0; i < codigos.length; i++) {
			System.out.println("cod prod qtd preco e tot = " + codigos[i] + " " + produtos[i] +  " " + quantidades[i] + " " + precos[i] + " " + totais[i] + " "); 
		}

		String totNota = request.getParameter("totNota");
		
		//nao sei como ia ser isso...
		String descTot = request.getParameter("destTot");

		String valorLiq = request.getParameter("valorLiq");
		
		System.out.println(" valot total e liquido, desconto= " + totNota + " " + valorLiq + " " + descTot);
		
//		int res = 0;
//		try {
//			res = 
//			
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
		
//		HttpSession session = request.getSession();
		
//		if(res == 1) {
//			session.setAttribute("Alert", "Nota Registrada com sucesso.");
//		request.getRequestDispatcher("/notaCompra.jsp").forward(request, response);
//		}
//		else {
//			session.setAttribute("Alert", "Ocorreu um erro no registro!");
//		request.getRequestDispatcher("/notaCompra.jsp").forward(request, response);
//		}
		
				
		//so assim para redirecionar essa pagina...
//		request.getRequestDispatcher("/notaCompra.jsp").forward(request, response);

	}

}
