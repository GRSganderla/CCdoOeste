package unioeste.geral.homebank.col;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.geral.homebank.bo.Movimentacao;
import unioeste.geral.homebank.dao.DaoMovimentacao;

public class ColMovimentacao {
	
	private Connection con;

	public ColMovimentacao(Connection conn) {
		con = conn;
	}

	public ArrayList<String> getLancamentos(int nroConta) throws Exception {
	
		DaoMovimentacao daoLB = new DaoMovimentacao(con);
		
		ArrayList<String> mov = daoLB.getMovimentacao(nroConta);
		
		return mov;
	}

	public int getMovNextID() throws NumberFormatException, Exception {

		DaoMovimentacao daoLB = new DaoMovimentacao(con);
		
		return daoLB.selectMaxID() + 1;
	}

	public int insertLancamento(Movimentacao movConta, int nroConta) {
		
		DaoMovimentacao daoLB = new DaoMovimentacao(con);
		
		int ok = daoLB.insertMoviSQL(movConta.getIdMovimentacao(), movConta.getValor(), nroConta, movConta.getDataMovimentacao(), movConta.getMot().getIdMotivo());
		
		return ok;
	}
}