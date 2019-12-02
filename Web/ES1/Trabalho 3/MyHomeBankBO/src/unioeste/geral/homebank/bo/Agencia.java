package unioeste.geral.homebank.bo;

import unioeste.geral.endereco.bo.EnderecoEspecifico;

public class Agencia {
	
	private int nroAgencia;
	private Banco matriz;
	private EnderecoEspecifico esp;
	
	public EnderecoEspecifico getEsp() {
		return esp;
	}
	public void setEsp(EnderecoEspecifico esp) {
		this.esp = esp;
	}
	public Banco getMatriz() {
		return matriz;
	}
	public void setMatriz(Banco matriz) {
		this.matriz = matriz;
	}
	public int getNroAgencia() {
		return nroAgencia;
	}
	public void setNroAgencia(int nroAgencia) {
		this.nroAgencia = nroAgencia;
	}
}
