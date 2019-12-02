package unioeste.geral.homebank.bo;

public class Fone {
	
	private int idFone;
	private int DDI;
	private int DDD;
	private String numero;
	
	public int getDDI() {
		return DDI;
	}
	public void setDDI(int dDI) {
		DDI = dDI;
	}
	public int getDDD() {
		return DDD;
	}
	public void setDDD(int dDD) {
		DDD = dDD;
	}
	public String getNumero() {
		return numero;
	}
	public void setNumero(String numero) {
		this.numero = numero;
	}
	public int getIdFone() {
		return idFone;
	}
	public void setIdFone(int idFone) {
		this.idFone = idFone;
	}
}
