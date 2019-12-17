package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;

public class Produto implements Serializable{

	public Produto(int idProduto, String codigo_barras, String nome_produto, int qtde_estoque, float preco_Venda,
			float preco_Compra, int idFornec) {
		super();
		this.idProduto = idProduto;
		this.codigo_barras = codigo_barras;
		this.nome_produto = nome_produto;
		this.qtde_estoque = qtde_estoque;
		Preco_Venda = preco_Venda;
		Preco_Compra = preco_Compra;
		this.idFornecedor = idFornec;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -7956027698798255973L;

	private int idProduto;
	private String codigo_barras;
	private String nome_produto;
	private int qtde_estoque;
	private float Preco_Venda;
	private float Preco_Compra;
	private int idFornecedor;
	
	public int getIdProduto() {
		return idProduto;
	}
	public void setIdProduto(int idProduto) {
		this.idProduto = idProduto;
	}
	public String getCodigo_barras() {
		return codigo_barras;
	}
	public void setCodigo_barras(String codigo_barras) {
		this.codigo_barras = codigo_barras;
	}
	public String getNome_produto() {
		return nome_produto;
	}
	public void setNome_produto(String nome_produto) {
		this.nome_produto = nome_produto;
	}
	public int getQtde_estoque() {
		return qtde_estoque;
	}
	public void setQtde_estoque(int qtde_estoque) {
		this.qtde_estoque = qtde_estoque;
	}
	public float getPreco_Venda() {
		return Preco_Venda;
	}
	public void setPreco_Venda(float preco_Venda) {
		Preco_Venda = preco_Venda;
	}
	public float getPreco_Compra() {
		return Preco_Compra;
	}
	public void setPreco_Compra(float preco_Compra) {
		Preco_Compra = preco_Compra;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public int getIdFornecedor() {
		return idFornecedor;
	}
	public void setIdFornecedor(int idFornecedor) {
		this.idFornecedor = idFornecedor;
	}
}
