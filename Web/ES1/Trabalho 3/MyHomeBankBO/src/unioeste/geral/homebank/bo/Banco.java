package unioeste.geral.homebank.bo;

public class Banco {

	private int idBanco;
	private String nome;
	private String nroBanco;
	
	public String getNroBanco() {
		return nroBanco;
	}
	public void setNroBanco(String nroBanco) {
		this.nroBanco = nroBanco;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public int getIdBanco() {
		return idBanco;
	}
	public void setIdBanco(int idBanco) {
		this.idBanco = idBanco;
	}
}
