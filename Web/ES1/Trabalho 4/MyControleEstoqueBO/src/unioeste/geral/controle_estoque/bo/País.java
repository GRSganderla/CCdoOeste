package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class País implements Serializable{

	public País(int idPais, String nomePaís) {
		super();
		this.idPais = idPais;
		this.nomePaís = nomePaís;
	}

	/**
	 *  Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -7128130617857365632L;

	private int idPais;
	private String nomePaís;

	public String getNomePaís() {
		return nomePaís;
	}

	public void setNomePaís(String nomePaís) {
		this.nomePaís = nomePaís;
	}

	public static long getSerialversionuid() {
		return serialVersionUID;
	}

	public int getIdPais() {
		return idPais;
	}

	public void setIdPais(int idPais) {
		this.idPais = idPais;
	}
}
