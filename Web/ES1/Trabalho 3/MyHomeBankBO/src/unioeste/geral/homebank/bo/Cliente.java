package unioeste.geral.homebank.bo;

public class Cliente {
	
	private int idCliente;
	private PessoaFisica pf = null;
	private PessoaJuridica pj = null;
	
	public PessoaFisica getPf() {
		return pf;
	}
	public void setPf(PessoaFisica pf) {
		this.pf = pf;
	}
	public PessoaJuridica getPj() {
		return pj;
	}
	public void setPj(PessoaJuridica pj) {
		this.pj = pj;
	}
	public int getIdCliente() {
		return idCliente;
	}
	public void setIdCliente(int idCliente) {
		this.idCliente = idCliente;
	}
}
