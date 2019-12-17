package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Sexo implements Serializable{

	public Sexo(int idSexo, char sigla, String descricao) {
		super();
		this.idSexo = idSexo;
		Sigla = sigla;
		this.descricao = descricao;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -3923905340447138060L;
	private int idSexo;
	private char Sigla;
	private String descricao;

	public int getIdSexo() {
		return idSexo;
	}
	public void setIdSexo(int idSexo) {
		this.idSexo = idSexo;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public char getSigla() {
		return Sigla;
	}
	public void setSigla(char sigla) {
		Sigla = sigla;
	}
	public String getDescricao() {
		return descricao;
	}
	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
}
