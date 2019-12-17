package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;
import java.util.ArrayList;

import unioeste.geral.controle_estoque.bo.PessoaJuridica;

public class Fornecedor implements Serializable{

	public Fornecedor(PessoaJuridica fornecedor, int idFornecedor, ArrayList<Produto> listProduto,
			ArrayList<Nota> notasCompra) {
		super();
		this.fornecedor = fornecedor;
		this.idFornecedor = idFornecedor;
		this.listProduto = listProduto;
		NotasCompra = notasCompra;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -1163957850137806256L;
	private PessoaJuridica fornecedor;
	private int idFornecedor;
	
	private ArrayList<Produto> listProduto;
	private ArrayList<Nota> NotasCompra;
	
	public PessoaJuridica getFornecedor() {
		return fornecedor;
	}
	public void setFornecedor(PessoaJuridica fornecedor) {
		this.fornecedor = fornecedor;
	}
	public int getIdFornecedor() {
		return idFornecedor;
	}
	public void setIdFornecedor(int idFornecedor) {
		this.idFornecedor = idFornecedor;
	}
	public ArrayList<Produto> getListProduto() {
		return listProduto;
	}
	public void setListProduto(ArrayList<Produto> listProduto) {
		this.listProduto = listProduto;
	}
	public ArrayList<Nota> getNotaVenda() {
		return NotasCompra;
	}
	public void setNotaVenda(ArrayList<Nota> notaVenda) {
		NotasCompra = notaVenda;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
}
