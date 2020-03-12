package unioeste.geral.controleestoque.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controle_estoque.bo.especifica.NotadeCompra;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class DAONotaCompra {
	
	private Connection conn;

	public DAONotaCompra(Connection con) {
		this.conn = con;
	}

	public NotadeCompra getNotaById(int nroNota) throws ControleEstoqueException {
		
		ConexaoBD sql = new ConexaoBD();
		
		String query = "SELECT * FROM notacompra WHERE idnotaCompra="+nroNota+";";
		
		ArrayList<String> res = null;
		
		try {
			res = sql.getTabela(conn, query);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if(res == null) {
			throw new ControleEstoqueException("Nota com o numero "+nroNota+" não está registrada no BD!");
		}
    
		float desconto = Float.parseFloat(res.get(2));
		float valorTotal = Float.parseFloat(res.get(3));
		int idForn = Integer.parseInt(res.get(4));
		
		return new NotadeCompra(res.get(1), valorTotal, desconto, 0, null, 0, idForn);
	}
}
