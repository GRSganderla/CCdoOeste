package comandosSQL;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.ArrayList;

public class funcoesSQL {
	
	public static int getLogin(Connection conn, String login, String senha) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement("SELECT idCliente FROM cliente WHERE Email = '"+ login +"' AND Senha = '"+ senha +"';");
			
			ResultSet res = stat.executeQuery();
			res.next();
			int possuiLog = res.getInt(1);
			
			return possuiLog;
			
		}catch(Exception e) {System.out.println(e);}
		return 0;	
	}
	
	public static ArrayList<String> getCliente(Connection conn, int idCliente) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement("SELECT cliente.*, rua.nomeRua, bairro.NomeBairro, cidade.nomeCidade, estado.nomeEstado, pa�s.nomePa�s "
					+ "FROM cliente, endere�o, rua, bairro, cidade, estado, pa�s where cliente.idCliente = '"+ idCliente+"' AND cliente.idEndere�o = endere�o.idEndere�o "
							+ " AND endere�o.idRua = rua.idRua AND endere�o.idBairro = bairro.idBairro AND endere�o.idCidade = cidade.idCidade AND cidade.idEstado = estado.idEstado AND estado.idPa�s = pa�s.idPa�s;");
			
			
			ResultSet res = stat.executeQuery();
			ArrayList<String> nomes = new ArrayList<String>();
			ResultSetMetaData rsmd = res.getMetaData();
			int colunas = rsmd.getColumnCount();
			res.next();
			for(int i = 2; i <= colunas; i++){
				
				nomes.add(res.getString(i));
			}
			
			return nomes;
			
		}catch(Exception e) {System.out.println(e);}
		return null;	
	}
	
	public static void select(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			ResultSetMetaData rsmd = res.getMetaData();
			int colunas = rsmd.getColumnCount();
			int colAtual;
			
			System.out.println();
			
			for(colAtual = 1; colAtual <= colunas; colAtual++)
			{
				System.out.printf("| %-50s ", rsmd.getColumnName(colAtual));
				
			}
			
			System.out.print("|\n|");
			
			for(colAtual = 1; colAtual <= colunas*53-1; colAtual++) System.out.print("=");
			
			System.out.println("|");
			
			while(res.next()) {
				
				for(int i = 1; i <= colunas; i++) {
					System.out.printf("| %-50s ", res.getString(i));
				}
				System.out.println("|");
			}
			
		}catch(Exception e) {System.out.println(e);}	
	}
	
	public static void insertSQLComand(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement create = conn.prepareStatement(query);
			create.executeUpdate();
			
		}catch(Exception e) {System.out.println(e);}
	}
	
	public static Connection getConnection(String query) throws Exception{
		
		try {
			
			Class.forName("com.mysql.jdbc.Driver");
			
			Connection conn = DriverManager.getConnection(query, "root", "");
			return conn;
			
		}catch(Exception e) {System.out.println(e); } 
		
		return null;
	}
}
