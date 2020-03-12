package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;
import java.util.ArrayList;

public abstract class Pessoa implements Serializable {

	public Pessoa(EnderecoEspecifico enderecoEsp, ArrayList<Fone> listFone, ArrayList<Email> listEmail) {
		this.enderecoEsp = enderecoEsp;
		this.listFone = listFone;
		this.listEmail = listEmail;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 6543832224816443068L;

	private EnderecoEspecifico enderecoEsp;
	private ArrayList<Fone> listFone;
	private ArrayList<Email> listEmail;
	
	public EnderecoEspecifico getEnderecoEsp() {
		return enderecoEsp;
	}
	public void setEnderecoEsp(EnderecoEspecifico enderecoEsp) {
		this.enderecoEsp = enderecoEsp;
	}
	public ArrayList<Fone> getListFone() {
		return listFone;
	}
	public void setListFone(ArrayList<Fone> listFone) {
		this.listFone = listFone;
	}
	public ArrayList<Email> getListEmail() {
		return listEmail;
	}
	public void setListEmail(ArrayList<Email> listEmail) {
		this.listEmail = listEmail;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}	
}
