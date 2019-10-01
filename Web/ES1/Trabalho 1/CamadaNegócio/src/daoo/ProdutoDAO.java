package daoo;

import java.sql.Connection;

import modeloss.Produto;
import sqll.Query;

public class ProdutoDAO {

	public static void insereProduto(Produto p, int tipo, int modelo) throws Exception {
		
		Connection con = Query.getConnection();
		
		int id = Query.getId(con, "SELECT produto.idProduto FROM produto, tipoProduto, modelo WHERE produto.nomeProd = '"+p.getNome()+"' AND produto.Modelo_idModelo = modelo.idModelo AND produto.idTipoProduto = tipoProduto.idTipoProduto;");
		int idProx;
		
		if(id == 0) {
			
			idProx = Query.getId(con, "SELECT MAX(idProduto) FROM produto;")+1;
			Query.insertSQLComand(con, "INSERT INTO produto VALUES ('"+idProx+"', '"+p.getNome()+"', '"+p.getDescricao()+"', '"+p.getPeso()+"', '"+p.getCor()+"', '"+p.getTempoFab()+"', '"+tipo+"', '"+modelo+"');");
			id = idProx;
		}
		
		p.setIdProduto(id);
	}
	
	
	public static void deleteProduto(String id) throws Exception {
		
		Connection con = Query.getConnection();
		System.out.println("ALO");
		Query.insertSQLComand(con, "DELETE FROM produto WHERE nomeProd = '"+ id+"';");
	}
	
}
