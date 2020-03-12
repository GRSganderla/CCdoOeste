package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;
import java.util.ArrayList;

public class NotadeVenda extends Nota implements Serializable{

	public NotadeVenda(String data, float totalNota, float descontoTotal, float valorLiquido,
			ArrayList<ItemProduto> listaItens, int idCodigo, int idCli) {
		super(data, totalNota, descontoTotal, valorLiquido, listaItens);
		this.idCodigo = idCodigo;
		this.idCliente = idCli;
	}

	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -6423207342181173751L;

	private int idCodigo;
	private int idCliente;

	public int getIdCodigo() {
		return idCodigo;
	}

	public void setIdCodigo(int idCodigo) {
		this.idCodigo = idCodigo;
	}

	public static long getSerialversionuid() {
		return serialVersionUID;
	}

	public int getIdCliente() {
		return idCliente;
	}

	public void setIdCliente(int idCliente) {
		this.idCliente = idCliente;
	}
}
