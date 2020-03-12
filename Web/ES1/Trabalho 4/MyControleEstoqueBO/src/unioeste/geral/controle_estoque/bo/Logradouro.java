package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Logradouro implements Serializable{

	public Logradouro(int idLogradouro, String nomeLogradouro) {
		super();
		this.idLogradouro = idLogradouro;
		this.nomeLogradouro = nomeLogradouro;
	}

	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 2183664169208613338L;

	public static long getSerialversionuid() {
		return serialVersionUID;
	}

	private int idLogradouro;
	private String nomeLogradouro;

	public String getNomeLogradouro() {
		return nomeLogradouro;
	}

	public void setNomeLogradouro(String nomeLogradouro) {
		this.nomeLogradouro = nomeLogradouro;
	}

	public int getIdLogradouro() {
		return idLogradouro;
	}

	public void setIdLogradouro(int idLogradouro) {
		this.idLogradouro = idLogradouro;
	}
}
