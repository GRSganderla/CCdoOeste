package unioeste.geral.controle_estoque.bo;

import java.io.Serializable;

public class Fone implements Serializable{

	public Fone(String numero, DDD nroDDD, DDI nroDDI) {
		super();
		Numero = numero;
		this.nroDDD = nroDDD;
		this.nroDDI = nroDDI;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = -338388057877421563L;
	private String Numero;
	private DDD nroDDD;
	private DDI nroDDI;
	
	public String getNumero() {
		return Numero;
	}
	public void setNumero(String numero) {
		Numero = numero;
	}
	public DDD getNroDDD() {
		return nroDDD;
	}
	public void setNroDDD(DDD nroDDD) {
		this.nroDDD = nroDDD;
	}
	public DDI getNroDDI() {
		return nroDDI;
	}
	public void setNroDDI(DDI nroDDI) {
		this.nroDDI = nroDDI;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
}
