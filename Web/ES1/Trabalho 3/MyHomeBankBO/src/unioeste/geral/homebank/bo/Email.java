package unioeste.geral.homebank.bo;

public class Email {
	
	private int idEmail;
	private String email;
	
	public String getNome() {
		return email;
	}
	public void setNome(String nomeEmail) {
		this.email = nomeEmail;
	}
	public int getIdEmail() {
		return idEmail;
	}
	public void setIdEmail(int idEmail) {
		this.idEmail = idEmail;
	}
}
