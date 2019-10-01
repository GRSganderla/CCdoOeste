package unioeste.geral.endereco.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.Conexao;

public class DaoCidade {

	public int selectIdUF(Connection con, int idCid) {

		String stringiduf = "0";
		try {
			stringiduf = Conexao.getSelect(con, "SELECT idUF FROM cidade WHERE idCidade='"+idCid+"';");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		int idUF = Integer.parseInt(stringiduf);
		
		return idUF;
	}

	public String selectNomeCidade(Connection con, int idCid) throws Exception {
		
		return Conexao.getSelect(con, "SELECT nomeCidade FROM cidade WHERE idCidade='"+idCid+"';");
	}

}
