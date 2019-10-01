package controle;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;
import dao.DaoTelefone;
import unioeste.classesbo.Telefone;
import util.NegocioException;

public class ColTelefone {
	
	public Connection con;
	
	public ColTelefone(Connection connection) {

		con = connection;

	}
	
	public boolean validarFones(ArrayList<Telefone> ListaFonesPaciente) throws NegocioException {
	
		
		
		return true;

	}
	
	public void inserirTelefones(ArrayList<Telefone> telefone, int idPaciente, Connection con) throws NegocioException, SQLException {
		
		DaoTelefone telefone1 = new DaoTelefone();
		
		telefone1.insereTelefone(telefone, con, idPaciente);
		
		
	}
	
	public ArrayList<Telefone> consultarTelefone(int idPaciente, Connection con) throws NegocioException, SQLException{
		
		DaoTelefone telefone = new DaoTelefone();
			
		ArrayList<Telefone> telefone1 = telefone.consultaTelefone(idPaciente, con);
		
		return telefone1;
	}
	
	public Connection getCon() {
		return con;
	}

	public void setCon(Connection con) {
		this.con = con;
	}
}