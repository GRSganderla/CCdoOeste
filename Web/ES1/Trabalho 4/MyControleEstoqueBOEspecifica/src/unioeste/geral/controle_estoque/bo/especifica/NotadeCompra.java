package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;
import java.util.ArrayList;

public class NotadeCompra extends Nota implements Serializable{

	public NotadeCompra(String data, float totalNota, float descontoTotal, float valorLiquido,
			ArrayList<ItemProduto> listaItens, int idCodigo, int idFornecedor) {
		super(data, totalNota, descontoTotal, valorLiquido, listaItens);
		this.idCodigo = idCodigo;
		this.setIdFornecedor(idFornecedor);
	}

	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -2969178220055356949L;

	private int idCodigo;
	private int idFornecedor;

	public int getIdCodigo() {
		return idCodigo;
	}

	public void setIdCodigo(int idCodigo) {
		this.idCodigo = idCodigo;
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
