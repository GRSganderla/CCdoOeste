package unioeste.geral.controleestoque.col;

import java.sql.Connection;

import unioeste.geral.controle_estoque.bo.especifica.NotadeVenda;
import unioeste.geral.controleestoque.dao.DAONotaVenda;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColNotaVenda {

	public Connection con;
	
	public ColNotaVenda(Connection con) {
		
		this.con = con;
	}

	public void verificaNroNota(int nro) throws ControleEstoqueException {

		DAONotaVenda dNV = new DAONotaVenda(this.con);
		
		dNV.checkNota(nro);
	}

	public void insereNotaV(int codigo, String data, float desconto, float tot, int idCliente) {

		DAONotaVenda dNV = new DAONotaVenda(this.con);
		
		String query = "INSERT INTO notavenda (idnotaVenda, data, desconto, valorTotal, idcliente) VALUES ("+codigo+", '"+data+"', "+desconto+","+tot+", "+idCliente+");";
		
		dNV.insertNota(query);
	}

	public NotadeVenda getNotaVenda(int nroNota) throws ControleEstoqueException {
		// TODO Auto-generated method stub
		DAONotaVenda dNV = new DAONotaVenda(this.con);
		
		NotadeVenda cons = dNV.getNotaById(nroNota);
		
		return cons;
	}
	
	
}
