package unioeste.geral.controleestoque.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controle_estoque.bo.CNPJ;
import unioeste.geral.controle_estoque.bo.Endereco;
import unioeste.geral.controle_estoque.bo.EnderecoEspecifico;
import unioeste.geral.controle_estoque.bo.PessoaJuridica;
import unioeste.geral.controle_estoque.bo.especifica.Fornecedor;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class DAOFornecedor {
	
	private Connection conn;

	public DAOFornecedor(Connection con) {
		this.conn = con;
	}

	public Fornecedor getFornecById(int idFornecedor) throws ControleEstoqueException {
		
		ConexaoBD sql = new ConexaoBD();
		
		String query = "SELECT * FROM Fornecedor WHERE idfornecedor="+idFornecedor+";";
		
		ArrayList<String> res = null;
		
		try {
			res = sql.getTabela(conn, query);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if(res == null) {
			throw new ControleEstoqueException("Fornecedor com o id "+idFornecedor+" não está registrado no BD!");
		}
		
		String nomeFornecedor = res.get(1);
		String CNPJ = res.get(2);
		int nroLocal = Integer.parseInt(res.get(3));
		String comple = res.get(4);
		int idEnd = Integer.parseInt(res.get(5));
		
		return new Fornecedor(new PessoaJuridica(new EnderecoEspecifico(nroLocal, comple, new Endereco(idEnd, null, null, null, null)), null, null, nomeFornecedor, new CNPJ(CNPJ)),idFornecedor,null, null);
	}
}
