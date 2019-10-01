package unioeste.geral.endereco.col;

import java.sql.Connection;

import unioeste.geral.endereco.bo.*;
import unioeste.geral.endereco.dao.DaoCidade;

public class ColCidade {

	private Connection con;
	
	public ColCidade(Connection con) {
		
		this.con = con;
	}
	
	public Cidade getCidade(int idCid) throws Exception {
		
		Cidade cid = new Cidade();
		String nome = null;
		DaoCidade daoCid = new DaoCidade();
		int idUF;
		
		cid.setIdCidade(idCid);
		
		try {
			nome = daoCid.selectNomeCidade(con, idCid);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		cid.setNomeCidade(nome);
		
		idUF = daoCid.selectIdUF(con, idCid);
		
		UF uf = new UF();
		ColUF colUf = new ColUF(con);
		
		uf = colUf.getUF(idUF);
		
		cid.setUF(uf);
		
		return cid;
	}
}
