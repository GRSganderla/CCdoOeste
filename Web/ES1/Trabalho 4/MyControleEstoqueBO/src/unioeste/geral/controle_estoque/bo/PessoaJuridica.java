package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;
import java.util.ArrayList;

public class PessoaJuridica extends Pessoa implements Serializable{

	public PessoaJuridica(EnderecoEspecifico enderecoEsp, ArrayList<Fone> listFone, ArrayList<Email> listEmail, String Nome, CNPJ cpj) {
		super(enderecoEsp, listFone, listEmail);
		this.nome = Nome;
		this.cnpj = cpj;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 8556834880092366579L;
	private String nome;
	private CNPJ cnpj;

	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public CNPJ getCnpj() {
		return cnpj;
	}
	public void setCnpj(CNPJ cnpj) {
		this.cnpj = cnpj;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
}
