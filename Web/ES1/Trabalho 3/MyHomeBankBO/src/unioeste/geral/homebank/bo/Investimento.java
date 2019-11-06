package unioeste.geral.homebank.bo;

import java.sql.Date;

public class Investimento {

	private int idInvestimento;
	private Date dataInvestida;
	private TipoInvestimento tipoInv;
	public int getIdInvestimento() {
		return idInvestimento;
	}
	public void setIdInvestimento(int idInvestimento) {
		this.idInvestimento = idInvestimento;
	}
	public Date getDataInvestida() {
		return dataInvestida;
	}
	public void setDataInvestida(Date dataInvestida) {
		this.dataInvestida = dataInvestida;
	}
	public TipoInvestimento getTipoInv() {
		return tipoInv;
	}
	public void setTipoInv(TipoInvestimento tipoInv) {
		this.tipoInv = tipoInv;
	}
}
