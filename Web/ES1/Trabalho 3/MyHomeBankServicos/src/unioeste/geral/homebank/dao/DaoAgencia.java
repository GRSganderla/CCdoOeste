package unioeste.geral.homebank.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.ConexaoBD;

public class DaoAgencia {
	
	private Connection con;

	public DaoAgencia(Connection conn) {
		con = conn;
	}

	public int getIdAgencia(int nroAgencia) {
		
		int id = 0;
		
		String sql = "SELECT idAgencia FROM Agencia WHERE idAgencia = '"+ nroAgencia +"';";
		
		try {
			
			id = Integer.parseInt(ConexaoBD.getSelect(con, sql));
		}
		catch(Exception e) {e.printStackTrace();}
		
		return id;
	}

}
