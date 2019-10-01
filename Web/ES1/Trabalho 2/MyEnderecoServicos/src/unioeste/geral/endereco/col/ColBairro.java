package unioeste.geral.endereco.col;

import java.sql.Connection;

import unioeste.geral.endereco.bo.Bairro;
import unioeste.geral.endereco.dao.DaoBairro;

public class ColBairro {

	private Connection con;
	
	public ColBairro(Connection conn) {
		
		con = conn;
	}
	
	public Bairro getBairro(int id) throws Exception {
		
		Bairro bairro = new Bairro();
		DaoBairro daob = new DaoBairro();
		String nome = null;
		
		bairro.setIdBairro(id);
		
		nome = daob.selectBairroPorID(this.con, id);
		
		bairro.setNomeBairro(nome);
		
		return bairro;
	}
	
}
