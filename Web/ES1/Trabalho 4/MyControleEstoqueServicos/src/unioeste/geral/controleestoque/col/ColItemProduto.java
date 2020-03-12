package unioeste.geral.controleestoque.col;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.geral.controleestoque.dao.DAOItemProduto;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class ColItemProduto {
	
	public Connection con;

	public ColItemProduto(Connection con) {
		this.con = con;
	}

	public int lastId() throws ControleEstoqueException {
		// TODO Auto-generated method stub
		DAOItemProduto dIP = new DAOItemProduto(this.con);
		
		int id = dIP.getMaxId();
		
		return id;
	}

	public void insereItem(int id, int qtde, float preco, float total, int nroNota, int codigoP) throws ControleEstoqueException {

		DAOItemProduto dIP = new DAOItemProduto(this.con);
		
		String query = "INSERT INTO itemnotavenda (iditemNotaVenda, quantidade, preço, total, idnotaVenda, idproduto) VALUES ("+id+","+qtde+","+preco+","+total+","+nroNota+","+codigoP+");";
		
		dIP.insereNovoItem(query);
	}

	public String[][] pegaItensProdutos(int nroNota) throws ControleEstoqueException {
		// TODO Auto-generated method stub
		DAOItemProduto dIP = new DAOItemProduto(this.con);
		
		String query = "SELECT itemnotaVenda.idproduto, produto.nome, itemnotaVenda.quantidade, itemnotaVenda.preço, itemnotaVenda.total FROM itemnotaVenda, produto WHERE itemnotaVenda.idnotaVenda="+nroNota+" AND itemnotaVenda.idproduto=produto.idproduto;";
		
		ArrayList<String> res = dIP.getAllItens(query);
		
		String ret[][] = new String[(res.size()/5)+1][5];
		
		int i = 0, j = 0;
		for(String ind: res) {
			ret[i][j] = ind;
			if(j == 4) {
				j = 0;
				i += 1;
			}
			else
				j++;
		}
		
		return ret;
	}

}
