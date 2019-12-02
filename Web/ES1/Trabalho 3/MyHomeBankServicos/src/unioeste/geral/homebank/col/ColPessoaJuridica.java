package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.homebank.bo.CNPJ;
import unioeste.geral.homebank.bo.PessoaJuridica;

public class ColPessoaJuridica {
	
	@SuppressWarnings("unused")
	private Connection con;
	
	public ColPessoaJuridica(Connection conn) {
		con = conn;
	}
	
	public PessoaJuridica getPessoa(String nome, String cnpj) {
		
		PessoaJuridica pff = new PessoaJuridica();
		
		CNPJ c = new CNPJ();
		c.setCnpj(cnpj);
		
		pff.setCnpj(c);
		pff.setNome(nome);
		
		return pff;
	}
}
