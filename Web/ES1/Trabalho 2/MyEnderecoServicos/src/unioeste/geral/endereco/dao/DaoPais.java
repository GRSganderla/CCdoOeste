package unioeste.geral.endereco.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.Conexao;

public class DaoPais {

	public String selectNomePais(Connection con, int idPais) throws Exception {
		// TODO Auto-generated method stub
		return Conexao.getSelect(con, "SELECT nomePais FROM pais WHERE idPais='"+idPais+"';");
	}

}
