package unioeste.geral.controleestoque.manager;

import java.sql.Connection;
import java.sql.SQLException;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controle_estoque.bo.especifica.Fornecedor;
import unioeste.geral.controle_estoque.bo.especifica.NotadeVenda;
import unioeste.geral.controle_estoque.bo.especifica.Produto;
import unioeste.geral.controleestoque.col.ColCliente;
import unioeste.geral.controleestoque.col.ColFornecedor;
import unioeste.geral.controleestoque.col.ColItemProduto;
import unioeste.geral.controleestoque.col.ColNotaVenda;
import unioeste.geral.controleestoque.col.ColProduto;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class UCControleEstoqueServicos {
	
	public Connection con;
	
	public UCControleEstoqueServicos(){
		ConexaoBD novaCon = new ConexaoBD();
		
		try {
			this.con = novaCon.getConnection();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public int RegistrarVenda(String nro, String nome, String data, String codigo[], String nomeProduto[], String qtde[], String precos[], String totais[], String total, String desconto, String valorLiq) {
		
		ColCliente cCli = new ColCliente(this.con);
		
		try {
			
			con.setAutoCommit(false);
			
			int idCliente = cCli.verificaCliente(nome);
			
			ColNotaVenda cNV = new ColNotaVenda(this.con);
			cNV.verificaNroNota(Integer.parseInt(nro));
			ColProduto ColP = new ColProduto(this.con);
			
			for(int i = 0; i < codigo.length; i++) {
				
				ColP.verificaProduto(codigo[i], nomeProduto[i], qtde[i], precos[i]);
			}
			
			float tot = Float.parseFloat(valorLiq);
			
			if(tot != (Float.parseFloat(total) - Float.parseFloat(desconto))) {
				
				tot = Float.parseFloat(total) - Float.parseFloat(desconto);
			}
			
			cNV.insereNotaV(Integer.parseInt(nro), data, Float.parseFloat(desconto), tot, idCliente);
			
			ColItemProduto colIP = new ColItemProduto(this.con);
			
			int id = colIP.lastId()+1;
			
			for(int i = 0; i < codigo.length; i++) {
				
				id += i;
				colIP.insereItem(id, Integer.parseInt(qtde[i]), Float.parseFloat(precos[i]), Float.parseFloat(totais[i]), Integer.parseInt(nro), Integer.parseInt(codigo[i])); 
			}
			
			for(int i = 0; i < codigo.length; i++) {
				
				ColP.diminuiEstoque(Integer.parseInt(codigo[i]), Integer.parseInt(qtde[i]));
			}
			
			con.commit();
			
			return 1;
			
		} catch (ControleEstoqueException e) {
			try {
				con.rollback();
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			e.printStackTrace();
		} catch (SQLException e) {
			try {
				con.rollback();
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			e.printStackTrace();
		}
		
		return 0;
	}
	
	
	public String[][] ConsultarNotaVenda(int nroNota) {
		
		ColNotaVenda colNota = new ColNotaVenda(this.con);
		
		NotadeVenda not;
		try {
			not = colNota.getNotaVenda(nroNota);
		
			ColCliente cCli = new ColCliente(this.con);
			String nome = cCli.pegaNome(not.getIdCliente());
			
			ColItemProduto cIP = new ColItemProduto(this.con);
			
			String [][] produtos = cIP.pegaItensProdutos(nroNota);
			String[][] res = new String[produtos.length+1][5];
			
			res[0][0] = String.valueOf(nroNota);
			res[0][1] = not.getData();
			res[0][2] = nome;
			
			int i;
			for(i = 0; i < produtos.length; i++) {
				res[i+1][0] = produtos[i][0];
				res[i+1][1] = produtos[i][1];
				res[i+1][2] = produtos[i][2];
				res[i+1][3] = produtos[i][3];
				res[i+1][4] = produtos[i][4];
			}
			
			res[i][0] = String.valueOf(not.getTotalNota());
			res[i][1] = String.valueOf(not.getDescontoTotal());
			res[i][2] = String.valueOf(not.getValorLiquido());
		
			return res;
		} catch (ControleEstoqueException e) {
			// TODO Auto-generated catch block
			System.err.println(e.getMessage());
		} 
		
		return null;
	}
	
	public String[] ConsultarProduto(int codigo) {
		
		ColProduto prod = new ColProduto(this.con);
		
		Produto produto;
		
		try {
			produto = prod.getProduto(codigo);
			
			ColFornecedor fornec = new ColFornecedor(this.con);
			
			Fornecedor forn = fornec.getFornecedor(produto.getIdFornecedor());
			
			String[] retorno = new String[6];
			retorno[0] = produto.getCodigo_barras();
			retorno[1] = produto.getNome_produto();
			retorno[2] = forn.getFornecedor().getNome();
			retorno[3] = String.valueOf(produto.getPreco_Compra());
			retorno[4] = String.valueOf(produto.getPreco_Venda());
			retorno[5] = String.valueOf(produto.getQtde_estoque());
			
			return  retorno;
			
		} catch (ControleEstoqueException e) {
			System.err.println(e.getMessage());
		}
		
		return null;
	}
}
