package unioeste.geral.homebank.bo;

import java.util.ArrayList;

import unioeste.geral.endereco.bo.EnderecoEspecifico;

public class Pessoa {
	
	private String nome;
	private EnderecoEspecifico esp;
	private ArrayList<Fone> fones;
	private ArrayList<Email> emails;
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public EnderecoEspecifico getEsp() {
		return esp;
	}
	public void setEsp(EnderecoEspecifico esp) {
		this.esp = esp;
	}
	public ArrayList<Fone> getFones() {
		return fones;
	}
	public void setFones(ArrayList<Fone> fones) {
		this.fones = fones;
	}
	public ArrayList<Email> getEmails() {
		return emails;
	}
	public void setEmails(ArrayList<Email> emails) {
		this.emails = emails;
	}
}
