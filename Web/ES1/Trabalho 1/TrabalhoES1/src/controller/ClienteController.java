package controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import daoo.ClienteDAO;
import daoo.EndereçoDAO;
import modeloss.Cliente;
import modeloss.Endereço;

/**
 * Servlet implementation class ClienteController
 */
@WebServlet("/ClienteController")
public class ClienteController extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ClienteController() {
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
		try {
			consultar(request, response);
		} catch (Exception e) {e.printStackTrace();}
		
		request.getRequestDispatcher("ConsultaAltera.jsp").forward(request, response);
	}
	protected void consultar(HttpServletRequest request, HttpServletResponse response) throws Exception {
		
		Cliente cadastrado = ClienteDAO.getCliente(Integer.parseInt(request.getParameter("ID")));
		
		request.setAttribute("Nome", cadastrado.getNome());
		request.setAttribute("CNPJ", cadastrado.getCNPJ());
		request.setAttribute("CPF", cadastrado.getCPF());
		request.setAttribute("Email", cadastrado.getEmail());
		request.setAttribute("Senha", cadastrado.getSenha());
		request.setAttribute("Numero", cadastrado.getNum());
		request.setAttribute("Complemento", cadastrado.getComplemento());
		request.setAttribute("CEP", cadastrado.getCEP());
		
		Endereço novo = EndereçoDAO.getEndereco(cadastrado.getEndereco());
		request.setAttribute("Rua", novo.getRua());
		request.setAttribute("Bairro", novo.getBairro());
		request.setAttribute("Cidade", novo.getCidade());
		request.setAttribute("Estado", novo.getEstado());
		request.setAttribute("País", novo.getPaís());
		request.setAttribute("clienteId", Integer.parseInt(request.getParameter("ID")));
	}
}
