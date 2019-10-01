package unioeste.geral.endereco.bo;

import java.io.Serializable;

public class Cidade implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int idCidade;
	private String nomeCidade;
	private UF UF;
	
	public int getIdCidade() {
		return idCidade;
	}
	public void setIdCidade(int idCidade) {
		this.idCidade = idCidade;
	}
	public String getNomeCidade() {
		return nomeCidade;
	}
	public void setNomeCidade(String nomeCidade) {
		this.nomeCidade = nomeCidade;
	}
	public UF getUF() {
		return UF;
	}
	public void setUF(UF UF) {
		this.UF = UF;
	}
}
