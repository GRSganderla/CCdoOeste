package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class CPF implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 4389500624981903855L;
	private String numero;
	public CPF(String numero) {
		super();
		this.numero = numero;
	}
	public String getNumero() {
		return numero;
	}
	public void setNumero(String numero) {
		this.numero = numero;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	
}
