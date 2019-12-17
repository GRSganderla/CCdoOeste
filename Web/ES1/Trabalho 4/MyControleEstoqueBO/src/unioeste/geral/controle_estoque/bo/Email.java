package unioeste.geral.controle_estoque.bo;

public class Email {

	public Email(int idEmail, String email) {
		super();
		this.idEmail = idEmail;
		this.email = email;
	}

	private int idEmail;
	private String email;

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public int getIdEmail() {
		return idEmail;
	}

	public void setIdEmail(int idEmail) {
		this.idEmail = idEmail;
	}
}
