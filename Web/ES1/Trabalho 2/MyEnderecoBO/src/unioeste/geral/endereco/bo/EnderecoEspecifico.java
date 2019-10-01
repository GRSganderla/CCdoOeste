package unioeste.geral.endereco.bo;

import java.io.Serializable;

public class EnderecoEspecifico implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int idEnderecoEspecifico;
	private int nroCasa;
	private String Complemento;
	private Endereco end;
	
	public int getIdEnderecoEspecifico() {
		return idEnderecoEspecifico;
	}
	public void setIdEnderecoEspecifico(int idEnderecoEspecifico) {
		this.idEnderecoEspecifico = idEnderecoEspecifico;
	}
	public int getNroCasa() {
		return nroCasa;
	}
	public void setNroCasa(int nroCasa) {
		this.nroCasa = nroCasa;
	}
	public String getComplemento() {
		return Complemento;
	}
	public void setComplemento(String complemento) {
		Complemento = complemento;
	}
	public Endereco getEnd() {
		return end;
	}
	public void setEnd(Endereco end) {
		this.end = end;
	}
}
