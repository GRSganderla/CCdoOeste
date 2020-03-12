package unioeste.geral.controleestoque.col;

import java.sql.Connection;

import unioeste.geral.controle_estoque.bo.especifica.Produto;
import unioeste.geral.controleestoque.dao.DAOProduto;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColProduto {
	
	public Connection con;

	public ColProduto(Connection con) {
		this.con = con;
	}

	public Produto getProduto(int codigoProduto) throws ControleEstoqueException {
		
		DAOProduto daoP = new DAOProduto(this.con);
		
		Produto alvo = daoP.getProdutoPorCod(codigoProduto);
		
		return alvo;
	}

	public void verificaProduto(String codigo, String nome, String qtd, String preco) throws NumberFormatException, ControleEstoqueException {
		
		DAOProduto daoP = new DAOProduto(this.con);
		
		Produto check = daoP.getProdutoPorCod(Integer.parseInt(codigo));
		
		if(!check.getNome_produto().equals(nome) || (check.getPreco_Compra() > Float.parseFloat(preco)) || (check.getQtde_estoque() <= 0) || (check.getQtde_estoque() < Integer.parseInt(qtd)))
			throw new ControleEstoqueException("O Produto selecionado na Nota de Venda não atende as requirimentos para a Venda!");
			
	}

	public void diminuiEstoque(int codigo, int qtde) throws ControleEstoqueException {
		
		DAOProduto daoP = new DAOProduto(this.con);
		
		String query = "UPDATE produto SET quantEstoque = quantEstoque - "+qtde+" WHERE idproduto="+codigo+";";
		
		daoP.retiraEstq(query);
	}
}
