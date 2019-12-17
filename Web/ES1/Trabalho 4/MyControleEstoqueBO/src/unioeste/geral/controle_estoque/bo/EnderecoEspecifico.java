package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class EnderecoEspecifico implements Serializable{

	public EnderecoEspecifico(int nroResidencial, String complemento, Endereco endereco) {
		super();
		this.nroResidencial = nroResidencial;
		Complemento = complemento;
		this.endereco = endereco;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -4099163594673023854L;

	private int nroResidencial;
	private String Complemento;
	private Endereco endereco;
	
	public int getNroResidencial() {
		return nroResidencial;
	}
	public void setNroResidencial(int nroResidencial) {
		this.nroResidencial = nroResidencial;
	}
	public String getComplemento() {
		return Complemento;
	}
	public void setComplemento(String complemento) {
		Complemento = complemento;
	}
	public Endereco getEndereco() {
		return endereco;
	}
	public void setEndereco(Endereco endereco) {
		this.endereco = endereco;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}	
}
