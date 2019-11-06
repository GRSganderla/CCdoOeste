package unioeste.geral.homebank.bo;

import java.sql.Date;

public class Movimentacao {

	private int idMovimentacao;
	private double valor;
	private ContaBancaria cliConta;
	private Date dataMovimentacao;
	private Motivo mot;
	
	
	public double getValor() {
		return valor;
	}
	public void setValor(double valor) {
		this.valor = valor;
	}
	
	public Motivo getMot() {
		return mot;
	}
	public void setMot(Motivo mot) {
		this.mot = mot;
	}
	public ContaBancaria getCliConta() {
		return cliConta;
	}
	public void setCliConta(ContaBancaria cliConta) {
		this.cliConta = cliConta;
	}
	public int getIdMovimentacao() {
		return idMovimentacao;
	}
	public void setIdMovimentacao(int idMovimentacao) {
		this.idMovimentacao = idMovimentacao;
	}
	public Date getDataMovimentacao() {
		return dataMovimentacao;
	}
	public void setDataMovimentacao(Date dataMovimentacao) {
		this.dataMovimentacao = dataMovimentacao;
	}
}
