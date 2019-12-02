package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.homebank.bo.CPF;
import unioeste.geral.homebank.bo.PessoaFisica;

public class ColPessoaFisica {
	
	@SuppressWarnings("unused")
	private Connection con;
	
	public ColPessoaFisica(Connection conn) {
		con = conn;
	}
	
	public PessoaFisica getPessoa(String nome, String cpf) {
		
		PessoaFisica pff = new PessoaFisica();
		
		CPF c = new CPF();
		c.setCPF(cpf);
		
		pff.setCpf(c);
		pff.setNome(nome);
		
		return pff;
	}
}
