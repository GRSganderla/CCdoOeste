package controle;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;

import dao.DaoEmail;
import unioeste.classesbo.Email;
import util.NegocioException;

public class ColEmail {

	public Connection con;

	public ColEmail(Connection connection) {

		con = connection;

	}

	public int inserirEmails(ArrayList<Email> Email, int idPaciente) throws NegocioException, SQLException {

		DaoEmail emails = new DaoEmail();

		emails.insereEmail(Email, con, idPaciente);

		return 0;
	}
	
	public ArrayList<Email> consultarEmails(int idPaciente, Connection con) throws NegocioException, SQLException{
		
		DaoEmail email = new DaoEmail();
			
		ArrayList<Email> emails = email.consultaEmail(idPaciente, con);
		
		return emails;
	}

	public Connection getCon() {
		return con;
	}

	public void setCon(Connection con) {
		this.con = con;
	}
}