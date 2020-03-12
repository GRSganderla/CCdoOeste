package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class DDD implements Serializable{

	public DDD(int nroDDD) {
		super();
		this.nroDDD = nroDDD;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -7128418209338640954L;
	private int nroDDD;
	
	public int getNroDDD() {
		return nroDDD;
	}
	public void setNroDDD(int nroDDD) {
		this.nroDDD = nroDDD;
	}
	
}
