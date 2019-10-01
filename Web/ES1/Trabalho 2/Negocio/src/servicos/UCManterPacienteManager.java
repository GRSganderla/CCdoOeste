package servicos;

import java.sql.Connection;

import controle.ColEmail;
import controle.ColPaciente;
import controle.ColSexo;
import controle.ColTelefone;
import sql.Query;
import unioeste.classesbo.especificas.Paciente;

public class UCManterPacienteManager {

	public UCManterPacienteManager() {

	}

	public void cadastrarPaciente(Paciente paciente) throws Exception {

		Connection con = Query.getConnection();
		con.setAutoCommit(false);

		ColPaciente colPaciente = new ColPaciente(con);
		
		try {

			if (colPaciente.obterPacientePorCPF(paciente.getPessoa().getCPF())) {
				paciente.validaObjeto();
				
				ColSexo colSexo = new ColSexo(con);
				
				
				paciente.getPessoa().getSexo().setIdSexo(colSexo.obterSexoPorSigla(paciente.getPessoa().getTipoSexo()));
				//paciente.getPessoa().getSexo().setIdSexo(1);
				
				int id = colPaciente.inserirPaciente(paciente, con);
				paciente.setIdPaciente(id);
				
				ColTelefone colTelefone = new ColTelefone(con);
				// colTelefone.validarFones(paciente.getPessoa().getListaTelefone());
				colTelefone.inserirTelefones(paciente.getPessoa().getListaTelefone(), paciente.getIdPaciente(), con);
				

				ColEmail colEmail = new ColEmail(con);
				colEmail.inserirEmails(paciente.getPessoa().getListaEmail(), paciente.getIdPaciente());

			}
			con.commit();

		} catch (Exception e) {

			e.printStackTrace();
			con.rollback();
		}

	}

	public Paciente consultarPaciente(String cpf) throws Exception {
		
		Connection con = Query.getConnection();
		

		ColPaciente colPaciente = new ColPaciente(con);
		Paciente paciente = new Paciente();
		paciente = colPaciente.consultarPaciente(cpf, con);
		
		ColTelefone colTelefone = new ColTelefone(con);
		paciente.getPessoa().setListaTelefone(colTelefone.consultarTelefone(paciente.getIdPaciente(), con));
		
		ColEmail colEmail = new ColEmail(con);
		paciente.getPessoa().setListaEmail(colEmail.consultarEmails(paciente.getIdPaciente(), con));
		
		return paciente;
		
	}

}
