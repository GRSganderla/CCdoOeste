package unioeste.geral.endereco.col;

import java.sql.Connection;

import unioeste.geral.endereco.bo.Lougradouro;
import unioeste.geral.endereco.dao.DaoLougradouro;

public class ColLougradouro {

	private Connection con;
	
	public ColLougradouro(Connection con) {
		
		this.con = con;
	}
	
	public Lougradouro getLougradouro(int idLougradouro) throws Exception {

		Lougradouro lougradouro = new Lougradouro();
		
		lougradouro.setIdLougradouro(idLougradouro);
		
		DaoLougradouro daoL = new DaoLougradouro();
		
		String nomeLougradouro = daoL.selectNomeLougradouro(con, idLougradouro);
		
		lougradouro.setNomeLougradouro(nomeLougradouro);
		
		return lougradouro;
	}

}
