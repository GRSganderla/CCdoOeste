package unioeste.geral.endereco.col;

import java.sql.Connection;

import unioeste.geral.endereco.bo.Pais;
import unioeste.geral.endereco.bo.UF;
import unioeste.geral.endereco.dao.DaoUF;

public class ColUF {

	private Connection con;
	
	public ColUF(Connection con) {
		
		this.con = con;
	}

	public UF getUF(int idUF) throws Exception {
		
		UF uf = new UF();
		DaoUF daoUF = new DaoUF();
		int idPais;
		String nomeUF;
		
		nomeUF = daoUF.selectNomeUF(con, idUF);
		idPais = daoUF.selectIdPais(con, idUF);
		
		uf.setIdUF(idUF);
		uf.setNomeUF(nomeUF);
		
		ColPais colP = new ColPais(con);
		Pais pais = new Pais();
		
		pais = colP.getPais(idPais);
		uf.setPais(pais);
		
		return uf;
	}
	
}
