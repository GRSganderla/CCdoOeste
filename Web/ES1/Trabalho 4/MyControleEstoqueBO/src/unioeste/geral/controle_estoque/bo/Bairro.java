package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Bairro implements Serializable {

	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 8944237374421154468L;

	private int idBairro;
	private String nomeBairro;

	public Bairro(int id, String nome) {
		this.idBairro = id;
		this.nomeBairro =  nome;
	}
	
	public static long getSerialversionuid() {
		return serialVersionUID;
	}

	public String getNomeBairro() {
		return nomeBairro;
	}

	public void setNomeBairro(String nomeBairro) {
		this.nomeBairro = nomeBairro;
	}

	public int getIdBairro() {
		return idBairro;
	}

	public void setIdBairro(int idBairro) {
		
		this.idBairro = idBairro;
	}
}
