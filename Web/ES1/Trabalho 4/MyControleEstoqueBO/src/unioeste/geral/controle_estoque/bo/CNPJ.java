package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class CNPJ implements Serializable{

	public CNPJ(String numero) {
		super();
		Numero = numero;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -5805917951840682576L;
	private String Numero;

	public String getNumero() {
		return Numero;
	}
	public void setNumero(String numero) {
		Numero = numero;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
}
