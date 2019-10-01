package controle;

import java.sql.Connection;
import java.sql.SQLException;

import dao.DaoPaciente;
import unioeste.classesbo.CPF;
import unioeste.classesbo.especificas.Paciente;
import util.NegocioException;

public class ColPaciente {

	public Connection con;

	public ColPaciente(Connection connection) {

		con = connection;

	}

	public boolean obterPacientePorCPF(CPF cpf) throws NegocioException {

		if (cpf != null)
			return true;
		else
			return false;
	}

	public int inserirPaciente(Paciente a, Connection con) throws NegocioException, SQLException {
		
		int res = 0;
		DaoPaciente daoPaciente = new DaoPaciente();
		res = daoPaciente.inserePaciente(a, con);
		
		return res ;
	}
	
	public Paciente consultarPaciente(String cpf, Connection con) throws NegocioException, SQLException {
		
		DaoPaciente paciente = new DaoPaciente();
		
		Paciente res = new Paciente();
		
		res = paciente.consultar(cpf, con);
		
		return res;
		
	}
	
	public Connection getCon() {
		return con;
	}

	public void setCon(Connection con) {
		this.con = con;
	}
}
