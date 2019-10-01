package unioeste.geral.endereco.manager;

import java.sql.Connection;

import unioeste.geral.endereco.col.*;
import unioeste.geral.exception.EnderecoException;
import unioeste.apoio.MySQL.Conexao;
import unioeste.geral.endereco.bo.*;

public class UCEnderecoGeralServicos {
	
	private Connection con;
	
	public UCEnderecoGeralServicos() throws Exception {
		
		try {
			this.con = Conexao.getConnection();
		} catch (Exception e) {

			e.printStackTrace();
		}
	}

	public Endereco obterEnderecoPorCEP(String CEP) throws EnderecoException, Exception {
		
		ColEndereco contrEnd = new ColEndereco(con);
		
		Endereco endereco = contrEnd.getEnderecoPorCEP(CEP);
		
		return endereco;
		
	}
	
	public Cidade obterCidade(Cidade cid) throws Exception {
		
		ColCidade contrCid = new ColCidade(con);
		
		Cidade cidade = contrCid.getCidade(cid.getIdCidade());
		
		return cidade;
	}
	
	public Endereco obterEnderecoPorID(Endereco end) throws EnderecoException {
		
		ColEndereco contrEnd  = new ColEndereco(con);
		try {
			contrEnd.getEnderecoPorID(end);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return end;
	}
	
	public EnderecoEspecifico obterEnderecoExterno(String site) {

		ColEnderecoEspecifico colEsp = new ColEnderecoEspecifico();
		EnderecoEspecifico endEsp = new EnderecoEspecifico();
		
		endEsp = colEsp.getEnderecoEspecifico(site);
		
		return endEsp;
	}
}
