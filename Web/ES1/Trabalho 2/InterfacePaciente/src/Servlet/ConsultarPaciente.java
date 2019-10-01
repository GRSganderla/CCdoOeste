package Servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import serviços.UCManterPacienteManager;
import unioeste.classesbo.especificas.Paciente;

/**
 * Servlet implementation class ConsultarPaciente
 */
@WebServlet("/ConsultarPaciente")
public class ConsultarPaciente extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ConsultarPaciente() {
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
	
		UCManterPacienteManager manter = new UCManterPacienteManager();
		String[] paciente;
		
		try {
			paciente = manter.consultarPaciente(request.getParameter("CPF"));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
;		request.setAttribute("Nome1", paciente[0]);
		request.setAttribute("Nome2", paciente[1]);
		request.setAttribute("Nome3", paciente[2]);
		request.setAttribute("Complemento", paciente[3]);
		request.setAttribute("Sexo", paciente[4]);
		request.setAttribute("Data", paciente[5]);
		request.setAttribute("Tipo", paciente[6]);
		request.setAttribute("CPF", paciente[7]);
		request.setAttribute("Casa", paciente[8]);
		request.setAttribute("Email", paciente[9]);
		request.setAttribute("Email2", paciente[10]);
		request.setAttribute("Telefone", paciente[11]);
		request.setAttribute("Telefone", paciente[12]);
		
		request.getRequestDispatcher("Consultar.jsp").forward(request, response);
		
	}

}
