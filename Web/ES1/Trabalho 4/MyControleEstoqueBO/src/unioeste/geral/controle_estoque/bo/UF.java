package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class UF implements Serializable{

	public UF(int idUF, String nomeUF, unioeste.geral.controle_estoque.bo.País país) {
		super();
		this.idUF = idUF;
		this.nomeUF = nomeUF;
		País = país;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 1893719978134227073L;

	private int idUF;
	private String nomeUF;
	private País País;
	
	public String getNomeUF() {
		return nomeUF;
	}
	public void setNomeUF(String nomeUF) {
		this.nomeUF = nomeUF;
	}
	public País getPaís() {
		return País;
	}
	public void setPaís(País país) {
		País = país;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public int getIdUF() {
		return idUF;
	}
	public void setIdUF(int idUF) {
		this.idUF = idUF;
	}
}
