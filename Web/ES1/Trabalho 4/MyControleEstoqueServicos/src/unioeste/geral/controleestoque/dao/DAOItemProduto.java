package unioeste.geral.controleestoque.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class DAOItemProduto {
	private Connection conn;

	public DAOItemProduto(Connection con) {
		this.conn = con;
	}

	public int getMaxId() throws ControleEstoqueException {
		// TODO Auto-generated method stub
		ConexaoBD cBD = new ConexaoBD();
		
		String res = null;
		try {
			res = cBD.getSelect(conn, "SELECT MAX(iditemNotaVenda) FROM itemnotavenda");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if(res != null)
			return Integer.parseInt(res);
		else 
			throw new ControleEstoqueException("Falha ao pegar o id do ultimo registro de um Item Nota de Venda");
	}

	public void insereNovoItem(String query) throws ControleEstoqueException {
		
		ConexaoBD cBD = new ConexaoBD();
		
		try {
			cBD.insereSQLComand(conn, query);
		} catch (Exception e) {
			e.printStackTrace();
			throw new ControleEstoqueException("Falha na inserção de um novo Item de Nota de Venda");
		}
		
	}

	public ArrayList<String> getAllItens(String query) throws ControleEstoqueException {
		// TODO Auto-generated method stub
		ConexaoBD cBD = new ConexaoBD();
		
		ArrayList<String> res = null;
		try {
			res = cBD.getTabela(conn, query);
		}catch(Exception e) {
			e.printStackTrace();
			throw new ControleEstoqueException("Não existe itens de Venda de Produto");
		}
		
		return res;
	}

}
