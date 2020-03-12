package unioeste.geral.controleestoque.col;

import java.sql.Connection;

import unioeste.geral.controle_estoque.bo.especifica.NotadeCompra;
import unioeste.geral.controleestoque.dao.DAONotaCompra;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColNotaCompra {
	
	public Connection con;

	public ColNotaCompra(Connection con) {
		
		this.con = con;
	}

	public NotadeCompra getNotaCompra(int nroNota) throws ControleEstoqueException {

		DAONotaCompra dNC = new DAONotaCompra(this.con);
		
		NotadeCompra cons = dNC.getNotaById(nroNota);
		
		return cons;
	}
}
