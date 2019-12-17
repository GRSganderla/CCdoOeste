package unioeste.geral.controleestoque.col;

import java.sql.Connection;

import unioeste.geral.controleestoque.dao.DAOCliente;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColCliente {
	
	private Connection con;

	public ColCliente(Connection con) {
		this.con = con;
	}

	public int verificaCliente(String nome) throws ControleEstoqueException {
		
		DAOCliente daoCli = new DAOCliente(this.con);
		
		int cod = daoCli.getClienteId(nome);
		
		return cod;
	}

	public String pegaNome(int idCliente) throws ControleEstoqueException {
		// TODO Auto-generated method stub
		DAOCliente daoCli = new DAOCliente(this.con);
		
		String query = "SELECT nome FROM Cliente WHERE idcliente="+idCliente+";";
		
		String nome = daoCli.getNomeCliente(query);
		
		return nome;
	}
}
