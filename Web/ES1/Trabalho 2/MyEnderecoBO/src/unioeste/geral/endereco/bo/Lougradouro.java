package unioeste.geral.endereco.bo;

import java.io.Serializable;

public class Lougradouro implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int idLougradouro;
	private String nomeLougradouro;
	
	public int getIdLougradouro() {
		return idLougradouro;
	}
	public void setIdLougradouro(int idLougradouro) {
		this.idLougradouro = idLougradouro;
	}
	public String getNomeLougradouro() {
		return nomeLougradouro;
	}
	public void setNomeLougradouro(String nomeLougradouro) {
		this.nomeLougradouro = nomeLougradouro;
	}	
}
