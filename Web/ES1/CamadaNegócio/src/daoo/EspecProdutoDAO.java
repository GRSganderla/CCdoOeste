package daoo;

import java.sql.Connection;

import modeloss.EspecProduto;
import modeloss.Produto;
import sqll.Query;

public class EspecProdutoDAO {

	public static int inserirTabelaT(EspecProduto p) throws Exception {

		Connection con = Query.getConnection();

		int idT = Query.getId(con, "SELECT idTipoProduto FROM tipoProduto WHERE '" + p.getTipoProd() + "';");
		int idProx;

		if (idT == 0) {
			idProx = Query.getId(con, "SELECT MAX(idTipoProduto) FROM tipoProduto") + 1;
			Query.insertSQLComand(con, "INSERT INTO tipoProduto VALUES ('" + idProx + "', '" + p.getTipoProd() + "');");
			idT = idProx;
		}

		return idT;
	}

	public static int inserirTabelaM(EspecProduto p) throws Exception {

		Connection con = Query.getConnection();

		int idM = Query.getId(con, "SELECT idModelo FROM modelo WHERE '" + p.getModelo() + "';");
		int idProx;
		if (idM == 0) {
			idProx = Query.getId(con, "SELECT MAX(idModelo) FROM modelo") + 1;
			Query.insertSQLComand(con, "INSERT INTO modelo VALUES ('" + idProx + "', '" + p.getModelo() + "');");
			idM = idProx;
		}
		return idM;
	}

	public static int inserirTabelaE(EspecProduto es) throws Exception {

		Connection con = Query.getConnection();

		int idProx;
		idProx = Query.getId(con, "SELECT MAX(idEstoque) FROM estoque") + 1;
		Query.insertSQLComand(con, "INSERT INTO estoque VALUES ('" + idProx + "', '1000');");
		return idProx;
	}

	public static int inserirTabelaMP(EspecProduto es, int e) throws Exception {
		
		Connection con = Query.getConnection();

		int idMP = Query.getId(con, "SELECT idMatériaPrima FROM matériaprima WHERE '" + es.getMaterial() + "';");
		int idProx;
		if (idMP == 0) {
			idProx = Query.getId(con, "SELECT MAX(idMatériaPrima) FROM matériaprima") + 1;
			Query.insertSQLComand(con, "INSERT INTO matériaprima VALUES ('" + idProx + "', '" + es.getMaterial() + "', '"+ e+"');");
			idMP = idProx;
		}
		return idMP;
	}
	
	public static void inserirTabelaPM(Produto p, EspecProduto es, int idMP) throws Exception {
		
		Connection con = Query.getConnection();
		int idProdMat = Query.getId(con, "SELECT idProdutoMatéria from produtomatéria where idProduto = '"+p.getIdProduto()+"' AND idMatériaPrima = '"+ idMP+"' ;");
		int idProx;
		if (idProdMat == 0) {
			idProx = Query.getId(con, "SELECT MAX(idProdutoMatéria) FROM produtomatéria") + 1;
			Query.insertSQLComand(con, "INSERT INTO produtomatéria VALUES ('" + idProx + "', '" + es.getPreco() + "', '"+ es.getQuant()+"', '"+ (es.getQuant()*es.getPreco())+"', '"+ p.getIdProduto()+"', '"+ idMP+"');");
			idMP = idProx;
		}
	}
}
