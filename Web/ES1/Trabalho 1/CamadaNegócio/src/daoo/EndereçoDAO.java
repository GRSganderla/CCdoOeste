package daoo;

import java.sql.Connection;
import java.util.ArrayList;

import modeloss.Endere�o;
import sqll.Query;

public class Endere�oDAO {
	
	public static Endere�o getEndereco(int id) throws Exception {
		
		if(id == 0)
			return null;
		
		Connection con = Query.getConnection();
		ArrayList<String> cliente = Query.getTabela(con, "SELECT rua.nomeRua, bairro.nomeBairro, cidade.nomeCidade, estado.nomeEstado, pa�s.nomePa�s FROM endere�o, rua, bairro, cidade, estado, pa�s"
				+ " where endere�o.idEndere�o = '"+ id+"' AND endere�o.idRua = rua.idRua AND endere�o.idBairro = bairro.idBairro AND endere�o.idCidade = cidade.idCidade AND cidade.idEstado = estado.idEstado AND estado.idPa�s = pa�s.idPa�s;");
		
		Endere�o cadastrado = new Endere�o(cliente);
		
		return cadastrado;
	}
	
	public static int insereEndere�o(Endere�o c) throws Exception {
		
		Connection con = Query.getConnection();
		
		int pais = Query.getId(con, "SELECT idPa�s FROM pa�s WHERE nomePa�s = '" + c.getPa�s() + "';");
		int estado = Query.getId(con, "SELECT idEstado FROM estado WHERE nomeEstado = '" + c.getEstado() + "';");
		int cidade = Query.getId(con, "SELECT idCidade FROM cidade WHERE nomeCidade = '"+ c.getCidade() +"';");
		int bairro = Query.getId(con, "SELECT idBairro FROM bairro WHERE nomeBairro = '" + c.getBairro() + "';");
		int rua = Query.getId(con, "SELECT idRua FROM rua WHERE nomeRua = '" + c.getRua() + "';");
		int endereco = Query.getId(con, "SELECT idEndere�o FROM endere�o WHERE idRua = '" + rua + "' AND idBairro = '"+ bairro+"' AND idCidade = '"+ cidade +"';");
		int idProx;
		
		if(pais == 0) {
			idProx = Query.getId(con, "SELECT MAX(idPa�s) FROM pa�s") + 1;
			Query.insertSQLComand(con, "INSERT INTO pa�s VALUES ('" + idProx+"', '"+c.getPa�s()+"');");
			pais = idProx;
		}
		if(estado == 0) {
			idProx = Query.getId(con, "SELECT MAX(idEstado) FROM estado") + 1;
			Query.insertSQLComand(con, "INSERT INTO estado VALUES ('" + idProx+"', '"+c.getEstado()+"', '"+ pais +"');");
			estado = idProx;
		}
		if(cidade == 0) {
			idProx = Query.getId(con, "SELECT MAX(idCidade) FROM cidade")+1;
			Query.insertSQLComand(con, "INSERT INTO cidade VALUES ('"+ idProx +"', '"+ c.getCidade() +"', '"+ estado +"');");
			cidade = idProx;
		}
		if(bairro == 0) {
			idProx = Query.getId(con, "SELECT MAX(idBairro) FROM bairro") + 1;
			Query.insertSQLComand(con, "INSERT INTO bairro VALUES ('" + idProx+"', '"+c.getBairro()+"');");
			bairro = idProx;
		}
		if(rua == 0) {
			idProx = Query.getId(con, "SELECT MAX(idRua) FROM rua") + 1;
			Query.insertSQLComand(con, "INSERT INTO rua VALUES ('"+ idProx +"', '"+c.getRua()+"');");
			rua = idProx;
		}
		if(endereco == 0) {
			idProx = Query.getId(con, "SELECT MAX(idEndere�o) FROM endere�o")+1;
			Query.insertSQLComand(con, "INSERT INTO endere�o VALUES ('"+ idProx +"', '"+ rua+ "', '"+ bairro +"', '"+cidade+"');");
			endereco = idProx;
		}
		
		return endereco;
	}
	
}
