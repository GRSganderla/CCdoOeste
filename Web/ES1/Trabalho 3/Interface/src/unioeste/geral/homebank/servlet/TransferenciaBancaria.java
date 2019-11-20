package unioeste.geral.homebank.servlet;


import java.io.IOException;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import unioeste.geral.homebank.servicos.HomeBank;
import unioeste.geral.homebank.servicos.ServicoHomeBank;

/**
 * Servlet implementation class TransferenciaBancaria
 */
@WebServlet("/TransferenciaBancaria")
public class TransferenciaBancaria extends HttpServlet {
	private static final long serialVersionUID = 1L;

    /**
     * Default constructor. 
     */
    public TransferenciaBancaria() {
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
		
		URL url = new URL("http://localhost:9877/homebankWS?wsdl");
		QName qname = new QName("http://servicos.homebank.geral.unioeste/", "HomeBankImplService");
		
		Service ws = Service.create(url, qname);
		
		HomeBank homeWSDL = ws.getPort(HomeBank.class);

		request.setCharacterEncoding("UTF-8");
		//parte cliente
		String cliente = request.getParameter("cliente");
		String cpfCnpj = request.getParameter("cpfCnpj");
		int conta = Integer.parseInt(request.getParameter("conta"));
		Date data = null;
		String dadoData = request.getParameter("data");
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		try {
			data = sdf.parse(dadoData);
				
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println(cliente + " " + cpfCnpj + " " + conta + " " + data);

		
		//parte favorecido
		int nroBanco = Integer.parseInt(request.getParameter("codBanco"));
		int nroAgencia = Integer.parseInt(request.getParameter("nroAgencia"));
		int nroConta = Integer.parseInt(request.getParameter("nroConta"));
		String nomeFav = request.getParameter("favorecido");
		String cpfCnpj_fav = request.getParameter("cpfCnpj_fav");
		double valor = Double.parseDouble(request.getParameter("valorTransf"));
		
		System.out.println(nroBanco + " " + nroAgencia + " " +
		nroConta + " " + nomeFav + " " + cpfCnpj_fav + " " + valor);
		
		int res = 0;
		try {
			res = homeWSDL.registrarTransferenciaBancaria(cliente, cpfCnpj, nomeFav, cpfCnpj_fav, data, conta, nroConta, nroBanco, nroAgencia, valor);
			//res = ServicoHomeBank.registrarTransferenciaBancaria(cliente, cpfCnpj, nomeFav, cpfCnpj_fav, data, conta, nroConta, nroBanco, nroAgencia, valor);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		HttpSession session = request.getSession();
		
		if(res == 1) {
			session.setAttribute("Alert", "Transfência Realizada");
			response.sendRedirect("index.jsp");
		}
		else {
			session.setAttribute("Alert", "Ocorreu um erro ao transferir!");
			response.sendRedirect("index.jsp");
		}
	}

}
