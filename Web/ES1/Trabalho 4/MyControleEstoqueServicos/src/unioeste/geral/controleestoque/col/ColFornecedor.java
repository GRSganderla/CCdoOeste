package unioeste.geral.controleestoque.col;

import java.sql.Connection;

import unioeste.geral.controle_estoque.bo.especifica.Fornecedor;
import unioeste.geral.controleestoque.dao.DAOFornecedor;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColFornecedor {
	
	private Connection con;

	public ColFornecedor(Connection con) {
		this.con = con;
	}

	public Fornecedor getFornecedor(int idFornecedor) throws ControleEstoqueException {
		
		DAOFornecedor dForn = new DAOFornecedor(this.con);
		
		Fornecedor fab = dForn.getFornecById(idFornecedor);
		
		return fab;
	}

}
