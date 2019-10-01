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
 * Servlet implementation class CadastroClienteController
 */
@WebServlet("/CadastroClienteController")
public class CadastroClienteController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public CadastroClienteController() {
		super();
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
		
		if(request.getParameter("Senha").equals(request.getParameter("Senha1"))) {
			
			try {
				
				Cliente c = new Cliente();
			
				c.setNome(request.getParameter("Nome"));
				c.setEmail(request.getParameter("Email"));
				c.setCPF(request.getParameter("CPF"));
				c.setCNPJ(request.getParameter("CNPJ"));
				c.setSenha(request.getParameter("Senha"));
				c.setComplemento(request.getParameter("Complemento"));
				c.setNum(Integer.parseInt(request.getParameter("Numero")));
				c.setEmail(request.getParameter("Email"));
				c.setCEP(request.getParameter("CEP"));
				
				Endereço e = new Endereço();
				e.setRua(request.getParameter("Rua"));
				e.setBairro(request.getParameter("Bairro"));
				e.setCidade(request.getParameter("Cidade"));
				e.setEstado(request.getParameter("Estado"));
				e.setPaís(request.getParameter("País"));

				int ed = EndereçoDAO.insereEndereço(e);
				
				ClienteDAO.insereCliente(c, ed);
				
				request.setAttribute("clienteId", c.getIdCliente());
				
				request.getRequestDispatcher("Menu.jsp").forward(request, response);
				
			}catch(Exception e) {System.out.println(e);}
		}
		else {
			request.getRequestDispatcher("Cadastro.jsp").forward(request, response);
		}
	}
}
