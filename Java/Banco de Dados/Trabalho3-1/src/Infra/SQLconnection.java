package Infra;
import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;

public class SQLconnection {
	
	  public static Connection getConnection(String user, String pw) throws SQLException, ClassNotFoundException {
		  
	    Class.forName("org.mariadb.jdbc.Driver");

	    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/bancoBancario", user, pw);

	    return connection;
	  }
	  
	  public static void insertSQLComand(Connection conn, String query) throws Exception
		{
			try {
				
				PreparedStatement create = conn.prepareStatement(query);
				create.executeUpdate();
				
			}catch(Exception e) {System.out.println(e);}
		}
	  
	  public static void getListaInv(Connection conn, Integer id) throws Exception
		{
			try {
				
				
				PreparedStatement stat = conn.prepareStatement("SELECT Saldo FROM Conta WHERE nroConta = "+ id+ ";");
				ResultSet ress = stat.executeQuery();
				ress.next();
				double saldo = ress.getDouble(1);
				String query = "SELECT Investimento.nroInvestimento, Investimento.valor, Investimento.`Data`, Investimento.idTipoInvestimento, TipoInvestimento.nomeTipoInvestimento FROM Investimento, TipoInvestimento WHERE Investimento.nroConta = ? AND TipoInvestimento.idTipoInvestimento = Investimento.idTipoInvestimento;\n";
				stat = conn.prepareStatement(query);
				stat.setInt(1, id);
				ResultSet res = stat.executeQuery();
				ResultSetMetaData rsmd = res.getMetaData();
				int colunas = rsmd.getColumnCount();
				int colAtual;
				
				System.out.println();
				
				for(colAtual = 1; colAtual <= colunas; colAtual++)
				{
					System.out.printf("| %-35s ", rsmd.getColumnName(colAtual));
					
				}
				
				System.out.print("|\n|");
				
				for(colAtual = 1; colAtual <= colunas*38-1; colAtual++) 
					if(colAtual%38 >= 1) System.out.print("=");
					else System.out.print("|");
				
				System.out.println("|");
				
				while(res.next()) {
					
					for(int i = 1; i <= colunas; i++) {
						System.out.printf("| %-35s ", res.getString(i));
					}
					
					saldo -= res.getDouble(2);
					System.out.println("|");
				}
				for(colAtual = 1; colAtual <= colunas*38+1; colAtual++) 
					System.out.print("=");
				
				System.out.println();
				System.out.println("Saldo Total R$: " + saldo);
				
			}catch(Exception e) {System.out.println(e);}	
		}
	  
	  public static void getExtrato(Connection conn, Integer id) throws Exception
		{
			try {
				
				
				PreparedStatement stat = conn.prepareStatement("SELECT Saldo FROM Conta WHERE nroConta = "+ id+ ";");
				ResultSet ress = stat.executeQuery();
				ress.next();
				double saldo = ress.getDouble(1);
				String query = "SELECT Movimentação.`idMovimentação`, Movimentação.Data, Movimentação.`idTipoMovimentação`, TipoMovimentação.`nomeTipoMovimentação`, Movimentação.Valor FROM Movimentação, TipoMovimentação WHERE (Movimentação.nroContaCliente = ? OR Movimentação.nroContaFavorecido = ?) AND (Movimentação.`idTipoMovimentação` = TipoMovimentação.`idTipoMovimentação`);\n";
				
				stat = conn.prepareStatement(query);
				stat.setInt(1, id);
				stat.setInt(2, id);
				ResultSet res = stat.executeQuery();
				ResultSetMetaData rsmd = res.getMetaData();
				int colunas = rsmd.getColumnCount();
				int colAtual;
				
				System.out.println();
				
				for(colAtual = 1; colAtual <= colunas; colAtual++)
				{
					System.out.printf("| %-35s ", rsmd.getColumnName(colAtual));
					
				}
				
				System.out.print("|\n|");
				
				for(colAtual = 1; colAtual <= colunas*38-1; colAtual++) 
					if(colAtual%38 >= 1) System.out.print("=");
					else System.out.print("|");
				
				System.out.println("|");
				
				while(res.next()) {
					
					for(int i = 1; i <= colunas; i++) {
						System.out.printf("| %-35s ", res.getString(i));
					}
					String reg = res.getString(4);
					if(reg.equals("Depósito")) saldo += res.getDouble(5);
					else saldo -= res.getDouble(5);
					System.out.println("|");
				}
				for(colAtual = 1; colAtual <= colunas*38+1; colAtual++) 
					System.out.print("=");
				
				System.out.println();
				System.out.println("Saldo Total R$: " + saldo);
				
			}catch(Exception e) {System.out.println(e);}	
		}
	  
	  public static Integer getConta(Connection conn, int id) {
		  try {
				
				PreparedStatement stat = conn.prepareStatement("SELECT nroConta FROM Conta WHERE codCliente = "+ id +";");
				
				ResultSet res = stat.executeQuery();
				res.next();
				int possuiLog = res.getInt(1);
				
				return possuiLog;
				
			}catch(Exception e) {System.out.println(e);}
			return 0;	
		}
	  
	  public static ArrayList<String> getCliente(Connection conn) throws Exception
		{
			try {
				
				PreparedStatement stat = conn.prepareStatement("SELECT CodCliente, nomeCliente FROM Cliente LIMIT 2;");
				
				ResultSet res = stat.executeQuery();
				ArrayList<String> nomes = new ArrayList<String>();
				ResultSetMetaData rsmd = res.getMetaData();
				int colunas = rsmd.getColumnCount();
				while(res.next()) {
					for(int i = 2; i <= colunas; i++){
						
						nomes.add(res.getString(i));
					}
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
					System.out.printf("| %-40s ", rsmd.getColumnName(colAtual));
					
				}
				
				System.out.print("|\n|");
				
				for(colAtual = 1; colAtual <= colunas*43-1; colAtual++) 
					if(colAtual%43 >= 1) System.out.print("=");
					else System.out.print("|");
				
				System.out.println("|");
				
				while(res.next()) {
					
					for(int i = 1; i <= colunas; i++) {
						System.out.printf("| %-40s ", res.getString(i));
					}
					System.out.println("|");
				}
				
			}catch(Exception e) {System.out.println(e);}	
		}
}
