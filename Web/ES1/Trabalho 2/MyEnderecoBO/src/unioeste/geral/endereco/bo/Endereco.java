package unioeste.geral.endereco.bo;

import java.io.Serializable;

public class Endereco  implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int idEndereco;
	private String CEP;
	private Lougradouro lougradouro;
	private Bairro bairro;
	private Cidade cidade;
	
	public int getIdEndereco() {
		return idEndereco;
	}
	public void setIdEndereco(int idEndereco) {
		this.idEndereco = idEndereco;
	}
	public String getCEP() {
		return CEP;
	}
	public void setCEP(String cEP) {
		CEP = cEP;
	}
	public Lougradouro getLougradouro() {
		return lougradouro;
	}
	public void setLougradouro(Lougradouro lougradouro) {
		this.lougradouro = lougradouro;
	}
	public Bairro getBairro() {
		return bairro;
	}
	public void setBairro(Bairro bairro) {
		this.bairro = bairro;
	}
	public Cidade getCidade() {
		return cidade;
	}
	public void setCidade(Cidade cidade) {
		this.cidade = cidade;
	}
}
