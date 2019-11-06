package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.homebank.bo.Banco;
import unioeste.geral.homebank.dao.DaoBanco;

public class ColBanco {

	private Connection con;
	
	public ColBanco(Connection conn) {
		con = conn;
	}
	
	public int valida(int favBanco) {
		
		DaoBanco daoB = new DaoBanco(con);
		
		int idBanco = daoB.getIdBanco(favBanco);
		
		return idBanco;
	}

	public Banco getBanco(int favBanco) {
		// TODO Auto-generated method stub
		return null;
	}
}
