package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import unioeste.classesbo.Email;

public class DaoEmail {

	public void insereEmail(ArrayList<Email> listaEmails, Connection con, int idPaciente) throws SQLException {

		String sql = "INSERT INTO email (Email, paciente_idPaciente) VALUES (?,?)";

		// PreparedStatement create = con.prepareStatement(sql);

		for (Email email : listaEmails) {
			PreparedStatement create = con.prepareStatement(sql);
			create.setString(1, email.getEmail());
			create.setInt(2, idPaciente);
			create.execute();
		}

	}

	public ArrayList<Email> consultaEmail(int idPaciente, Connection con) throws SQLException {
		
		ArrayList<Email> m = new ArrayList<Email>();
		String sql = "SELECT * FROM email WHERE paciente_idPaciente = ?;" ;
				
		PreparedStatement stt = con.prepareStatement(sql);
		stt.setInt(1, idPaciente);
		ResultSet res = stt.executeQuery();
		int i=0;
		while (res.next()) {
		Email email = new Email();
		email.setEmail(res.getString("Email"));
		System.out.println(res.getString("Email"));
		email.setIdEmail(res.getInt("idEmail"));
		System.out.println(res.getInt("idEmail"));
		
		m.add(i,email);
		
		i++;
		}		
	
	
		
		return m;
	}

}

