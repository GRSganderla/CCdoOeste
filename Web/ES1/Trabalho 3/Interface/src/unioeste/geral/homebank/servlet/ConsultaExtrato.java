package unioeste.geral.homebank.servlet;

import java.io.IOException;
import java.net.URL;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import unioeste.geral.homebank.servicos.HomeBank;
import unioeste.geral.homebank.servicos.ServicoHomeBank;;
/**
 * Servlet implementation class ConsultaExtrato
 */
@WebServlet("/ConsultaExtrato")
public class ConsultaExtrato extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * Default constructor.
	 */
	public ConsultaExtrato() {
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

		URL url = new URL("http://localhost:9877/homebankWS?wsdl");
		QName qname = new QName("http://servicos.homebank.geral.unioeste/", "HomeBankImplService");
		
		Service ws = Service.create(url, qname);
		
		HomeBank homeWSDL = ws.getPort(HomeBank.class);
		
		HttpSession session = request.getSession();
		
		request.setCharacterEncoding("UTF-8");
		String cliente = request.getParameter("cliente");
		String cpf_cnpj = request.getParameter("cpf_cnpj");
		
		System.out.println(cliente);
		System.out.println(cpf_cnpj);
			
		if(cliente != "" && cpf_cnpj != "") {
			
			try {
				
				String[][] aa = homeWSDL.consultarExtratoConta(cliente, cpf_cnpj);
				
				//String[][] aa = ServicoHomeBank.consultarExtratoConta(cliente, cpf_cnpj);
				double saldo = Double.parseDouble(aa[aa.length-1][0]);
				
				System.out.println(aa.length);
				
				String[][] tabela = new String[aa.length-1][4];
				
				int i = 0, j =0;
				
				for(String[] lin: aa) {
					if(i == aa.length-1) break;
					j = 0;
					for(String col : lin) {
						tabela[i][j++] = col;
					}
					i++;
				}
		
				request.setAttribute("cliente", cliente);
				request.setAttribute("cpf_cnpj", cpf_cnpj);
				request.setAttribute("tabela", tabela);
				request.setAttribute("saldo", saldo);
				
				session.setAttribute("Alert", "No");
				request.getRequestDispatcher("/ExtratoConsultado.jsp").forward(request, response);
				
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else {
			session.setAttribute("Alert", "Nome do Cliente ou CPF/CNPJ não inserido");
			response.sendRedirect("index.jsp");
		}
	}

}
