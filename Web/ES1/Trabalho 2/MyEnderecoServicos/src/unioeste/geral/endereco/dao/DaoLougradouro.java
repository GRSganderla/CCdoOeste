package unioeste.geral.endereco.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.Conexao;

public class DaoLougradouro {

	public String selectNomeLougradouro(Connection con, int idLougradouro) throws Exception {
		// TODO Auto-generated method stub
		return Conexao.getSelect(con, "SELECT nomeLougradouro FROM lougradouro WHERE idLougradouro='"+idLougradouro+"';");
	}

}
