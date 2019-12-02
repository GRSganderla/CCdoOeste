package unioeste.geral.homebank.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.ConexaoBD;

public class DaoBanco {

	private Connection con;

	public DaoBanco(Connection conn) {
		con = conn;
	}

	public int getIdBanco(int idBanco) {
		
		int id = 0;
		
		String sql = "SELECT idBanco FROM Banco WHERE idBanco = '"+ idBanco +"';";
		
		try {
			
			id = Integer.parseInt(ConexaoBD.getSelect(con, sql));
		}
		catch(Exception e) {e.printStackTrace();}
		
		return id;
	}

}
