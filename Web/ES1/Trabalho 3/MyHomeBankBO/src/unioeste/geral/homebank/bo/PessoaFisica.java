package unioeste.geral.homebank.bo;

public class PessoaFisica extends Pessoa{
	
	private CPF cpf;
	private Sexo sx;
	
	public CPF getCpf() {
		return cpf;
	}
	public void setCpf(CPF cpf) {
		this.cpf = cpf;
	}
	public Sexo getSx() {
		return sx;
	}
	public void setSx(Sexo sx) {
		this.sx = sx;
	}	
}
