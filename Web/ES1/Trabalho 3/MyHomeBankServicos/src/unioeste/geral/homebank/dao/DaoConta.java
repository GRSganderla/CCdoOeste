package unioeste.geral.homebank.dao;

import java.sql.Connection;
import java.util.ArrayList;
import java.text.SimpleDateFormat;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.homebank.bo.ContaBancaria;
import unioeste.geral.homebank.bo.TipoConta;

public class DaoConta {
	
	private Connection con;
	
	public DaoConta(Connection conn) {
		con = conn;
	}

	public ContaBancaria selectConta(int idCli) throws Exception {
		
		ContaBancaria cb = new ContaBancaria();
		
		String query = "SELECT * FROM Conta WHERE idCliente = '"+ idCli +"';";
		
		ArrayList<String> conta = ConexaoBD.getTabela(con, query);
		
		System.out.println(conta.get(0));
		System.out.println(conta.get(1));
		System.out.println(conta.get(2));
		System.out.println(conta.get(3));
		
		cb.setNroConta(Integer.parseInt(conta.get(0)));
		cb.setSaldo(Double.parseDouble(conta.get(1)));
		
		SimpleDateFormat format = new SimpleDateFormat("dd-MM-yyyy");
	
		cb.setDataDeAbertura(new java.sql.Date(format.parse(conta.get(2)).getTime()));
		
		TipoConta tc = new TipoConta();
		if(conta.get(3).equals("1")) {
		
			tc.setIdTipoConta(1);
			tc.setNomeTipoConta("Conta-Corrente");
		}
		else if(conta.get(3).equals("2")) {
			tc.setIdTipoConta(2);
			tc.setNomeTipoConta("Conta-Poupança");
		}
		
		cb.setTipo(tc);
		
		return cb;
	}

	public void update(int idConta, double saldo) {

		String query = "UPDATE Conta SET saldo = "+saldo+" WHERE idCliente = "+idConta+";";
		
		try {
			ConexaoBD.insereSQLComand(con, query);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
