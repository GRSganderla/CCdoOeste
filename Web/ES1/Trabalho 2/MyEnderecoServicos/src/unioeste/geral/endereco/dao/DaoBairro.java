package unioeste.geral.endereco.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.Conexao;

public class DaoBairro {

	public String selectBairroPorID(Connection con, int id) throws Exception{
		
		String nome = null;
		try {
			nome = Conexao.getSelect(con, "SELECT nomeBairro FROM bairro WHERE idBairro = '"+id+"'");
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return nome;
	}
}