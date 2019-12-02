package unioeste.geral.homebank.col;

import java.sql.Connection;

import unioeste.geral.exception.ClienteException;
import unioeste.geral.homebank.bo.Cliente;
import unioeste.geral.homebank.bo.PessoaFisica;
import unioeste.geral.homebank.bo.PessoaJuridica;
import unioeste.geral.homebank.dao.DaoCliente;

public class ColCliente {

	private Connection con;
	
	public ColCliente(Connection Con) {
		
		con = Con;
	}
	
	public int validar(String nome, String doc) {
		
		DaoCliente dC = new DaoCliente(this.con);
		
		int idCliente = dC.buscaCliente(nome, doc);
		
		return idCliente;
	}

	public Cliente getCliente(String pessoa, String docPes) throws ClienteException {

		Cliente cl = new Cliente();
		
		if(docPes.matches("^\\d{3}\\x2E\\d{3}\\x2E\\d{3}\\x2D\\d{2}$")) {
			ColPessoaFisica colPf = new ColPessoaFisica(con);
			PessoaFisica pf = new PessoaFisica();
			
			pf = colPf.getPessoa(pessoa, docPes);
			cl.setPf(pf);
		}
		else if(docPes.matches("^\\d{2}.\\d{3}.\\d{3}/\\d{4}-\\d{2}$")) {
			
			ColPessoaJuridica colPj = new ColPessoaJuridica(con);
			PessoaJuridica pj = new PessoaJuridica();
			
			pj = colPj.getPessoa(pessoa, docPes);
			cl.setPj(pj);
		}
		else
			throw new ClienteException("CPF/CNPJ não está no formato correto");
		
		return cl;
	}
}
