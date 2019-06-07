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
 * Servlet implementation class AlterarController
 */
@WebServlet("/AlterarController")
public class AlterarController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public AlterarController() {
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
		try {
			Endereço novo = new Endereço();
			novo.setRua(request.getParameter("R"));
			novo.setBairro(request.getParameter("Bai"));
			novo.setCidade(request.getParameter("Cid"));
			novo.setEstado(request.getParameter("E"));
			novo.setPaís(request.getParameter("P"));
			int idEnd;

			idEnd = EndereçoDAO.insereEndereço(novo);
			
			Cliente c = new Cliente();
			int id = Integer.parseInt(request.getParameter("ID"));
			c.setIdCliente(id);
			c.setNome(request.getParameter("Nome"));
			c.setCPF(request.getParameter("CPF"));
			c.setCNPJ(request.getParameter("CNPJ"));
			c.setEmail(request.getParameter("Email"));
			c.setSenha(request.getParameter("S"));
			c.setCEP(request.getParameter("CEP"));
			if(request.getParameter("N").matches("-?\\d+")) c.setNum(Integer.parseInt(request.getParameter("N")));
			c.setComplemento(request.getParameter("Co"));
			c.setEndereco(idEnd);
			
			if((ClienteDAO.validaSenha(c.getSenha())) && (ClienteDAO.validaCEP(c.getCEP())) && (c.getNum() > 0))
			{	
				ClienteDAO.alteraCliente(c);
			}
			request.setAttribute("clienteId", id);
			request.getRequestDispatcher("Menu.jsp").forward(request, response);
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
