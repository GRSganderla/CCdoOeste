package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.homebank.dao.DaoAgencia;

public class ColAgencia {

	private Connection con;
	
	public ColAgencia(Connection conn) {
		con = conn;
	}
	
	public int valida(int favAgencia) {
		
		DaoAgencia daoA = new DaoAgencia(con);
		
		int idAgencia = daoA.getIdAgencia(favAgencia);
		
		return idAgencia;
	}
}
