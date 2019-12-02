package unioeste.geral.homebank.bo;

import java.util.ArrayList;
import java.sql.Date;

public class ContaBancaria {

	private TipoConta tipo;
	private int nroConta;
	private double saldo;
	private Date dataDeAbertura;
	private ArrayList<Investimento> invest;

	public int getNroConta() {
		return nroConta;
	}
	public void setNroConta(int nroConta) {
		this.nroConta = nroConta;
	}
	public TipoConta getTipo() {
		return tipo;
	}
	public void setTipo(TipoConta tipo) {
		this.tipo = tipo;
	}
	public Date getDataDeAbertura() {
		return dataDeAbertura;
	}
	public void setDataDeAbertura(Date dataDeAbertura) {
		this.dataDeAbertura = dataDeAbertura;
	}
	public double getSaldo() {
		return saldo;
	}
	public void setSaldo(double saldo) {
		this.saldo = saldo;
	}
	public ArrayList<Investimento> getInvest() {
		return invest;
	}
	public void setInvest(ArrayList<Investimento> invest) {
		this.invest = invest;
	}
}
