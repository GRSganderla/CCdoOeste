package Servlet;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import serviços.UCManterPacienteManager;
import unioeste.classesbo.Email;
import unioeste.classesbo.Pessoa;
import unioeste.classesbo.Sexo;
import unioeste.classesbo.Telefone;
import unioeste.classesbo.especificas.Paciente;

/**
 * Servlet implementation class CadastroPaciente
 */
@WebServlet("/CadastroPaciente")
public class CadastroPaciente extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public CadastroPaciente() {
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

		String[] param = null;
		param[0] = request.getParameter("Nome1");
		param[1] = request.getParameter("Nome2");
		param[3] = request.getParameter("Nome3");
		param[4] = request.getParameter("Complemento");
		param[5] = request.getParameter("Sexo");
		param[6] = request.getParameter("Data");
		param[7] = request.getParameter("Tipo");
		param[8] = request.getParameter("Email");
		param[9] = request.getParameter("Email2");
		param[10] = request.getParameter("CPF");
		param[11] = request.getParameter("Foto");
		param[12] = request.getParameter("Telefone");
		param[13] = request.getParameter("Telefone2");
		param[14] = request.getParameter("Casa");

		Pessoa pessoa = new Pessoa();
		pessoa.setPrimeiroNome(request.getParameter("Nome1"));
		pessoa.setNomeMeio(request.getParameter("Nome2"));
		pessoa.setUltimoNome(request.getParameter("Nome3"));
		pessoa.setComplemento(request.getParameter("Complemento"));
		pessoa.setDtNascimento(request.getParameter("Data"));
		pessoa.setTipoSanguineo(request.getParameter("Tipo"));
		pessoa.setCPF(request.getParameter("CPF"));
		// pessoa.setNroCasa(request.getParameter("Casa"));
		pessoa.setTipoSexo(request.getParameter("Sexo"));

		Paciente paciente = new Paciente();
		Telefone tele1 = new Telefone();
		tele1.setTelefone(request.getParameter("Telefone"));
		tele1.setDDD("45");
		tele1.setDDI("55");

		Telefone tele2 = new Telefone();
		tele2.setTelefone(request.getParameter("Telefone2"));
		tele2.setDDD("45");
		tele2.setDDI("55");

		ArrayList<Telefone> telefones = new ArrayList<Telefone>();
		telefones.add(tele1);
		telefones.add(tele2);
		
		Sexo sex = new Sexo();
		pessoa.setSexo(sex);

		ArrayList<Email> emails = new ArrayList<Email>();

		Email email1 = new Email();
		email1.setEmail(request.getParameter("Email"));
		Email email2 = new Email();
		email2.setEmail(request.getParameter("Email2"));

		emails.add(email1);
		emails.add(email2);

		paciente.setPessoa(pessoa);
		paciente.getPessoa().setListaEmail(emails);
		paciente.getPessoa().setListaTelefone(telefones);

		UCManterPacienteManager paciente1 = new UCManterPacienteManager();
		try {
			paciente1.cadastrarPaciente(paciente);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		request.getRequestDispatcher("Menu.jsp").forward(request, response);
	}

}
