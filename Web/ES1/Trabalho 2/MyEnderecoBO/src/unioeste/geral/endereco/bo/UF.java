package unioeste.geral.endereco.bo;

import java.io.Serializable;

public class UF implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int idUF;
	private String nomeUF;
	private Pais Pais;
	
	public int getIdUF() {
		return idUF;
	}
	public void setIdUF(int idUF) {
		this.idUF = idUF;
	}
	public String getNomeUF() {
		return nomeUF;
	}
	public void setNomeUF(String nomeUF) {
		this.nomeUF = nomeUF;
	}
	public Pais getPais() {
		return Pais;
	}
	public void setPais(Pais Pais) {
		this.Pais = Pais;
	}
}
