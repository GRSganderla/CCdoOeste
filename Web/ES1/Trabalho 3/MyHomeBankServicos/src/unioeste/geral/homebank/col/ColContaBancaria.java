package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.homebank.bo.ContaBancaria;
import unioeste.geral.homebank.dao.DaoConta;

public class ColContaBancaria {

	private Connection con;

	public ColContaBancaria(Connection conn) {
		con = conn;
	}

	public ContaBancaria getConta(int idCli) throws Exception {
		
		DaoConta daoC = new DaoConta(con);
		
		ContaBancaria cb = daoC.selectConta(idCli);
		
		return cb;
	}

	public void atualizaSaldo(int idConta, double saldo) {

		DaoConta daoC = new DaoConta(con);
		
		daoC.update(idConta, saldo);
	}
	
	
}
