package unioeste.geral.endereco.col;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.geral.endereco.bo.*;
import unioeste.geral.endereco.dao.*;
import unioeste.geral.exception.EnderecoException;

public class ColEndereco {
	
	private Connection con;
	
	public ColEndereco(Connection con) {
		
		this.con = con;
	}
	
	public boolean validarCEP(String CEP) {
		
		return (CEP.matches("[0-9]{5}-[0-9]{3}"));
	}
	
	
	public Endereco getEnderecoPorCEP(String CEP) throws Exception, EnderecoException {
		
		Endereco end = new Endereco();
		
		if(this.validarCEP(CEP)) {
			
			DaoEndereco daoEnd = new DaoEndereco();
			
			ArrayList<Integer> ids = daoEnd.selectIds(con, CEP);
				
			if((ids.get(0)) != 0) {
				
				end.setCEP(CEP);
				
				end.setIdEndereco(ids.get(0));
				
				ColLougradouro collou = new ColLougradouro(con);
				
				end.setLougradouro(collou.getLougradouro(ids.get(1)));
				
				ColBairro colbai = new ColBairro(con);
				
				end.setBairro(colbai.getBairro(ids.get(2)));
				
				ColCidade colcid = new ColCidade(con);
				
				end.setCidade(colcid.getCidade(ids.get(3)));
				
				return end;
			}
			else {
				
				throw new EnderecoException("CEP não cadastrado");
			}
			
		}
		else {
			
			throw new EnderecoException("CEP não valido!");
		}
	}

	public void getEnderecoPorID(Endereco end) throws EnderecoException, Exception {
		
		if(end.getIdEndereco() > 0) {
			
			DaoEndereco daoEnd = new DaoEndereco();
			
			String CEP = daoEnd.selectCEP(con, end.getIdEndereco());
			
			ArrayList<Integer> ids = daoEnd.selectIds(con, CEP);
			end.setCEP(CEP);
			
			ColLougradouro collou = new ColLougradouro(con);
			
			end.setLougradouro(collou.getLougradouro(ids.get(1)));
			
			ColBairro colbai = new ColBairro(con);
			
			end.setBairro(colbai.getBairro(ids.get(2)));
			
			ColCidade colcid = new ColCidade(con);
			
			end.setCidade(colcid.getCidade(ids.get(3)));
		}
		else {
			
			throw new EnderecoException("Id do Endereço não valida!");
		}
	}
}
