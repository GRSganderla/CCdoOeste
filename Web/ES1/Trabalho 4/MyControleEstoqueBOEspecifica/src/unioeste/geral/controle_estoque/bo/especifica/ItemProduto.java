package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;

public class ItemProduto implements Serializable{

	public ItemProduto(int qtde, float total, float preco, Produto item) {
		super();
		this.qtde = qtde;
		Total = total;
		Preco = preco;
		this.item = item;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -6873044531740177070L;

	private int qtde;
	private float Total;
	private float Preco;
	
	private Produto item;
	
	public Produto getItem() {
		return item;
	}
	public void setItem(Produto item) {
		this.item = item;
	}
	public int getQtde() {
		return qtde;
	}
	public void setQtde(int qtde) {
		this.qtde = qtde;
	}
	public float getTotal() {
		return Total;
	}
	public void setTotal(float total) {
		Total = total;
	}
	public float getPreco() {
		return Preco;
	}
	public void setPreco(float preco) {
		Preco = preco;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
}
