package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Cidade implements Serializable{

	public Cidade(int idCidade, String nomeCidade, unioeste.geral.controle_estoque.bo.UF uF) {
		super();
		this.idCidade = idCidade;
		this.nomeCidade = nomeCidade;
		UF = uF;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -7317898071695523255L;
	
	private int idCidade;
	private String nomeCidade;
	private UF UF;
	
	public String getNomeCidade() {
		return nomeCidade;
	}
	public void setNomeCidade(String nomeCidade) {
		this.nomeCidade = nomeCidade;
	}
	public UF getUF() {
		return UF;
	}
	public void setUF(UF uF) {
		UF = uF;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public int getIdCidade() {
		return idCidade;
	}
	public void setIdCidade(int idCidade) {
		this.idCidade = idCidade;
	}
}
