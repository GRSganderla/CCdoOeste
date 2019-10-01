package unioeste.geral.endereco.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.Conexao;

public class DaoEndereco {
		
	public ArrayList<Integer> selectIds(Connection con, String CEP) throws Exception {
		
		ArrayList<Integer> ids = new ArrayList<Integer>();
		
		ArrayList<String> stringID = new ArrayList<String>();
		
		stringID = Conexao.getTabela(con, "SELECT idEndereco, idLougradouro, idBairro, idCidade FROM endereco WHERE cep='"+CEP+"';");
		
		for(String a: stringID) {
			ids.add(Integer.parseInt(a));
		}
		
		return ids;
	}
	
	public String selectCEP(Connection con, int idEndereco) throws Exception {
		
		return Conexao.getSelect(con, "SELECT CEP FROM endereco WHERE idEndereco='"+idEndereco+"';");
	}
}
