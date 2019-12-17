package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Endereco implements Serializable{

	public Endereco(int idEndereco, String cEP, Logradouro logradouro, Bairro bairro, Cidade cidade) {
		super();
		this.idEndereco = idEndereco;
		CEP = cEP;
		this.logradouro = logradouro;
		this.bairro = bairro;
		this.cidade = cidade;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 1607878091849453776L;

	private int idEndereco;
	private String CEP;
	private Logradouro logradouro;
	private Bairro bairro;
	private Cidade cidade;
	
	public String getCEP() {
		return CEP;
	}
	public void setCEP(String cEP) {
		CEP = cEP;
	}
	public Logradouro getLogradouro() {
		return logradouro;
	}
	public void setLogradouro(Logradouro logradouro) {
		this.logradouro = logradouro;
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
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public int getIdEndereco() {
		return idEndereco;
	}
	public void setIdEndereco(int idEndereco) {
		this.idEndereco = idEndereco;
	}
}
