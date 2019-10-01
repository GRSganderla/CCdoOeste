package unioeste.geral.endereco.col;

import java.sql.Connection;

import unioeste.geral.endereco.bo.Pais;
import unioeste.geral.endereco.dao.DaoPais;

public class ColPais {

	private Connection con;
	
	public ColPais(Connection con) {
		
		this.con = con;
	}

	public Pais getPais(int idPais) throws Exception {

		Pais pais = new Pais();
		DaoPais daoPais = new DaoPais();
		
		pais.setIdPais(idPais);
		
		String nomePais = daoPais.selectNomePais(con, idPais);
		
		pais.setNomePais(nomePais);
		
		return pais;
	}
}
