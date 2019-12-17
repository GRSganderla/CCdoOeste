package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;
import java.util.ArrayList;

public abstract class Nota implements Serializable{

	public Nota(String data, float totalNota, float descontoTotal, float valorLiquido,
			ArrayList<ItemProduto> listaItens) {
		super();
		this.data = data;
		TotalNota = totalNota;
		DescontoTotal = descontoTotal;
		ValorLiquido = valorLiquido;
		this.listaItens = listaItens;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -1665280179632967467L;

	private String data;
	
	private float TotalNota;
	private float DescontoTotal;
	private float ValorLiquido;
	
	private ArrayList<ItemProduto> listaItens;
	
	public String getData() {
		return data;
	}
	public void setData(String data) {
		this.data = data;
	}
	public float getTotalNota() {
		return TotalNota;
	}
	public void setTotalNota(float totalNota) {
		TotalNota = totalNota;
	}
	public float getDescontoTotal() {
		return DescontoTotal;
	}
	public void setDescontoTotal(float descontoTotal) {
		DescontoTotal = descontoTotal;
	}
	public float getValorLiquido() {
		return ValorLiquido;
	}
	public void setValorLiquido(float valorLiquido) {
		ValorLiquido = valorLiquido;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public ArrayList<ItemProduto> getListaItens() {
		return listaItens;
	}
	public void setListaItens(ArrayList<ItemProduto> listaItens) {
		this.listaItens = listaItens;
	}
}
