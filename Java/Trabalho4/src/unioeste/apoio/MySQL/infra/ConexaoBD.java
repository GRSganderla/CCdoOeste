package unioeste.apoio.MySQL.infra;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;

public class ConexaoBD {
	
	public Connection getConnection() throws ClassNotFoundException{
		
		try {
			
			Class.forName("com.mysql.cj.jdbc.Driver");
			
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/receitadispesa?useTimezone=true&serverTimezone=UTC", "root", "Guilherme1702");
			
			return conn;
			
		}catch(SQLException e) {System.out.println(e.getMessage()); } 
		
		return null;
	}
	
	public void insereSQLComand(Connection conn, String query) throws Exception
	{
			
		PreparedStatement create = conn.prepareStatement(query);
		create.executeUpdate();

	}
	
	public ArrayList<String> getTabela(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			ArrayList<String> cliente = new ArrayList<String>();
			
			ResultSetMetaData rsmd = res.getMetaData();
			int colunas = rsmd.getColumnCount();
			res.next();
			
			for(int i = 1; i <= colunas; i++){
				
				cliente.add(res.getString(i));
			}
			
			return cliente;
			
		}catch(Exception e) {
			
			System.out.println(e);
		}
		return null;	
	}
	
	public String getSelect(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			String cliente;
			
			res.next();
			
			cliente = res.getString(1);
			
			return cliente;
			
		}catch(Exception e) {
			System.out.println(e);
		}
		return null;	
	}
	
	public int ultimoId(Connection conn, String query) {
		
		try {
			PreparedStatement stat = conn.prepareStatement(query);
		
			ResultSet res = stat.executeQuery();
			
			int cliente;
			
			res.next();
			
			cliente = res.getInt(1);
		
			return cliente;
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return 0;
	}
}
