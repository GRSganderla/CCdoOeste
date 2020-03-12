package unioeste.geral.controleestoque.dao;

import java.sql.Connection;
import java.util.ArrayList;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.controle_estoque.bo.especifica.NotadeVenda;
import unioeste.geral.controleestoque.exception.ControleEstoqueException;

public class DAONotaVenda {

	public Connection con;
	
	public DAONotaVenda(Connection con) {
		this.con = con;
	}

	public void checkNota(int nro) throws ControleEstoqueException {
		
		ConexaoBD cBD = new ConexaoBD();
		String res= null;
		try {
			res = cBD.getSelect(con, "select COUNT(*) from notavenda WHERE idnotaVenda="+nro+" IN ( SELECT idnotaVenda from notavenda);");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if(res.equals("1")) {
			throw new ControleEstoqueException("O número da Nota de Venda ja existe no banco de dados!");
		}
	}

	public void insertNota(String query) {
		
		ConexaoBD cBD = new ConexaoBD();
		
		try {
			cBD.insereSQLComand(con, query);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public NotadeVenda getNotaById(int nroNota) throws ControleEstoqueException {
		
		ConexaoBD sql = new ConexaoBD();
		
		String query = "SELECT * FROM notavenda WHERE idnotaVenda="+nroNota+";";
		
		ArrayList<String> res = null;
		
		try {
			res = sql.getTabela(con, query);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if(res == null) {
			throw new ControleEstoqueException("Nota com o numero "+nroNota+" não está registrada no BD!");
		}
    
		float desconto = Float.parseFloat(res.get(2));
		float valorTotal = Float.parseFloat(res.get(3));
		int idCli = Integer.parseInt(res.get(4));
		
		return new NotadeVenda(res.get(1), valorTotal+desconto, desconto, valorTotal, null, 0, idCli);
	}

	
}
