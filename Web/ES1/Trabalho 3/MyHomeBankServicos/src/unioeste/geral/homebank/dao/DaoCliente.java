package unioeste.geral.homebank.dao;

import java.sql.Connection;

import unioeste.apoio.MySQL.ConexaoBD;

public class DaoCliente {

	private Connection com;
	
	public DaoCliente(Connection con) {
		com = con;
	}

	public int buscaCliente(String nome, String doc) {
		
		int idCliente = 0;
		String sql = "SELECT idCliente FROM cliente WHERE nomeCliente = '"+nome+"' AND (CPF = '"+doc+"' OR CNPJ = '"+doc+"');";
		
		try {
			
			idCliente = Integer.parseInt(ConexaoBD.getSelect(com, sql));
		}
		catch(Exception e) {e.printStackTrace();}
		
		return idCliente;
	}
}
