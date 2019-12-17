package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;
import java.util.ArrayList;

public class PessoaFisica extends Pessoa implements Serializable{

	public PessoaFisica(EnderecoEspecifico enderecoEsp, ArrayList<Fone> listFone, ArrayList<Email> listEmail, String nome, Sexo sexo, CPF cpf) {
		super(enderecoEsp, listFone, listEmail);
		this.setNome(nome);
		this.sexo = sexo;
		this.cpf = cpf;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 5988022630413410445L;
	private String nome;
	private Sexo sexo;
	private CPF cpf;
	
	public Sexo getSexo() {
		return sexo;
	}
	public void setSexo(Sexo sexo) {
		this.sexo = sexo;
	}
	public CPF getCpf() {
		return cpf;
	}
	public void setCpf(CPF cpf) {
		this.cpf = cpf;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
}
