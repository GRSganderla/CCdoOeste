package unioeste.geral.endereco.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.Conexao;

public class DaoUF {

	public String selectNomeUF(Connection con, int idUF) throws Exception {
		
		return Conexao.getSelect(con, "SELECT nomeUF FROM UF WHERE idUF='"+ idUF+"';");
	}

	public int selectIdPais(Connection con, int idUF) throws Exception {

		String stringIdPais = Conexao.getSelect(con, "SELECT idPais FROM UF WHERE idUF='"+idUF+"';");
		
		int idPais = Integer.parseInt(stringIdPais);
		
		return idPais;
	}

}
