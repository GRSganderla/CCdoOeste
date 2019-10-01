package daoo;

import java.sql.Connection;
import java.util.ArrayList;

import modeloss.Endereço;
import sqll.Query;

public class EndereçoDAO {
	
	public static Endereço getEndereco(int id) throws Exception {
		
		if(id == 0)
			return null;
		
		Connection con = Query.getConnection();
		ArrayList<String> cliente = Query.getTabela(con, "SELECT rua.nomeRua, bairro.nomeBairro, cidade.nomeCidade, estado.nomeEstado, país.nomePaís FROM endereço, rua, bairro, cidade, estado, país"
				+ " where endereço.idEndereço = '"+ id+"' AND endereço.idRua = rua.idRua AND endereço.idBairro = bairro.idBairro AND endereço.idCidade = cidade.idCidade AND cidade.idEstado = estado.idEstado AND estado.idPaís = país.idPaís;");
		
		Endereço cadastrado = new Endereço(cliente);
		
		return cadastrado;
	}
	
	public static int insereEndereço(Endereço c) throws Exception {
		
		Connection con = Query.getConnection();
		
		int pais = Query.getId(con, "SELECT idPaís FROM país WHERE nomePaís = '" + c.getPaís() + "';");
		int estado = Query.getId(con, "SELECT idEstado FROM estado WHERE nomeEstado = '" + c.getEstado() + "';");
		int cidade = Query.getId(con, "SELECT idCidade FROM cidade WHERE nomeCidade = '"+ c.getCidade() +"';");
		int bairro = Query.getId(con, "SELECT idBairro FROM bairro WHERE nomeBairro = '" + c.getBairro() + "';");
		int rua = Query.getId(con, "SELECT idRua FROM rua WHERE nomeRua = '" + c.getRua() + "';");
		int endereco = Query.getId(con, "SELECT idEndereço FROM endereço WHERE idRua = '" + rua + "' AND idBairro = '"+ bairro+"' AND idCidade = '"+ cidade +"';");
		int idProx;
		
		if(pais == 0) {
			idProx = Query.getId(con, "SELECT MAX(idPaís) FROM país") + 1;
			Query.insertSQLComand(con, "INSERT INTO país VALUES ('" + idProx+"', '"+c.getPaís()+"');");
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
			idProx = Query.getId(con, "SELECT MAX(idEndereço) FROM endereço")+1;
			Query.insertSQLComand(con, "INSERT INTO endereço VALUES ('"+ idProx +"', '"+ rua+ "', '"+ bairro +"', '"+cidade+"');");
			endereco = idProx;
		}
		
		return endereco;
	}
	
}
