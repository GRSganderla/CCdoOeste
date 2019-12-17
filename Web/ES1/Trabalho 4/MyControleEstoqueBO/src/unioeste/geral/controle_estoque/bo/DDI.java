package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class DDI implements Serializable{

	public DDI(int nroDDI) {
		super();
		this.nroDDI = nroDDI;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -6619993222524644125L;
	private int nroDDI;
	
	public int getNroDDI() {
		return nroDDI;
	}
	public void setNroDDI(int nroDDI) {
		this.nroDDI = nroDDI;
	}
}
