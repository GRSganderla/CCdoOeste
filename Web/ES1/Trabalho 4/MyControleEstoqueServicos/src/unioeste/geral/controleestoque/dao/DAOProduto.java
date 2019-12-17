package unioeste.geral.controleestoque.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controle_estoque.bo.especifica.Produto;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class DAOProduto {
	
	private Connection conn;

	public DAOProduto(Connection con) {
		this.conn = con;
	}

	public Produto getProdutoPorCod(int codigoProduto) throws ControleEstoqueException {
		
		ConexaoBD sql = new ConexaoBD();
		
		String query = "SELECT * FROM Produto WHERE idProduto="+codigoProduto+";";
		
		ArrayList<String> res = null;
		
		try {
			res = sql.getTabela(conn, query);
		} catch (Exception e) {

			e.printStackTrace();
		}
		
		if(res == null) {
			throw new ControleEstoqueException("Produto com id de "+codigoProduto+" não está registrado no BD!");
		}
		
		String codBarras = res.get(1);
		String nomeProduto = res.get(2);
		int qtde = Integer.parseInt(res.get(3));
		float custo = Float.parseFloat(res.get(4));
		float venda = Float.parseFloat(res.get(5));
		int idFornec = Integer.parseInt(res.get(6));
		
		return new Produto(codigoProduto, codBarras, nomeProduto, qtde, venda, custo, idFornec);
	}

	public void retiraEstq(String query) throws ControleEstoqueException {

		ConexaoBD cBD = new ConexaoBD();
		
		try {
			cBD.insereSQLComand(conn, query);
		} catch (Exception e) {
			e.printStackTrace();
			throw new ControleEstoqueException("Falha ao diminuir o estoque do Produto!");
		}
	}

}
